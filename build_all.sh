#!/bin/bash

# Build the global CMake definition in a separate subdirectory.

# terminate on any error
set -e

mkdir -p build
cd build
cmake ..
make


