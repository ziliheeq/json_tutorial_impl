#include "leptjson.h"
#include <assert.h>
#include <stdlib.h>

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)
#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch) ((ch) >= '1' && (ch) <= '9')

typedef struct {
    const char* json;
} lept_context;


/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void lept_parse_whitespace(lept_context* c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}


static int lept_parse_literal(lept_context* c, lept_value* v,
const char* literal, lept_type type) {
    size_t i;
    EXPECT(c, literal[0]);
    for (i = 0; literal[i+1]; i++) {
        if (c->json[i] != literal[i+1])
            return LEPT_PARSE_INVALID_VALUE;
    } 
    c->json += i;
    v->type = type;
    return LEPT_PARSE_OK;
}


static int lept_parse_number(lept_context* c, lept_value* v) {
    const char* p = c->json;
    /* 负号 '-' */
    if (*p == '-') p++;
    /* 整数 */
    if (*p == '0') p++;
    else {
        if (!ISDIGIT1TO9(*p)) return LEPT_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);
    }

    /* 小数 */
    if (*p == '.' ) {
        p++;
        if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);
    }

    /* 指数 */
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);

    }

    v->n = strtod(c->json, NULL);
    v->type = LEPT_NUMBER;
    c->json = p;

    return LEPT_PARSE_OK;
}

/* value = null / false / true */
/* 提示：下面代码没处理 false / true，将会是练习之一 */
static int lept_parse_value(lept_context* c, lept_value* v)
{
    switch (*c->json)
    {
        case 't': return lept_parse_literal(c, v, "true", LEPT_TRUE);
        case 'f': return lept_parse_literal(c, v, "false", LEPT_FALSE);
        case 'n': return lept_parse_literal(c, v, "null", LEPT_NULL);
        default:  return lept_parse_number(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
    }
}


int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    int ret;

    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*c.json != '\0')
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
    }

    return ret;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

double lept_get_number(const lept_value* v) {
    assert(v != NULL && v->type == LEPT_NUMBER);
    return v->n;
}