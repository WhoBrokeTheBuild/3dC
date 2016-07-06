#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <stdlib.h>
#include <util/dynarr.h>

char * StrDuplicate(const char * str, size_t maxLen);

DYNARR_DEF(Str, char *);

#endif // UTIL_STRING_H
