#include <stdio.h>
#include <string.h>

#include "include/mstring.h"
#include "include/mstring_extras.h"


struct tests_array
{
    int length;
    int (**tests)(void); // 1 fail // 0 success
};

#define TA_MAKER(tests) \
    (struct tests_array){ \
        .length = sizeof(tests) / sizeof((tests)[0]), \
        .tests = (tests) \
    }

#define TEST_FAIL(msg, ...) do { printf("FAIL: " msg "\n"); __VA_ARGS__; return 1; } while(0)

#define TEST_SUCCESS(...) do { __VA_ARGS__; return 0; } while(0)


void test(struct tests_array ta)
{
    int successes = 0;
    int fails = 0;

    for (int i = 0; i< ta.length; i++)
    {
        int r = ta.tests[i]();
        if (r == 0) successes++;
        else fails++;
    }

    printf("total: %d\n", ta.length);
    printf("successes: %d\n",successes);
    printf("fails: %d\n", fails);
}

int t1()
{
    const char* ca = "Hello, World!";
    mstring a = mstring_new_from_cstring(ca);
    if (mstring_size(a) != strlen(ca))
        TEST_FAIL("mstring_size failed",
            mstring_delete(&a));

    TEST_SUCCESS(mstring_delete(&a));
}

int t2()
{
    TEST_SUCCESS();
}

int main(void)
{
    int (*tests[])() = {&t1,&t2};
    test(TA_MAKER(tests));

    return 0;
}
