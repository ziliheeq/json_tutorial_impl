#include "lept.h"
#include <assert.h>

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
} lept_context;


/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void lept_parse_whitespace(lept_context* c)
{
    const char *p = c->json;
    while (*p == ' ' | *p == '\t' | *p == '\n' | *p == '\r')
        p++;
    c->json = p;
}


static int lept_parse_null(lept_context* c, lept_type* v)
{
    EXPECT(c, 'n');
    
}

/* value = null / false / true */
/* 提示：下面代码没处理 false / true，将会是练习之一 */
static int lept_parse_value(lept_context* c, lept_type* v)
{
    switch (*c->json)
    {
    case 'n': return lept_parse_null(c, v);
    default:
        break;
    }
}

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);

    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespece(&c);
    return lept_parse_value(&c, v);
}