#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>

bool TryParseFloat(float * tmp, const char * str, char ** endptr);
float ParseFloat(const char * str, char ** endptr);

long int GetFileSize(FILE * fp);

#endif // UTIL_H
