#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STRING_IMPLEMENTATION
#include <stdint.h>
#include "include/string.h"

#define STRING_EXTRAS_IMPLEMENTATION
#include "include/string_extras.h"



int main(void)
{
    string_t s = string_new(1);
    s.data[0] = '\t';
    string_output_pretty(0, s, 1);
    string_delete(&s);
    return 0;
}
