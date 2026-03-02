#!/bin/bash

# Exit on any error
set -e

echo "--- Building Search v1.0 ---"

# 1. Create a build directory and compile
mkdir -p build
cd build
cmake ..
make

echo "--- Installing Binary ---"

# 2. Install the binary to /usr/local/bin
sudo cp search /usr/local/bin/search
sudo chmod +x /usr/local/bin/search

echo "--- Installing Configuration ---"

# 3. Install the config and license file to the current user's home
CONFIG_DIR="$HOME/.config/search"
mkdir -p "$CONFIG_DIR"
cp ../src/config.lua "$CONFIG_DIR/config.lua"
cp ../src/license.txt "$CONFIG_DIR/license.txt"

echo "----------------------------------------"
echo "Done! You can now run 'search' in your terminal."
echo "Config installed to: $CONFIG_DIR/config.lua"
echo "License installed to: $CONFIG_DIR/license.txt"
