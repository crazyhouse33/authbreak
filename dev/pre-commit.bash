#!/bin/bash
set -e
#Run test
echo building again from scratch
cd ../build
rm -rf -- *
cmake .. 
cmake --build . --target all
cmake --build . --target test



