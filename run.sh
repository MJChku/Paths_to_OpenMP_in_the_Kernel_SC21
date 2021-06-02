#!/bin/bash
rm -dr build/*
cp do_cmake build/
cd build
./do_cmake
make
