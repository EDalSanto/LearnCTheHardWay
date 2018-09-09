# include <stdio.h>

int main(int argc, char *argv[]) {
  // create two arrays
  int ages[] = { 23, 43, 12, 89, 12 };
  char *names[] = {
    "Alan", "Frank",
    "Mary", "John", "Lisa"
  };

  // get size of ages
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  for (i = 0; i < count; i++) {
    printf("%s has %d years alive\n", *(names + i), *(ages + i));
  }

  printf("---\n");

  int *cur_age = ages;
  char **cur_name = names;

  // second way using pointers
  for (i = 0; i < count; i++) {
    printf("%s has %d years alive\n", *(cur_name + i), *(cur_age + i));
  }

  printf("---\n");

  // or as arrays
  for (i = 0; i < count; i++) {
    printf("%s has %d years alive\n", cur_name[i], cur_age[i]);
  }

  // command line args with pointers
  char **args = argv;

  for (i = 0; i < argc; i++) {
    printf("arg: %s\n", args[i]);
  }

  // address of ages
  printf("%p\n", &ages);
  // value of ages
  printf("%d\n", *ages);
  // address of names
  printf("%p\n", &names);
  // value of names
  printf("%s\n", *names);
}
