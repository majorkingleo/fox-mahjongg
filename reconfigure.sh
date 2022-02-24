#!/usr/bin/env bash

# just for automake
git log > ChangeLog
aclocal
automake --add-missing
automake -f
autoconf -f

./configure $*
