#!/bin/sh

meson setup build src
cd build
ninja
cd ..
