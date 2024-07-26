#!/usr/bin/bash

set -xe

CC=gcc
CFLAGS="-Wall -Wextra"

$CC $CFLAGS -o fsm_example fsm_example.c
