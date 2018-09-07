// include function declarations for stdin / stdout
# include <stdio.h>
// include assert macro to verify assumptions and print diagnostic messages
# include <assert.h>
// stdlib.h defines variable types, macros and various general functions
# include <stdlib.h>
// string.h provides functions for string manipulation
# include <string.h>

// define a Person struct is like defining a class
struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

// factory function for creating a person struct
struct Person *Person_create(char *name, int age, int height, int weight) {
  // find size of person in bytes and allocating memory for it in RAM, then point the pointer who at that memory location
  struct Person *who = malloc(sizeof(struct Person));
  // evaluate whether expression is true / false
  //   if true, does nothing
  //   if false, displays an error on stderr and aborts program execution
  assert(who != NULL);

  // deference struct pointer and assign attributes -> is shorthand for (*sp)
  // duplicate name and assign to name attribute of who
  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  // return pointer to new person struct
  return who;
}

void Person_destroy(struct Person *who) {
  // evaluate whether expression is true / false
  //   if true, does nothing
  //   if false, displays an error on stderr and aborts program execution
  assert(who != NULL);

  // free up memory that OS allocated for us
  free(who->name);
  free(who);
}

void Person_print(struct Person *who) {
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[]) {
  // make 2 people
  struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
  struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

  // print them out and where in memory
  printf("Joe is at memory location: %p\n", joe);
  Person_print(joe);

  printf("Frank is at memory location: %p\n", frank);
  Person_print(frank);

  // make everyone age 20 years and print again
  // again, deferencing struct point and updating field
  joe->age += 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight += 20;
  Person_print(frank);

  // clean up
  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}
