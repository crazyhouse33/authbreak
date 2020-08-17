#!/bin/bash
set -e
#Run test
echo building again from scratch
cd ../build
rm -rf -- *
cmake .. -G Ninja
cmake --build . --target all
cmake --build . --target test



