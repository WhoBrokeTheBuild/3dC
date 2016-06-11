#include "util.h"

long int GetFileSize(FILE * fp)
{
    CHECK(fp, "File isn't open");

    fseek(fp, 0L, SEEK_END);
    long int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;

error:

    return -1;
}
