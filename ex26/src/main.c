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

// helpers
int strings_equal(const char *str1, const char *str2) {
  return strcmp(str1, str2) == 0;
}

int substr_match(char *line, char *substr) {
  return (int)strstr(line, substr);
}

int line_is_flag(const char *line) {
  return line[0] == FLAG_INITIATOR;
}

int main(int argc, char *argv[]) {
  FILE *stream;
  char *line, *search_term;
  size_t nread;
  int more_lines_to_read, or_flag, i, matching_search_terms, num_search_terms;

  // make sure enough args passed
  if (argc < 2) {
    sentinel("Must pass at least one argument to program");
  }
  // parse args for flags and search terms count
  num_search_terms = 0;
  for (i = 1; i < argc; i++) {
    if (strings_equal(argv[i], "-o")) {
      or_flag = 1;
    } else {
      num_search_terms += 1;
    }
  }
  // find all log files utilizing glob
  // for each log file
  //   open file
  //   read each line

  // relative to the current working directory when the executable is run
  stream = fopen("./logfile.log", "r");
  more_lines_to_read = getline(&line, &nread, stream) != -1;
  while (more_lines_to_read) {
    // reset match statuses to false
    matching_search_terms = 0;

    // search through all search tokens for match
    for (i = 1; i < argc; i++) {
      if (line_is_flag(argv[i])) continue;

      // see if current search term is match
      search_term = argv[i];
      if (substr_match(line, search_term)) {
        // mark token as matched if match
        matching_search_terms += 1;
      }
    }

    // print out match
    if (!or_flag && (matching_search_terms == num_search_terms)) {
      // num_search_termsprint out line if all tokens matched with AND
      debug("%s", line);
    } else if (or_flag && matching_search_terms) {
      // print out line if any tokens matched with OR
      debug("%s", line);
    }

    // read next line
    more_lines_to_read = getline(&line, &nread, stream) != -1;
  }
  return 0;
error:
  return -1;
}

/* IDEAS FOR IMPROVEMENT */
// store search term somehow..
//   create way to track whether a token has been seen
//  {
//     token1: true,
//     token2: false
//  } -> implement hashmap in C for probably better scalability and clarity but worst memory
