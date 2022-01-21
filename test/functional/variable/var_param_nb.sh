#!/bin/sh

set "il y a 1 seule variable élément !"
echo $#

set "deux" "élément"
echo $#

set "il" "y" "a" "six" "élément" "!"
echo $#

