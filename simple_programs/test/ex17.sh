#!/bin/sh

# exit if any subcommand or pipeline returns a non-zero status
set -e

# re-compile
make

# create db
./bin/ex17 db.dat c 100 512

# create some reasons
./bin/ex17 db.dat s 1 Eddie eddie@gmail.com
./bin/ex17 db.dat s 2 Michelle michelle@gmail.com

# get them
./bin/ex17 db.dat g 1
./bin/ex17 db.dat g 2

# find em
./bin/ex17 db.dat f name Eddie

# list em
./bin/ex17 db.dat l

# delete em
./bin/ex17 db.dat d 1
./bin/ex17 db.dat d 2

# list em
./bin/ex17 db.dat l

# clean up
rm db.dat
