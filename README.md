# RDP-client

Современный X11 RDP-клиент на базе движка FreeRDP 3.x (RHEL, CentOS, Fedora, Ubuntu, Debian, ALT Linux) — очищенный, переработанный и сфокусированный на одной цели: быстрые и надёжные удалённые рабочие столы под Linux.

> **Релиз:** 1.0.2 · **Дата:** 2026-11-03 · **Разработчик:** a.silaev · **Git tag:** `v1.0.1`

## Что это?

RDP-client — упрощённый форк FreeRDP, из которого удалены сервер, альтернативные клиенты (SDL, Wayland, Windows, macOS, Android, iOS) и тяжёлые инструменты. Остаётся только X11-клиент с ядром протокола и необходимыми виртуальными каналами.

## Возможности

- **Нативный X11-клиент** — работает на любом Linux/BSD-десктопе с X11
- **Режим keep-alive** — предотвращает блокировку сессии по таймауту (`/keepalive[:N]`)
- **Метаданные сборки** — каждый бинарник содержит дату/время сборки и имя сборщика
- **Чистое версионирование** — никаких суффиксов `dev0` и хешей git в `--version`
- **Современные кодеки** — RFX, NSCodec, GFX pipeline
- **Виртуальные каналы** — cliprdr, disp, rail, rdpgfx, rdpsnd, drive, smartcard, printer и др.
- **FUSE-clipboard** — drag & drop файлов через FUSE3
- **Тёмно-серый фон** — `#333333` вместо чёрного при загрузке
- **Антифликер ресайз** — плавное изменение размера окна

## Установка

Полная инструкция по сборке и установке — в файле **[INSTALL.md](INSTALL.md)**.

Кратко:

```bash
git clone git@github.com:Team-Advanced-Visualization-Solutions/RDP-client.git
cd RDP-client
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
sudo cmake --install .
sudo ln -sf /opt/RDP-client/bin/rdp-client /usr/local/bin/rdp-client
```

По умолчанию устанавливается в `/opt/RDP-client`, чтобы не конфликтовать с системным FreeRDP. Бинарник несёт правильный `RPATH` (`$ORIGIN/../lib64`), `LD_LIBRARY_PATH` не нужен.

## Использование

```bash
# Простое подключение
rdp-client /v:server.example.com /u:username /p:password

# Keep-alive: предотвращает блокировку сессии по таймауту
# Каждые N секунд имитируется микро-движение мыши + нажатие Shift.
# Визуально незаметно, но Windows сбрасывает idle-таймер.
rdp-client /v:server /u:user /p:pass /keepalive

# Быстрая проверка — интервал 60 секунд
rdp-client /v:server /u:user /keepalive:60

# Свой интервал (30 секунд)
rdp-client /v:server /u:user /keepalive:30

# Полный экран на всех мониторах
rdp-client /v:server /u:user /f /multimon

# Перенаправление диска
rdp-client /v:server /u:user /drive:home,/home/user

# Фиксированный размер + графика
rdp-client /v:server /u:user /w:1920 /h:1080 /gfx
```

### Основные параметры

| Параметр | Описание |
|----------|----------|
| `/v:<хост>` | Имя или IP сервера |
| `/u:<user>` | Имя пользователя |
| `/p:<pass>` | Пароль |
| `/f` | Полный экран |
| `/w:<w> /h:<h>` | Произвольное разрешение |
| `/multimon` | Использовать все мониторы |
| `/gfx` | Включить RDPGFX pipeline |
| `/network:<type>` | Тип соединения (broadband, lan и т.д.) |
| `/keepalive[:N]` | Предотвращает блокировку сессии — имитация активности каждые N сек (по умолч. 300) |
| `+clipboard` / `-clipboard` | Включить/отключить буфер обмена |
| `+fonts` | Сглаживание шрифтов |
| `+aero` | Композитный рабочий стол |
| `/drive:<name>,<path>` | Перенаправление локального диска |
| `/sound` | Перенаправление звука |
| `/mic` | Перенаправление микрофона |
| `/printer` | Перенаправление принтера |

## Структура проекта

```
RDP-client/
├── README.md                   # описание проекта
├── INSTALL.md                  # инструкция по сборке и установке
├── INSTALL.sh                  # скрипт установки
├── CMakeLists.txt              # project(RDP-client)
├── client/
│   ├── common/                 # librdp-client-base.so — общая логика клиента
│   └── X11/                    # rdp-client — X11-фронтенд
├── libfreerdp/                 # librdp-core.so — движок RDP-протокола
├── winpr/                      # librdp-winpr.so — совместимость с Windows API
├── channels/                   # плагины виртуальных каналов (только клиент)
├── include/                    # публичные заголовки
└── cmake/                      # модули сборки
```

## Отличия от upstream FreeRDP

| | FreeRDP | RDP-client |
|--|---------|------------|
| Клиенты | X11, SDL, Wayland, Windows, macOS, Android, iOS | **Только X11** |
| Сервер | Полный сервер + прокси | **Удалён** |
| Размер исходников | ~100+ МБ | **~66 МБ** |
| Имя бинарника | `xfreerdp` / `sdl-freerdp` / `wlfreerdp` | **`rdp-client`** |
| Библиотеки | `libfreerdp3.so` / `libfreerdp-client3.so` / `libwinpr3.so` | `librdp-core.so` / `librdp-client-base.so` / `librdp-winpr.so` |
| Строка версии | `FreeRDP version 3.x.x-dev0 (githash)` | `RDP-client 1.x.x (protocol engine 3.x.x, built YYYY-MM-DD HH:MM:SS by user)` |
| Keepalive | Не доступен | `/keepalive` встроен |
| Фон окна | Чёрный | **Тёмно-серый `#333333`** |
| Ресайз | Мерцание | **Антифликер** |

## Версионирование

RDP-client использует собственную сквозную нумерацию релизов (например, **1.0.2**), независимую от upstream FreeRDP. Версия протокольного движка показывается рядом для справки:

```
RDP-client 1.0.2 (protocol engine 3.32.3, built 2026-11-03 11:28:39 by user)
```

## Лицензия

Apache License 2.0 (как и upstream FreeRDP).

## Благодарности

Основано на FreeRDP 3.x — https://github.com/FreeRDP/FreeRDP
