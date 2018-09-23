#!/bin/sh

# recompile
make

# setup some test data
touch logfile.log
echo "search_term1 no_match1 search_term2" > logfile.log

# run
./logfind search_term1 # match on 1
./logfind search_term2 # match on 2
./logfind search_term1 foo # don't match
./logfind -o search_term1 foo # match or

# clean up
rm logfile.log
make clean
