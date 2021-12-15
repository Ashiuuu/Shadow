#!/bin/sh

meson setup build
ninja -C build
mv build/42sh .
mv build/test_suite .
