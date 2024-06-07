#!/bin/sh

rm -f include/config.h.in~ config.mak configure

echo "Wait please..."
autoreconf -if
