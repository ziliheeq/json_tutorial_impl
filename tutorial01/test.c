#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

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

<<<<<<< HEAD

static void test_parse_null() {
=======
static void test_parse_null(){
>>>>>>> 81a40f2189f618876cbfc533eb81b9853d6a19df
    lept_value v;
    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
<<<<<<< HEAD
    printf("v->type = %d\n", v.type);
    printf("LEPT_NULL = %d\n", lept_get_type(&v));
}

static void test_parse_expect_value() {
    lept_value v;

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, " "));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
    
}

void test_parse() {
    test_parse_null();
=======

    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "oknul"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_except_value() {
    lept_value v;
    v.type = LEPT_FALSE;

    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, ""));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, " "));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse() {
    test_parse_null();
    test_parse_except_value();
>>>>>>> 81a40f2189f618876cbfc533eb81b9853d6a19df
}

int main()
{
<<<<<<< HEAD
    /* EXPECT_EQ_BASE(0, 11, 20, "%d");*/
    test_parse();
=======
    test_parse();
    printf("test_count= %d\n", test_count);
>>>>>>> 81a40f2189f618876cbfc533eb81b9853d6a19df
    printf("test_pass = %d\n", test_pass);
    printf("pass percent = %3.2f%%\n", test_pass * 100.0 / test_count);
    return 0;
}