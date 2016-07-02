#include "util.h"

#include <stdlib.h>
#include <assert.h>
#include <debug.h>

bool
TryParseFloat(float * tmp, const char * str, char ** endptr)
{
    assert(tmp != NULL);
    assert(str != NULL);

    errno = 0;
    *tmp = (float)strtod(str, endptr);
    CHECK(errno == 0, "Float parsing failed");

    return true;

error:
    *tmp = 0.0f;
    return false;
}

float
ParseFloat(const char * str, char ** endptr)
{
    assert(str != NULL);

    float tmp;
    TryParseFloat(&tmp, str, endptr);
    return tmp;
}

long int
GetFileSize(FILE * fp)
{
    CHECK(fp, "File isn't open");

    fseek(fp, 0L, SEEK_END);
    long int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;

error:

    return -1;
}
