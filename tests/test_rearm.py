# -*- coding: utf-8 -*-
"""Перевзвод платы после щелчка I/O посреди заезда (rearm_tick, ride_rearm).

Запуск из папки kart-marshal:

    python -m unittest discover tests
"""

import time
import unittest
from unittest import mock

import test_guard as G

M = G.M


class RearmTest(unittest.TestCase):
    """Плата как 25.11 у №13: после щелчка I/O считает заезд сама."""

    # Заглушки и помощники — из тестов продления без Stop. Не наследуем, чтобы
    # их тесты не прогонялись второй раз с этой платой.
    fake_ws_send = G.SoftRenewTest.fake_ws_send
    riding = G.SoftRenewTest.riding
    renew = G.SoftRenewTest.renew
    commands = G.SoftRenewTest.commands

    def setUp(self):
        G.SoftRenewTest.setUp(self)
        self.logs = []
        p = mock.patch.object(M, "wslog", lambda *a: self.logs.append(a[-1]))
        p.start()
        self.addCleanup(p.stop)
        self.pedal = "44"                     # adcIn: отпущена 40-49, нажата 180-189

    def board(self, kart, obj):
        """Start в ожидании берёт Length и Speed; Stop роняет реле и снимает
        катание по I/O; новый Start после Stop — снова ожидание (dIn уже 1,
        нового фронта нет)."""
        st = dict(kart["status"])
        cmd = obj.get("Command")
        if cmd == "Start":
            if M.kart_num(st, "timeDriveOn") == 0:
                st["lengthDrive"] = obj["Length"]
                if "Speed" in obj:
                    st["Speed"] = obj["Speed"]
            st["kOn"] = "1"
        elif cmd == "Stop":
            M.stop_ok_at["90000001"] = time.time() + 1
            st.update(kOn="0", timeDriveOn="0", adcIn="2")
        if st.get("kOn") == "1" and cmd != "Stop":
            st["adcIn"] = self.pedal
        kart["status"], kart["status_at"] = st, time.time() + 0.01

    def io_clicked(self, chunk_in=400, rest=1000, status_age=0.0, **status):
        """Заезд идёт, кусок кончится через chunk_in с, гость щёлкнул I/O."""
        k = self.riding()
        now = time.time()
        k["ride"].update(t_end=now + rest, chunk_end=now + chunk_in,
                         start_at=now - 120)
        k["status"].update(dict({"timeDriveOn": "1", "adcIn": self.pedal}, **status))
        k["status_at"] = now - status_age
        return k

    def tick(self, k):
        with mock.patch.object(M, "live_kart", lambda _k: k):
            M.rearm_tick(k, k["ride"], time.time())

    def test_io_click_with_pedal_released_rearms_the_board_once(self):
        k = self.io_clicked()
        self.tick(k)
        self.assertEqual(self.commands(), ["Stop", "Start"])
        self.assertEqual(self.gate_now, [True])              # реле вернули сразу
        self.assertAlmostEqual(k["ride"]["chunk_end"], time.time() + 540, delta=2)
        self.assertGreater(k["ride"]["start_at"], time.time() - 2)
        self.assertTrue(any("перевзвод после щелчка I/O" in s for s in self.logs))
        self.assertEqual(k["status"]["timeDriveOn"], "0")   # плата снова ждёт
        sent = len(self.sent)
        self.tick(k)                                         # второй тик — тишина
        self.assertEqual(len(self.sent), sent)

    def test_next_renewal_after_rearm_goes_without_stop(self):
        k = self.io_clicked()
        self.tick(k)
        self.sent[:] = []
        self.renew(k)
        self.assertEqual(self.commands(), ["Start"])
        self.assertTrue(any("продление без Stop" in s for s in self.logs))

    def test_pedal_pressed_waits_and_logs_once(self):
        self.pedal = "187"
        k = self.io_clicked()
        self.tick(k)
        k["status_at"] = time.time()
        self.tick(k)
        self.assertEqual(self.commands(), [])
        self.assertEqual(sum("педаль нажата" in s for s in self.logs), 1)

    def test_pedal_pressed_in_the_fresh_status_cancels_the_stop(self):
        k = self.io_clicked()                 # по старому статусу отпущена
        self.pedal = "186"                    # а свежий Status — нажата
        self.tick(k)
        self.assertEqual(self.commands(), [])
        self.assertIn({"Command": "Status"}, self.sent)

    def test_single_chunk_ride_needs_no_rearm(self):
        self.tick(self.io_clicked(chunk_in=400, rest=420))
        self.assertEqual(self.sent, [])

    def test_close_to_planned_renewal_leaves_it_to_ride_renew(self):
        self.tick(self.io_clicked(chunk_in=10))
        self.assertEqual(self.sent, [])

    def test_status_older_than_our_start_is_not_trusted(self):
        k = self.io_clicked()
        k["ride"]["start_at"] = time.time()
        self.tick(k)
        self.assertEqual(self.sent, [])

    def test_stale_status_is_not_trusted(self):
        self.tick(self.io_clicked(status_age=60))
        self.assertEqual(self.sent, [])

    def test_relay_off_is_not_an_io_click(self):
        self.tick(self.io_clicked(kOn="0"))
        self.assertEqual(self.sent, [])

    def test_board_waiting_is_left_alone(self):
        self.tick(self.io_clicked(timeDriveOn="0"))
        self.assertEqual(self.sent, [])

    def test_adc_fault_255_is_not_a_released_pedal(self):
        self.tick(self.io_clicked(adcIn="255"))
        self.assertEqual(self.commands(), [])

    def test_busy_renewal_blocks_rearm(self):
        k = self.io_clicked()
        M.renew_busy["90000001"] = time.time() + 10
        self.addCleanup(M.renew_busy.pop, "90000001", None)
        self.tick(k)
        self.assertEqual(self.sent, [])

    def test_switched_off_by_config(self):
        with mock.patch.dict(M.S, {"rearm_pedal_max": 0}):
            self.tick(self.io_clicked())
        self.assertEqual(self.sent, [])

    def test_board_clicking_after_every_start_is_rearmed_at_most_twice(self):
        k = self.io_clicked()
        for _ in range(4):
            k["status"]["timeDriveOn"] = "1"          # фронт I/O снова, без гостя
            k["status_at"] = time.time() + 2
            k["ride"]["rearm_at"] = 0
            self.tick(k)
        self.assertEqual(self.commands().count("Stop"), M.REARM_MAX)
        self.assertEqual(sum("больше не перевзвожу" in s for s in self.logs), 1)

    def test_ride_closed_while_asking_status_sends_no_stop(self):
        k = self.io_clicked()

        def ws_send(kart, obj):
            self.sent.append(obj)
            self.board(k, obj)
            if obj.get("Command") == "Status":
                k["ride"] = dict(M.IDLE)      # маршал закрыл заезд
            return True
        with mock.patch.object(M, "ws_send", ws_send):
            self.tick(k)
        self.assertEqual(self.commands(), [])


class TickerCallsRearmTest(unittest.TestCase):
    """Сторож заездов зовёт rearm_tick, но не в тот тик, где плановое продление."""

    def setUp(self):
        G.RaceTest.setUp(self)
        self.calls = []
        for name, fake in (("rearm_tick", lambda k, r, now: self.calls.append("rearm")),
                           ("ride_renew", lambda k: self.calls.append("renew"))):
            p = mock.patch.object(M, name, fake)
            p.start()
            self.addCleanup(p.stop)

    fake_ws_send = G.RaceTest.fake_ws_send

    def run_one_tick(self, kart):
        class Done(Exception):
            pass

        def sleep(_s, n=[0]):
            n[0] += 1
            if n[0] > 1:
                raise Done()
        with mock.patch.object(M, "all_karts", lambda: [kart]), \
                mock.patch.object(M, "time", mock.Mock(time=time.time, sleep=sleep)):
            try:
                M.ride_ticker()
            except Done:
                pass

    def kart(self, chunk_in):
        now = time.time()
        ride = dict(M.IDLE, phase="ride", t0=now, t_paid=now + 900, t_end=now + 960,
                    chunk_end=now + chunk_in)
        return {"id": "90000001", "duuid": "90000001", "ride": ride}

    def test_rearm_checked_mid_chunk(self):
        self.run_one_tick(self.kart(300))
        self.assertEqual(self.calls, ["rearm"])

    def test_planned_renewal_tick_does_not_rearm(self):
        self.run_one_tick(self.kart(5))
        self.assertEqual(self.calls, ["renew"])


if __name__ == "__main__":
    unittest.main()
