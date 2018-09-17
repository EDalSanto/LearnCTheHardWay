#include <stdio.h>
#include "../../includes/ex22.h"
#include "../../includes/dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age()
{
    return THE_AGE;
}

void set_age(int age)
{
   THE_AGE = age;
}

double update_ratio(double new_ratio)
{
    double *foo = NULL;
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

void print_size()
{
    log_info("I think size is: %d", THE_SIZE);
}
