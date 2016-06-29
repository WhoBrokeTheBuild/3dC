#include "obj.h"

#include <stdlib.h>
#include <stdio.h>
#include <debug.h>

OBJ *
OBJ_Create(int vertCount)
{
    OBJ * obj = (OBJ *)malloc(sizeof(OBJ));
    CHECK_MEM(obj);

    return obj;

error:
    OBJ_Destroy(obj);

    return NULL;
}

void
OBJ_Destroy(OBJ * obj)
{
    if (!obj)
        return;

    free(obj);
}

OBJ *
OBJ_Load(const char * filename)
{
    FILE * fp = NULL;
    OBJ * obj = NULL;

    fp = fopen(filename, "r");
    CHECK(!feof(fp), "Failed to open file %s", filename);

    obj = OBJ_Create(10);
    CHECK_MEM(obj);

    fclose(fp);
    return obj;

error:
    fclose(fp);
    OBJ_Destroy(obj);

    return NULL;
}
