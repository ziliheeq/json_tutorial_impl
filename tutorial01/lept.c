#include "lept.h"
#include <assert.h>

typedef struct {
    const char* json;
} lept_context;

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
}