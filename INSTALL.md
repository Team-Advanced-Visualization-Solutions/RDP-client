# Установка RDP-client

## Системные требования

- **CMake** ≥ 3.13
- **C-компилятор** (GCC или Clang)
- **OpenSSL** ≥ 1.1.1 (devel)
- **X11** development libraries:
  - libX11-devel
  - libXext-devel
  - libXcursor-devel
  - libXrender-devel
  - libXfixes-devel
  - libXi-devel
  - libXrandr-devel

- **Опционально:** FFmpeg, PulseAudio/ALSA, libusb-1.0, libcups, FUSE3

### Установка зависимостей (CentOS/RHEL/Fedora)

```bash
sudo dnf install cmake gcc openssl-devel \
    libX11-devel libXext-devel libXcursor-devel \
    libXrender-devel libXfixes-devel libXi-devel libXrandr-devel \
    libXdamage-devel libXinerama-devel \
    pulseaudio-libs-devel cups-devel fuse3-devel
```

### Установка зависимостей (ALT Linux / Simply Linux)

```bash
su -
apt-get install cmake gcc-c++ libssl-devel \
    libX11-devel libXext-devel libXcursor-devel \
    libXrender-devel libXfixes-devel libXi-devel libXrandr-devel \
    libXdamage-devel libXinerama-devel \
    pulseaudio-devel libcups-devel fuse3-devel
```

### Установка зависимостей (Debian/Ubuntu)

```bash
sudo apt install cmake build-essential libssl-dev \
    libx11-dev libxext-dev libxcursor-dev \
    libxrender-dev libxfixes-dev libxi-dev libxrandr-dev \
    libxdamage-dev libxinerama-dev \
    libpulse-dev libcups2-dev libfuse3-dev
```

---

## Быстрая установка (последняя версия из main)

```bash
git clone git@github.com:Team-Advanced-Visualization-Solutions/RDP-client.git
cd RDP-client
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
sudo cmake --install .
sudo ln -sf /opt/RDP-client/bin/rdp-client /usr/local/bin/rdp-client
```

---

## Установка конкретного релиза

```bash
git clone git@github.com:Team-Advanced-Visualization-Solutions/RDP-client.git
cd RDP-client
git checkout v1.0.0          # <-- конкретная версия
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
sudo cmake --install .
sudo ln -sf /opt/RDP-client/bin/rdp-client /usr/local/bin/rdp-client
```

---

## Проверка

```bash
rdp-client --version
# RDP-client 1.0.0 (protocol engine 3.32.3, built YYYY-MM-DD HH:MM:SS by user)
```

---

## Первый запуск

```bash
# Простое подключение
rdp-client /v:server.example.com /u:username /p:password

# С keepalive (предотвращает блокировку сессии)
rdp-client /v:server /u:user /p:pass /keepalive

# Полный экран + все мониторы
rdp-client /v:server /u:user /f /multimon
```

---

## Удаление

```bash
sudo rm -rf /opt/RDP-client
sudo rm -f /usr/local/bin/rdp-client
```

---

## Сборка без установки (staging)

```bash
cd build
cmake --install . --prefix /tmp/staging/opt/RDP-client
# Готовый каталог для переноса на другую машину
```
