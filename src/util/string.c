#include "string.h"

#include <string.h>

DYNARR_IMP(Str, char *, NULL);

char *
StrDuplicate(const char * str, size_t maxLen)
{
    size_t len;
    char * ret;

    if (!str)
        return (char *)NULL;

    len = strlen(str);
    if (maxLen < len)
        len = maxLen;

    ret = malloc(len + 1);
    memcpy(ret, str, len);
    ret[len] = '\0';
    return ret;
}
