#!/usr/bin/sh

set -xe

CC=g++
CFLAGS="-Wall -Wextra"

$CC $CFLAGS -o matriz matriz.cpp
