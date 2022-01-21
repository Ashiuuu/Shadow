#!/bin/sh

rm tree.dot
meson setup build
meson setup -Ddoc=true build --reconfigure
meson compile -C build doxygen_doc
ninja -C build
mv build/42sh .
mv build/test_suite .
