#!/bin/sh

meson setup build src
cd build
ninja
mv 42sh ../
cd ..
