# Прошивка платы: разобранный код

| Файл | Что |
|---|---|
| `decompiled/vendor_40201010_4020ad30.c` | код производителя (157 функций), псевдо-C из Ghidra; ключевые функции названы по смыслу |
| `strings_vendor.tsv` | строки прошивки с адресами, включая русские сообщения |
| `tools/` | скрипты, которыми делался разбор |

Как прошивка работает — `ai/03-proshivka.md`. Пароли и адреса вычищены
(`*_REDACTED`). Сами образы прошивки — только в закрытом репозитории
FireDrift_Access: в них пароль Wi-Fi.

## Карта функций

| Адрес | Имя | Роль |
|---|---|---|
| 4020a764 | `setup` | запуск: файлы, конфиг, Wi-Fi, пульт, датчики, время, SSDP, веб, задачи, вебсокет |
| 40208014 | `main_loop` | планировщик, веб-сервер, вебсокеты |
| 4020a0a8 | `throttle_tick_30ms` | педаль → газ (формула в `ai/03-proshivka.md`) |
| 4020951c | `sensors_tick_377ms` | телеметрия, начало заезда по фронту I/O |
| 40208154 | `ride_tick_1s` | таймеры заезда, парковки, ожидания 600 с, местный режим, 12 ч |
| 40208e74 | `ws_event` | команды сервера: Start, Stop, MaxSpeed, Status, Update |
| 40209468 / 40208044 | `adc_read` / `dac_write` | PCF8591 по I2C, без проверки ошибок |
| 40201788 | `rc_detect_noise_on_gpio` | режим пульта по «дребезгу» GPIO14 при загрузке |
| 40207cdc | `http_ota_update` | перепрошивка по ссылке |
| 40206818 | `http_routes_setup` | HTTP-адреса платы |

## Как повторить разбор

1. **Ghidra 12.2** (нужна Java 21+). На ноутбуке владельца: `C:\Users\wallg\Tools\ghidra_12.2_PUBLIC`.
   - Если Ghidra запускается из приложения Claude (пакет MSIX), Windows
     подменяет `%APPDATA%`, и модуль Felix падает с «The data file must be inside
     the data dir». Лечится в `support\launch.properties`:
     `VMARGS=-Dapplication.settingsdir=C:/Users/<имя>/Tools/ghidra-home/settings` и
     `VMARGS=-Dapplication.cachedir=C:/Users/<имя>/Tools/ghidra-home/cache`.
   - В `Ghidra\Processors\Xtensa\data\languages\xtensa.cspec` соглашение по
     умолчанию заменено на `__call0` (так работает ESP8266); без этого декомпилятор
     путает, какие регистры переживают вызов.
2. **Образ → ELF:** `py tools/bin2elf.py kart_dump.bin kart_app.elf` (программа с 0x1000,
   сегменты irom0/iram/dram, плюс пустые блоки для .bss, ROM и регистров).
3. **Импорт и анализ:** `support\analyzeHeadless.bat <папка> kart -import kart_app.elf`.
4. **Выгрузки:**
   - `-process kart_app.elf -noanalysis -postScript ExportMap.java <out>` — функции и
     константы из литералов;
   - `-postScript DecompileRange.java 40201010 4020ad30 <out>` — псевдо-C диапазона.
5. **Строки:** `py tools/strings_map.py kart_dump.bin strings.tsv`, связь с
   функциями — `py tools/join_strings.py <папка> <маркеры…>`. Русские сообщения
   прошивки — в UTF-8, ASCII-поиск их не видит.

Вычистка секретов делалась по адресам строк в образе, а не по значениям: пароли
не попадают даже в скрипты.
