#!/bin/bash
# Скрипт установки RDP-client в /opt/RDP-client

set -e

BUILD_DIR="${1:-build}"
if [ ! -f "$BUILD_DIR/client/X11/rdp-client" ]; then
    echo "Ошибка: бинарник rdp-client не найден в $BUILD_DIR"
    echo "Сначала соберите: mkdir build && cd build && cmake .. && cmake --build ."
    exit 1
fi

# Установка в /opt/RDP-client
echo "Установка RDP-client в /opt/RDP-client ..."
sudo cmake --install "$BUILD_DIR"

# Создание symlink
echo "Создание ссылки /usr/local/bin/rdp-client ..."
sudo ln -sf /opt/RDP-client/bin/rdp-client /usr/local/bin/rdp-client

# Проверка
echo ""
echo "Установка завершена!"
echo "---"
/opt/RDP-client/bin/rdp-client --version
echo "---"
echo "Использование: rdp-client /v:<сервер> /u:<пользователь>"
