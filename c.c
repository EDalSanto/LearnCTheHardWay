# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void my_copy(char **line_ptr) {
  strcpy(*line_ptr, "foo fucking bar");
}

int main(int argc, char *argv[]) {
  char *line;

  line = (char*)malloc(100 * sizeof(char));
  my_copy(&line);
  printf("line: %s\n", line);
  free(line);

  return 0;
}
