# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../../includes/dbg.h"

// grep for words only as log files
// example: logfind foo bar -> looks for any log files with the words foo *and* bar and prints them out
// optional argument -o which will transform parameters to *or* logic
// allowed log files -> loaded from ~/.logfind
//   can be anything the glob function allows -> start with flat list of exact files then add glob
// output matches as scan

int main(int argc, char *argv[]) {
  // tokenize input after executable
  //   skip executable in argv[0]
  //   break up into tokens
  //     array of strings
  //     note if optional by precense of flag as first arg after executable
  // find all log files
  // for each log file
  //   open file
  //   create way to track whether a token has been seen
  //     {
  //        token1: true,
  //        token2: false
  //     } -> hashmap in C..easier way maybe just have a variable for the token and a boolean for token found
  //     reset booleans to false
  //   while not end of file
  //     read / search text for token match using strstr => could potentially implement simple readline OR use readline lib
  //     mark token as matched if match
  //       turn boolean to true
  //     print out line if all tokens matched with AND
  //     print out line if any tokens matched with OR
  return 0;
error:
  return -1;
}
