#!/bin/sh

rm tree.dot
meson setup build
if [ $1 -eq "doc" ]; then 
    meson setup -Ddoc=true build --reconfigure
    meson compile -C build doxygen_doc;
else meson setup build;
fi 
ninja -C build
mv build/42sh .
mv build/test_suite .
