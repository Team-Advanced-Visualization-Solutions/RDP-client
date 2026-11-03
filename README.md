# RDP-client

Modern X11 RDP client based on FreeRDP 3.x — stripped down, refactored, and focused on a single goal: fast and reliable remote desktop sessions under Linux.

## What is this?

RDP-client is a streamlined, modernized fork of FreeRDP 3.x focused exclusively on the X11 Linux client. It strips the server, alternative frontends, and heavy tooling — keeping only the core RDP engine and essential virtual channels.

## Versioning

RDP-client uses its own release numbering (e.g. **1.0.0**), independent from upstream FreeRDP. The protocol engine version is shown alongside for reference:

```
RDP-client 1.0.0 (protocol engine 3.32.3, built 2026-11-03 04:50:26 by user)
```

## Features

- **X11 native client** — runs on any Linux/BSD desktop with X11
- **Keep-alive mode** — prevents session idle-lock with `--keepalive <seconds>`
- **Build metadata** — every binary embeds build date/time and builder name
- **Clean versioning** — no git suffix noise in `--version`
- **Modern codecs** — RFX, NSCodec, GFX pipeline
- **Virtual channels** — cliprdr, disp, rail, rdpgfx, rdpsnd, drive, smartcard, printer, and more
- **FUSE clipboard** — drag & drop files via FUSE3

## Building

### Requirements

- CMake ≥ 3.13
- C compiler (GCC or Clang)
- OpenSSL ≥ 1.1.1
- X11 development libraries (`libX11-devel`, `libXext-devel`, `libXcursor-devel`, `libXrender-devel`, `libXfixes-devel`, `libXi-devel`, `libXrandr-devel`)
- Optional but recommended: FFmpeg, PulseAudio/ALSA, libusb-1.0, libcups, FUSE3

### Quick build

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

### Result (in build directory)

```
client/X11/rdp-client           # main binary
client/common/librdp-client-base.so
libfreerdp/librdp-core.so
winpr/libwinpr/librdp-winpr.so
```

### Install (self-contained to `/opt/RDP-client`)

By default the project installs to `/opt/RDP-client` so it never conflicts with your distribution's FreeRDP packages. The binary carries the correct `RPATH` (`$ORIGIN/../lib64`), so no `LD_LIBRARY_PATH` tricks are needed — it finds its own libraries automatically.

```bash
cd build
sudo cmake --install .
```

After installation:

```bash
/opt/RDP-client/bin/rdp-client --version
```

Add to your `PATH`:

```bash
export PATH="/opt/RDP-client/bin:$PATH"
```

Or symlink if you prefer:

```bash
sudo ln -s /opt/RDP-client/bin/rdp-client /usr/local/bin/rdp-client
```

You can also stage the install into another directory (e.g. for packaging):

```bash
cmake --install . --prefix /tmp/staging/opt/RDP-client
```

## Usage

```bash
# Basic connection
./rdp-client /v:server.example.com /u:username /p:password

# Keep session alive every 5 minutes
./rdp-client /v:server /u:user /p:pass --keepalive

# Custom interval (30 seconds)
./rdp-client /v:server /u:user --keepalive:30

# Fullscreen with all monitors
./rdp-client /v:server /u:user /f /multimon

# Drive redirection
./rdp-client /v:server /u:user /drive:home,/home/user
```

### Key options

| Option | Description |
|--------|-------------|
| `/v:<host>` | Server hostname or IP |
| `/u:<user>` | Username |
| `/p:<pass>` | Password |
| `/f` | Fullscreen |
| `/w:<w> /h:<h>` | Custom resolution |
| `/multimon` | Use all monitors |
| `/gfx` | Enable RDPGFX pipeline |
| `/network:<type>` | Connection type (broadband, lan, etc.) |
| `--keepalive[:N]` | Send idle-proof ping every N seconds (default 300) |
| `+clipboard` / `-clipboard` | Enable/disable clipboard |
| `+fonts` | Smooth fonts |
| `+aero` | Desktop composition |

## Project structure

```
RDP-client/
├── client/
│   ├── common/          # librdp-client-base.so — shared client logic
│   └── X11/             # rdp-client binary + X11 frontend
├── libfreerdp/          # librdp-core.so — RDP protocol engine
├── winpr/               # librdp-winpr.so — Windows API compatibility layer
├── channels/            # Virtual channel plugins (client only)
├── include/             # Public headers
└── cmake/               # Build system modules
```

## Differences from upstream FreeRDP

| | FreeRDP | RDP-client |
|--|---------|------------|
| Clients | X11, SDL, Wayland, Windows, macOS, Android, iOS | **X11 only** |
| Server | Full server + proxy | **Removed** |
| Size | ~100+ MB sources | **~66 MB** |
| Binary name | `xfreerdp` / `sdl-freerdp` / `wlfreerdp` | **`rdp-client`** |
| Libraries | `libfreerdp3.so` / `libfreerdp-client3.so` / `libwinpr3.so` | `librdp-core.so` / `librdp-client-base.so` / `librdp-winpr.so` |
| Version string | `FreeRDP version 3.x.x-dev0 (githash)` | `RDP-client 1.x.x (protocol engine 3.x.x, built YYYY-MM-DD HH:MM:SS by user)` |
| Keepalive | Not available | `--keepalive` built-in |

## License

Apache License 2.0 (same as upstream FreeRDP).

## Acknowledgments

Based on FreeRDP 3.x — https://github.com/FreeRDP/FreeRDP
