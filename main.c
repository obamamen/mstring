#include <stdio.h>

#include "include/mstring.h"
#include "include/mstring_extras.h"

int main(void)
{
    mstring a = mstring_new_from_cstring(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    mstring_output_pretty(0,a);
    mstring b = mstring_new_from_cstring(
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
    mstring_output_pretty(0,b);
    mstring_append(&a, b);
    mstring_output_pretty(0,a);
    return 0;
}
