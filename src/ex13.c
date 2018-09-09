# include <stdio.h>

int main(int argc, char *argv[]) {
  int num_states = 4;

  char *states[] = {
   "California", "Oregon",
   "Washington", "Texas"
  };

  for (int i = 0; i < num_states; i++) {
    printf("state %d: %s\n", i, states[i]);
  }

  return 0;
}
