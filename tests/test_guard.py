# -*- coding: utf-8 -*-
"""Защита по телеметрии: сбой шины I2C (255) и местное катание.

Запуск из папки kart-marshal:

    python -m unittest discover tests
"""

import importlib.util
import os
import time
import types
import unittest
from unittest import mock

# В стандартной библиотеке есть встроенный модуль marshal, и `import marshal`
# достал бы его, а не сервер. Поэтому сервер грузим по пути к файлу.
_HERE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_spec = importlib.util.spec_from_file_location("kart_marshal", os.path.join(_HERE, "marshal.py"))
M = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(M)


def status(**fields):
    """Телеметрия свободного исправного карта с правками."""
    st = {"DUUID": "90000001", "kOn": "0", "kOn1": "1", "driveOn": 0,
          "timeDriveOn": 0, "localModeWaitStart": 0, "adcIn": "44",
          "adc0": "44", "adc3": "48"}
    st.update(fields)
    return st


class SyncThread(object):
    """Поток, который выполняет работу сразу, — чтобы тест видел результат."""

    def __init__(self, target=None, args=(), kwargs=None, daemon=None):
        self.target, self.args, self.kwargs = target, args, kwargs or {}

    def start(self):
        self.target(*self.args, **self.kwargs)


class GuardCheckTest(unittest.TestCase):

    def test_healthy_kart_is_fine(self):
        self.assertIsNone(M.guard_check(status(), "idle"))

    def test_healthy_kart_with_pedal_floored_is_fine(self):
        st = status(kOn="1", adcIn="216", adc0="216", adc3="220")
        self.assertIsNone(M.guard_check(st, "ride"))

    def test_value_254_is_not_a_fault(self):
        self.assertIsNone(M.guard_check(status(kOn="1", adcIn="254"), "ride"))

    def test_adc_255_with_relay_on_stops(self):
        kind, stop, text = M.guard_check(status(kOn="1", adcIn="255", adc0="255"), "ride")
        self.assertEqual(kind, "adc")
        self.assertTrue(stop)
        self.assertIn("adcIn", text)
        self.assertIn("adc0", text)

    def test_adc_255_as_number_is_seen(self):
        kind, stop, _ = M.guard_check(status(kOn=1, adc3=255), "idle")
        self.assertEqual(kind, "adc")
        self.assertTrue(stop)

    def test_adc_255_with_relay_off_only_warns(self):
        kind, stop, _ = M.guard_check(status(adcIn="255"), "idle")
        self.assertEqual(kind, "adc")
        self.assertFalse(stop)

    def test_local_ride_on_free_kart_stops(self):
        st = status(kOn="1", localModeWaitStart=1, timeDriveOn=1)
        kind, stop, _ = M.guard_check(st, "idle")
        self.assertEqual(kind, "local")
        self.assertTrue(stop)

    def test_local_ride_seen_by_timer_alone_stops(self):
        st = status(localModeWaitStart="1", timeDriveOn="1")
        self.assertTrue(M.guard_check(st, "idle")[1])

    def test_local_mode_armed_but_not_started_only_warns(self):
        st = status(localModeWaitStart=1, driveOn=1)
        kind, stop, _ = M.guard_check(st, "idle")
        self.assertEqual(kind, "local")
        self.assertFalse(stop)

    def test_local_mode_during_paid_ride_is_left_alone(self):
        st = status(kOn="1", localModeWaitStart=1, timeDriveOn=1)
        kind, stop, _ = M.guard_check(st, "ride")
        self.assertEqual(kind, "local")
        self.assertFalse(stop)

    def test_adc_fault_wins_over_local_mode(self):
        st = status(kOn="1", localModeWaitStart=1, timeDriveOn=1, adcIn="255")
        self.assertEqual(M.guard_check(st, "ride")[0], "adc")


class GuardStatusTest(unittest.TestCase):

    def setUp(self):
        M.guard_alarms.clear()
        M.guard_acted.clear()
        M.guard_logged.clear()
        self.sent, self.gates, self.finished = [], [], []
        patches = [
            mock.patch.object(M, "threading", types.SimpleNamespace(Thread=SyncThread)),
            mock.patch.object(M, "ws_send", lambda k, obj: self.sent.append(obj) or True),
            mock.patch.object(M, "drive_gate",
                              lambda k, allow, wait=True: self.gates.append(allow)),
            mock.patch.object(M, "ride_finish",
                              lambda k, why="": self.finished.append(why)),
            mock.patch.object(M, "wslog", lambda *a: None),
            mock.patch.object(M, "live_kart", lambda k: k),
        ]
        for p in patches:
            p.start()
            self.addCleanup(p.stop)

    def kart(self, phase="idle"):
        ride = dict(M.IDLE)
        ride["phase"] = phase
        return {"id": "90000001", "duuid": "90000001", "ride": ride}

    def test_local_ride_gets_stop_and_gate_off(self):
        M.guard_status(self.kart(), status(kOn="1", localModeWaitStart=1, timeDriveOn=1))
        self.assertEqual(self.sent, [{"Command": "Stop"}])
        self.assertEqual(self.gates, [False])
        self.assertEqual(self.finished, [])

    def test_stop_is_not_repeated_within_guard_repeat(self):
        k = self.kart()
        st = status(kOn="1", localModeWaitStart=1, timeDriveOn=1)
        M.guard_status(k, st)
        M.guard_status(k, st)
        self.assertEqual(len(self.sent), 1)

    def test_stop_is_repeated_after_guard_repeat(self):
        k = self.kart()
        st = status(kOn="1", localModeWaitStart=1, timeDriveOn=1)
        M.guard_status(k, st)
        M.guard_acted["90000001"] -= M.GUARD_REPEAT + 1
        M.guard_status(k, st)
        self.assertEqual(len(self.sent), 2)

    def test_adc_fault_during_ride_finishes_the_ride(self):
        M.guard_status(self.kart("ride"), status(kOn="1", adcIn="255", adc0="255"))
        self.assertEqual(len(self.finished), 1)
        self.assertIn("ЗАЩИТА", self.finished[0])
        self.assertEqual(self.sent, [])

    def test_adc_fault_on_free_kart_with_relay_on_stops(self):
        M.guard_status(self.kart(), status(kOn="1", adc3="255"))
        self.assertEqual(self.sent, [{"Command": "Stop"}])
        self.assertEqual(self.gates, [False])

    def test_adc_fault_with_relay_off_only_raises_alarm(self):
        M.guard_status(self.kart(), status(adcIn="255"))
        self.assertEqual(self.sent, [])
        self.assertEqual(self.finished, [])
        self.assertIn("90000001", M.guard_alarms)

    def test_armed_local_mode_sends_nothing(self):
        M.guard_status(self.kart(), status(localModeWaitStart=1, driveOn=1))
        self.assertEqual(self.sent, [])
        self.assertEqual(self.gates, [])
        self.assertNotIn("90000001", M.guard_alarms)

    def test_local_stop_skipped_if_paid_ride_began_meanwhile(self):
        k = self.kart()
        started = self.kart("ride")
        with mock.patch.object(M, "live_kart", lambda _k: started):
            M.guard_status(k, status(kOn="1", localModeWaitStart=1, timeDriveOn=1))
        self.assertEqual(self.sent, [])
        self.assertEqual(self.finished, [])

    def test_healthy_status_does_nothing(self):
        M.guard_status(self.kart("ride"), status(kOn="1", adcIn="188"))
        self.assertEqual((self.sent, self.gates, self.finished), ([], [], []))

    def test_local_gate_kept_if_paid_ride_began_during_stop(self):
        idle, riding = self.kart(), self.kart("ride")
        seen = iter([idle, riding])
        with mock.patch.object(M, "live_kart", lambda _k: next(seen)):
            M.guard_status(idle, status(kOn="1", localModeWaitStart=1, timeDriveOn=1))
        self.assertEqual(self.sent, [{"Command": "Stop"}])
        self.assertEqual(self.gates, [])


class GuardStartBlockTest(unittest.TestCase):

    def setUp(self):
        M.guard_alarms.clear()
        self.kart = {"duuid": "90000001"}

    def test_fresh_adc_alarm_blocks_start(self):
        M.guard_alarms["90000001"] = {"kind": "adc", "text": "сбой платы", "at": time.time()}
        self.assertIn("неисправен", M.guard_start_block(self.kart))

    def test_local_alarm_does_not_block_start(self):
        M.guard_alarms["90000001"] = {"kind": "local", "text": "местный", "at": time.time()}
        self.assertEqual(M.guard_start_block(self.kart), "")

    def test_old_adc_alarm_does_not_block_start(self):
        M.guard_alarms["90000001"] = {"kind": "adc", "text": "сбой платы",
                                      "at": time.time() - M.GUARD_ALARM_TTL - 1}
        self.assertEqual(M.guard_start_block(self.kart), "")


class RaceTest(unittest.TestCase):
    """Гонки защиты с заездом, продлением и переподключением карта."""

    def setUp(self):
        self.sent, self.gates, self.gate_now, self.wanted = [], [], [], []
        patches = [
            mock.patch.object(M, "threading", types.SimpleNamespace(Thread=SyncThread)),
            mock.patch.object(M, "time", types.SimpleNamespace(time=time.time,
                                                               sleep=lambda s: None)),
            mock.patch.object(M, "ws_send", self.fake_ws_send),
            mock.patch.object(M, "drive_gate",
                              lambda k, allow, wait=True: self.gates.append(allow)),
            mock.patch.object(M, "send_gate_now",
                              lambda k, allow: self.gate_now.append(allow)),
            mock.patch.object(M, "want_set", lambda k, **f: self.wanted.append(f)),
            mock.patch.object(M, "speed_gate", lambda k, fast, wait=False: None),
            mock.patch.object(M, "send_light_now", lambda k, on: None),
            mock.patch.object(M, "send_speed_now", lambda k, pct: None),
            mock.patch.object(M, "set_speed_http", lambda k, v: None),
            mock.patch.object(M, "renew_check", lambda k, d, t: None),
            mock.patch.object(M, "rides_save_safe", lambda: None),
            mock.patch.object(M, "kart_online", lambda k: True),
            mock.patch.object(M, "kart_reachable", lambda k: True),
            mock.patch.object(M, "wslog", lambda *a: None),
        ]
        for p in patches:
            p.start()
            self.addCleanup(p.stop)
        self.on_stop = None

    def fake_ws_send(self, kart, obj):
        self.sent.append(obj)
        if obj.get("Command") == "Stop" and self.on_stop:
            self.on_stop(kart)
        return True

    def riding(self):
        now = time.time()
        ride = dict(M.IDLE, phase="ride", minutes=10, t0=now, t_paid=now + 300,
                    t_end=now + 330)
        return {"id": "90000001", "duuid": "90000001", "ride": ride}

    def finish_events(self, since):
        return [e for e in M.ride_events[since:] if e["event"] == "finish"]

    def test_finish_closes_ride_on_live_object_before_board(self):
        stale = self.riding()
        live = dict(stale)            # переподключился: новый объект, тот же заезд
        phase_at_stop = []
        self.on_stop = lambda k: phase_at_stop.append(live["ride"]["phase"])
        with mock.patch.object(M, "live_kart", lambda _k: live):
            M.ride_finish(stale, "ЗАЩИТА: тест")
        self.assertEqual(live["ride"]["phase"], "idle")
        self.assertEqual(phase_at_stop, ["idle"])
        self.assertTrue(live.get("stop_at"))

    def test_second_finish_sends_no_second_event(self):
        k = self.riding()
        since = len(M.ride_events)
        with mock.patch.object(M, "live_kart", lambda _k: k):
            M.ride_finish(k, "заезд закончен")
            M.ride_finish(k, "ЗАЩИТА: тест")
        self.assertEqual(len(self.finish_events(since)), 1)

    def test_renew_stops_if_ride_closed_while_waiting_for_stop_ok(self):
        k = self.riding()

        def closed_by_guard(kart):
            M.stop_ok_at["90000001"] = time.time() + 1
            k["ride"] = dict(M.IDLE)

        self.on_stop = closed_by_guard
        with mock.patch.object(M, "live_kart", lambda _k: k):
            M.ride_renew(k)
        self.assertEqual(self.sent, [{"Command": "Stop"}])
        self.assertEqual(self.gate_now, [])
        self.assertNotIn({"gate": True}, self.wanted)

    def fresh_kart(self, **fields):
        k = {"id": "90000001", "duuid": "90000001", "ride": dict(M.IDLE),
             "status": {"kOn": "1"}, "status_at": time.time()}
        k.update(fields)
        return k

    def test_start_right_after_stop_sends_gate_without_trusting_telemetry(self):
        # Status, запрошенный до Stop, а пришедший после, моложе Stop и всё ещё
        # говорит kOn=1 — верить ему нельзя.
        stopped = time.time() - 1
        M.stop_ok_at["90000001"] = stopped + 0.5
        M.ride_start(self.fresh_kart(stop_at=stopped), 10, 0)
        self.assertEqual(self.gate_now, [True])
        self.assertEqual(self.gates, [])

    def test_start_without_recent_stop_trusts_telemetry(self):
        M.ride_start(self.fresh_kart(stop_at=time.time() - 60), 10, 0)
        self.assertEqual(self.gates, [True])
        self.assertEqual(self.gate_now, [])

    def test_start_sends_no_start_if_ride_closed_meanwhile(self):
        k = self.fresh_kart()
        with mock.patch.object(M, "drive_gate",
                               lambda kart, allow, wait=True: kart.update(ride=dict(M.IDLE))):
            M.ride_start(k, 10, 0)
        self.assertNotIn("Start", [c.get("Command") for c in self.sent])
        self.assertEqual(k["ride"]["phase"], "idle")
        self.assertFalse(k["ride"].get("t_paid"))


class GuardAlarmInPanelTest(unittest.TestCase):

    def setUp(self):
        M.guard_alarms.clear()

    def item(self, now):
        k = {"id": "90000001", "duuid": "90000001", "ride": dict(M.IDLE), "seen": now}
        return M.state_item(k, now, False, True)

    def test_fresh_alarm_is_shown(self):
        now = time.time()
        M.guard_alarms["90000001"] = {"text": "сбой платы", "at": now - 5}
        self.assertEqual(self.item(now)["alarm"], "сбой платы")

    def test_old_alarm_is_hidden(self):
        now = time.time()
        M.guard_alarms["90000001"] = {"text": "сбой платы", "at": now - M.GUARD_ALARM_TTL - 1}
        self.assertEqual(self.item(now)["alarm"], "")

    def test_no_alarm_by_default(self):
        self.assertEqual(self.item(time.time())["alarm"], "")


if __name__ == "__main__":
    unittest.main()
