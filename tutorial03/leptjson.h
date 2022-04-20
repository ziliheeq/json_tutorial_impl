#ifndef LEPT_H__
#define LEPT_H__
#define lept_set_null(v) lept_free(v)

#include <stdlib.h>

#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)
/* all json type */
typedef enum {
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

/* json node [tree] */
typedef struct {
    union 
    {
        struct { char* s; size_t len; } s; /* 字符串 */
        double n;  /* 数字 */
    } u;
    lept_type type;
} lept_value;

/* response status */
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR,
    LEPT_PARSE_NUMBER_TOO_BIG,
    LEPT_PARSE_MISS_QUOTATION_MARK,
    LEPT_PARSE_INVALID_STRING_ESCAPE,
    LEPT_PARSE_INVALID_STRING_CHAR
};

/* api 01 parse json */
int lept_parse(lept_value* v, const char* json);
/* api 02 access result , get type */
lept_type lept_get_type(const lept_value* v);
/* get number value */
double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

#define lept_set_null(v) lept_free(v)

void lept_free(lept_value* v);

#endif