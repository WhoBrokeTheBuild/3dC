#ifndef UTIL_PARSING_H
#define UTIL_PARSING_H

#include <stdbool.h>

bool TryParseFloat(float * tmp, const char * str, char ** endptr);
float ParseFloat(const char * str, char ** endptr);

#endif // UTIL_PARSING_H
