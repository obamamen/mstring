#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STRING_IMPLEMENTATION
#include <stdint.h>
#include "include/string.h"

#define STRING_EXTRAS_IMPLEMENTATION
#include "include/string_extras.h"



void print_s(const string_t s)
{
    printf("{\n");
    printf("    .data= [");
    string_output_ca(0, s.data, s.capacity, ", ", 1);
    printf("]\n");
    printf("    .size= %d\n",s.size);
    printf("    .capacity= %d\n",s.capacity);
    printf("}\n");
}

int main(void)
{
    string_t s = string_new(1);
    s.data[0] = '\t';
    print_s(s);
    string_delete(&s);
    return 0;
}
