#!/bin/sh

# recompile
make

# setup some test data
touch logfile.log
echo "search_term1 no_match1 search_term2" > logfile.log

# run
./logfind search_term1
./logfind search_term2
./logfind search_term1 search_term2

# clean up
rm logfile.log
make clean
