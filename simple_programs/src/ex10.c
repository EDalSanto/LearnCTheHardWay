# include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("ERROR: you need 1 arg\n");
    // this is how to abort a program
    return 1;
  }

  int i = 0;
  for (i = 0; argv[1][i] != '\0'; i++) {
    char letter = argv[1][i];

    switch (letter) {
      // jumps to each case
      case 'a':
      case 'A':
        printf("%d: 'A'\n", i);
        break;

      case 'e':
      case 'E':
        printf("%d: 'E'\n", i);
        break;

      default:
        printf("%d %s is Not A or E", i, letter):
    }
  }

  return 0;
}
