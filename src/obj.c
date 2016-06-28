#include "obj.h"

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

OBJ*
OBJ_Create(int vertCount)
{
    OBJ* obj = (OBJ*)malloc(sizeof(OBJ));
    CHECK_MEM(obj);

    obj->vertices = (Vec3*)malloc(sizeof(Vec3) * vertCount);
    CHECK_MEM(obj->vertices);

    obj->normals = (Vec3*)malloc(sizeof(Vec3) * vertCount);
    CHECK_MEM(obj->vertices);

    obj->texCoords = (Vec2*)malloc(sizeof(Vec2) * vertCount);
    CHECK_MEM(obj->vertices);

    return obj;

error:
    free(obj);
    free(obj->vertices);
    free(obj->normals);
    free(obj->texCoords);

    return NULL;
}

void
OBJ_Destroy(OBJ* obj)
{
    if (!obj)
        return;

    free(obj->vertices);
    free(obj->normals);
    free(obj->texCoords);
    free(obj);
}

OBJ*
OBJ_Load(const char* filename)
{
    FILE* fp = NULL;
    OBJ* obj = NULL;

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
