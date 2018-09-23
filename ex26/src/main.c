#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <glob.h>

#include "../../includes/dbg.h"

#define FLAG_INITIATOR '-'

/* Grep-like utility
 * example: logfind foo bar -> looks for any log files with the words foo *and* bar and prints them out
 * optional argument -o which will transform parameters to *or* logic
 * */

/* helpers */

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
  char **log_files;
  FILE *stream;
  char *line, *search_term, *current_file_name;
  size_t nread;
  int more_lines_to_read, or_flag, i, k, matching_search_terms, num_search_terms;

  // make sure enough args passed
  if (argc < 2) {
    sentinel("Must pass at least one argument to program");
  }
  // parse args for flags and search terms count
  num_search_terms = 0;
  or_flag = 0;
  for (i = 1; i < argc; i++) {
    if (strings_equal(argv[i], "-o")) {
      or_flag = 1;
    } else {
      num_search_terms += 1;
    }
  }

  // find all log files utilizing glob
  glob_t glob_buf;
  glob_buf.gl_offs = 0;
  glob("*.log", GLOB_DOOFFS, NULL, &glob_buf);
  debug("matched files %d", (int)glob_buf.gl_pathc);
  log_files = glob_buf.gl_pathv;

  // check each log file for match
  for (i = 0; i < glob_buf.gl_pathc; i++) {
    current_file_name = log_files[i];
    // relative to the current working directory when the executable is run
    stream = fopen(current_file_name, "r");
    more_lines_to_read = getline(&line, &nread, stream) != -1;
    while (more_lines_to_read) {
      // reset match statuses to false
      matching_search_terms = 0;

      // search through all search tokens for match
      for (k = 1; k < argc; k++) {
        if (line_is_flag(argv[k])) continue;

        // see if current search term is match
        search_term = argv[k];
        if (substr_match(line, search_term)) {
          // mark token as matched if match
          matching_search_terms += 1;
        }
      }

      // print out match
      if (matching_search_terms == num_search_terms) {
        // num_search_termsprint out line if all tokens matched with AND
        debug("FILE: %s, LINE: %s", current_file_name, line);
      } else if (or_flag && matching_search_terms) {
        // print out line if any tokens matched with OR
        debug("FILE: %s, LINE: %s", current_file_name, line);
      }

      // read next line
      more_lines_to_read = getline(&line, &nread, stream) != -1;
    }
  }

  return 0;
error:
  return -1;
}

/* IDEAS FOR IMPROVEMENT
 *
 * store search term somehow..
   create way to track whether a token has been seen
  {
     token1: true,
     token2: false
  } -> implement hashmap in C for probably better scalability and clarity but worst memory
 *
 * Add better tests for output matching https://stackoverflow.com/questions/26144614/how-to-test-code-that-writes-to-stdout
 * */
