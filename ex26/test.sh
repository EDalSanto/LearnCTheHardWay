#!/bin/sh

# recompile
make

# run
./logfind clean

# clean up
make clean
