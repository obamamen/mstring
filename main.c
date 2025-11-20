#include <stdio.h>

#include "include/mstring.h"
#include "include/mstring_extras.h"

int main(void)
{
    mstring a = mstring_new_from_cstring(
        "123");

    mstring_output_pretty(0,a);
    mstring_resize(&a, 10);
    mstring_output_pretty(0,a);
    mstring_resize(&a, 1);
    mstring_output_pretty(0,a);

    mstring_delete(&a);

    return 0;
}
