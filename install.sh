#!/bin/bash

# Install search binary to /usr/local/bin
cmake --install build

# Clean up build directory
rm -rf build

rm -rf ./search
