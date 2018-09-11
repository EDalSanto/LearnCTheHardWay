# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

void die(const char *message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

// typedef creates a fake type, in this case for a function pointer
// function pointer points to a function that returns an int and takes 2 ints as arguments
typedef int (*compare_cb) (int a, int b);

// create function pointer to sorting algo
typedef int *(sort_cb) (int *numbers, int count, compare_cb cmp);

/**
 * A Classic Bubble Sort function that uses the compare_cb to to do the sorting
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp) {
  int temp = 0;
  int i = 0;
  int j = 0;
  int *target = malloc(count * sizeof(int));

  if (!target)
    die("Memory Error.");

  memcpy(target, numbers, count * sizeof(int));

  for (i = 0; i < count; i++) {
    for (j = 0; j < count -1; j++) {
      if (cmp(target[j], target[j + 1]) > 0) {
        temp = target[j + 1];
        target[j + 1] = target[j];
        target[j] = temp;
      }
    }
  }
  return target;
}

int sorted_order(int a, int b) {
  return (a > b) - (a < b);
}

int reverse_order(int a, int b) {
  return (a < b) - (a > b);
}

int strange_order(int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

/**
 * Test sorting by sorting then printing
 */
void test_sorting(sort_cb sort, int *numbers, int count, compare_cb cmp) {
  int i = 0;
  int *sorted = sort(numbers, count, cmp);

  if (!sorted)
    die("Failed to sort as requested.");

  for (i = 0; i < count; i++) {
    printf("%d\n", sorted[i]);
  }
  printf("\n");

  free(sorted);

  // convert pointer to compare_cb to unsigned char pointer
  unsigned char *data = (unsigned char *) cmp;
  // printing out raw assembler byte code of function
  for (i = 0; i < 25; i++) {
    printf("%02x:", data[i]);
  }

  printf("\n");
}

void my_func() {

}

int main(int argc, char *argv[]) {
  if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if (!numbers) die("Memory Error");

  for (i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }

  // functions by default return address of stating point or entry point
  // so passing function name here is essentially a function pointer (like in JS / Python)
  test_sorting(bubble_sort, numbers, count, sorted_order);
  test_sorting(bubble_sort, numbers, count, reverse_order);
  test_sorting(bubble_sort, numbers, count, strange_order);
  // wrong func for compare_cb
  // passing void function parameter when expecting compare_cb type
  //test_sorting(numbers, count, my_func);
  // pass null -> segfault when trying to read memory at pointer
  // test_sorting(numbers, count, NULL);

  free(numbers);

  return 0;
}
