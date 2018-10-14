#include <stdio.h>

typedef enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_STRING
} VariantType;

struct Variant {
  VariantType type;
  union {
    int as_integer;
    float as_float;
    char *as_string;
  } data;
};

typedef struct Variant Variant;

void Variant_print(Variant *var) {
  switch(var->type) {
    case TYPE_INT:
      printf("INT: %d, MEM: %p\n", var->data.as_integer, &var->data.as_integer);
      break;
    case TYPE_FLOAT:
      printf("FLOAT: %f, MEM: %p\n", var->data.as_float, &var->data.as_float);
      break;
    case TYPE_STRING:
      printf("STRING: %s, MEM: %p\n", var->data.as_string, &var->data.as_string);
      break;
    default:
      printf("UNKNOWN TYPE: %d\n", var->type);
  }
}

int main(int argc, char *argv[]) {
  Variant a_int = { .type = TYPE_INT, .data.as_integer = 100 };
  Variant a_float = { .type = TYPE_FLOAT, .data.as_float = 100.34 };
  Variant a_string = { .type = TYPE_STRING, .data.as_string = "YO DUDE!" };

  Variant_print(&a_int);
  Variant_print(&a_float);
  Variant_print(&a_string);

  a_int.data.as_integer = 200;
  a_int.data.as_float = 100.0;
  printf("int as float %f\n", a_int.data.as_float);
  a_float.data.as_float = 2.345;
  a_string.data.as_string = "Hi There.";

  Variant_print(&a_int);
  Variant_print(&a_float);
  Variant_print(&a_string);

  return 0;
}
