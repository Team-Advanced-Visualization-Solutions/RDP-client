#!/bin/bash
# Install RDP-client to /opt/RDP-client

set -e

BUILD_DIR="${1:-build}"
if [ ! -f "$BUILD_DIR/client/X11/rdp-client" ]; then
    echo "Error: rdp-client binary not found in $BUILD_DIR"
    echo "Run first: mkdir build && cd build && cmake .. && cmake --build ."
    exit 1
fi

# Install to /opt/RDP-client
echo "Installing RDP-client to /opt/RDP-client ..."
sudo cmake --install "$BUILD_DIR"

# Create symlink
echo "Creating symlink /usr/local/bin/rdp-client ..."
sudo ln -sf /opt/RDP-client/bin/rdp-client /usr/local/bin/rdp-client

# Verify
echo ""
echo "Installation complete!"
echo "---"
/opt/RDP-client/bin/rdp-client --version
echo "---"
echo "Usage: rdp-client /v:<server> /u:<user>"
