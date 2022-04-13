#ifndef LEPT_H__
#define LEPT_H__

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
    double n;
    lept_type type;
} lept_value;

/* response status */
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR,
    LEPT_PARSE_NUMBER_TOO_BIG
};

/* api 01 parse json */
int lept_parse(lept_value* v, const char* json);
/* api 02 access result , get type */
lept_type lept_get_type(const lept_value* v);
/* get number value */
double lept_get_number(const lept_value* v);

#endif