#include <stdio.h>

#include "include/mstring.h"
#include "include/mstring_extras.h"

int main(void)
{
    mstring s = mstring_new_from("Hello, World!");
    mstring_output_pretty(0,s,1);
    mstring_delete(&s);
    mstring_output_pretty(0,s,1);
    return 0;
}
