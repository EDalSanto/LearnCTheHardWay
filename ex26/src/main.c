#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../../includes/dbg.h"

#define BUFFER_SIZE 1024
#define FLAG_INITIATOR '-'

// grep for words only as log files
// example: logfind foo bar -> looks for any log files with the words foo *and* bar and prints them out
// optional argument -o which will transform parameters to *or* logic
// allowed log files -> loaded from ~/.logfind
//   can be anything the glob function allows -> start with flat list of exact files then add glob
// output matches as scan

int strings_equal(const char *str1, const char *str2) {
  return strcmp(str1, str2) == 0;
}

int substr_match(char *line, char *substr) {
  return (int)strstr(line, substr);
}

int line_is_flag(const char *line) {
  return line[0] == FLAG_INITIATOR;
}

// function that returns

int main(int argc, char *argv[]) {
  FILE *stream;
  char *line, *search_term;
  char args_matched[BUFFER_SIZE];
  size_t nread;
  int more_lines_to_read, or_flag, i;

  // make sure enough args passed
  if (argc < 2) {
    sentinel("Must pass at least one argument to program");
  }
  // store inputs
  //   skip executable in argv[0]
  for (i = 1; i < argc; i++) {
    // check for -o flag
    if (strings_equal(argv[i], "-o")) {
      or_flag = 1;
    } else {
      search_term = argv[i];
      // store search term somehow..
      //   create way to track whether a token has been seen
      //  {
      //     token1: true,
      //     token2: false
      //  } -> hashmap in C..easier way maybe just have a variable for the token and a boolean for token found
    }
    debug("arg: %s", search_term);
  }
  // find all log files
  // for each log file
  //   open file
  //   read each line

  // relative to the current working directory when the executable is run
  stream = fopen("./Makefile", "r");
  //     reset booleans to false
  more_lines_to_read = getline(&line, &nread, stream) != -1;
  while (more_lines_to_read) {
    // search through all search tokens for match
    for (i = 1; i < argc; i++) {
      if (line_is_flag(argv[i])) continue;

      // see if current search term is match
      search_term = argv[i];
      if (substr_match(line, search_term)) {
        debug("%s", line);
      }
    }
    more_lines_to_read = getline(&line, &nread, stream) != -1;
    //     mark token as matched if match
    //       turn boolean to true
    //     print out line if all tokens matched with AND
    //     print out line if any tokens matched with OR
  }
  return 0;
error:
  return -1;
}
