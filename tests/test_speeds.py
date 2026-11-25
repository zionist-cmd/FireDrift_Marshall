# -*- coding: utf-8 -*-
"""Скорость по градациям: таблица «карт × градация» в karts.conf и лимит заезда.

Запуск из папки kart-marshal:

    python -m unittest discover tests
"""

import os
import tempfile
import time
import types
import unittest
from unittest import mock

from test_guard import M, SyncThread

SPEEDS = [{"name": "Обычный", "val": 70}, {"name": "Новичок", "val": 50},
          {"name": "Профи", "val": 100}]


class PresetSpeedTest(unittest.TestCase):

    def setUp(self):
        for name, value in (("KART_PRESET", {"90000001": {"Новичок": 40}}),
                            ("KART_SPEED", {"90000001": 75})):
            p = mock.patch.object(M, name, value)
            p.start()
            self.addCleanup(p.stop)
        p = mock.patch.dict(M.S, {"speeds": SPEEDS})
        p.start()
        self.addCleanup(p.stop)

    def test_own_value_of_the_kart_wins(self):
        self.assertEqual(M.preset_speed("90000001", 1), 40)

    def test_no_own_value_takes_the_common_one(self):
        self.assertEqual(M.preset_speed("90000001", 2), 100)
        self.assertEqual(M.preset_speed("90000002", 1), 50)

    def test_unknown_preset_falls_back_to_kart_limit(self):
        self.assertEqual(M.preset_speed("90000001", 9), 75)

    def test_ride_limit_is_kept_for_the_whole_ride(self):
        k = {"duuid": "90000001", "ride": dict(M.IDLE, phase="ride", limit=40)}
        self.assertEqual(M.ride_speed(k), 40)

    def test_without_ride_limit_the_kart_limit_is_used(self):
        self.assertEqual(M.ride_speed({"duuid": "90000001", "ride": dict(M.IDLE)}), 75)


class RideStartLimitTest(unittest.TestCase):

    def setUp(self):
        self.sent, self.speed_http = [], []
        patches = [
            mock.patch.object(M, "KART_PRESET", {"90000001": {"Новичок": 40}}),
            mock.patch.object(M, "KART_SPEED", {"90000001": 75}),
            mock.patch.dict(M.S, {"speeds": SPEEDS}),
            mock.patch.object(M, "threading", types.SimpleNamespace(Thread=SyncThread)),
            mock.patch.object(M, "time", types.SimpleNamespace(time=time.time,
                                                               sleep=lambda s: None)),
            mock.patch.object(M, "ws_send", lambda k, obj: self.sent.append(obj) or True),
            mock.patch.object(M, "drive_gate", lambda k, allow, wait=True: None),
            mock.patch.object(M, "set_speed_http", lambda k, v: self.speed_http.append(v)),
            mock.patch.object(M, "rides_save_safe", lambda: None),
            mock.patch.object(M, "ride_event", lambda *a, **kw: None),
            mock.patch.object(M, "wslog", lambda *a: None),
        ]
        for p in patches:
            p.start()
            self.addCleanup(p.stop)

    def kart(self):
        return {"id": "90000001", "duuid": "90000001", "ride": dict(M.IDLE),
                "status": {"kOn": "1"}, "status_at": time.time()}

    def test_panel_start_uses_the_kart_value_of_the_preset(self):
        k = self.kart()
        M.ride_start(k, 10, 1)                # «Новичок»: у карта свой 40
        self.assertEqual(k["ride"]["limit"], 40)
        self.assertEqual(self.sent[-1]["Speed"], 40)
        self.assertEqual(self.speed_http, [40])

    def test_panel_start_uses_the_common_value_when_kart_has_none(self):
        k = self.kart()
        M.ride_start(k, 10, 2)                # «Профи»: своего нет, общий 100
        self.assertEqual(k["ride"]["limit"], 100)

    def test_explicit_limit_wins_over_presets(self):
        k = self.kart()
        M.ride_start(k, 10, 0, limit=75)      # так стартует CRM
        self.assertEqual(k["ride"]["limit"], 75)
        self.assertEqual(self.speed_http, [75])


class KartsConfTest(unittest.TestCase):

    def test_presets_survive_write_and_read(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = os.path.join(tmp, "karts.conf")
            with mock.patch.object(M, "NAMES_PATH", path):
                M.write_names({"90000001": "12"}, {"90000001": 75}, {},
                              {"90000001": {"Новичок": 40, "Профи": 90}})
                names, speed, crawl, preset = M.read_names()
        self.assertEqual(names.get("90000001"), "12")
        self.assertEqual(speed, {"90000001": 75})
        self.assertEqual(preset, {"90000001": {"Новичок": 40, "Профи": 90}})


if __name__ == "__main__":
    unittest.main()
