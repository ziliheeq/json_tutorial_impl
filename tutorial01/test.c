#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lept.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++; \
        if (equality) \
            test_pass++; \
        else { \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
            main_ret = 1; \
        } \
    } while(0)

/* encapsulation API, abstruct formal macro for calling */
#define EXPECT_EQ_INT(expect, actual)  EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

int main()
{
    /* EXPECT_EQ_BASE(0, 11, 20, "%d");*/
    EXPECT_EQ_INT(22, 30);
    printf("test_pass = %d\n", test_pass);
    return 0;
}