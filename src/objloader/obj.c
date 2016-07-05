#include "obj.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>

#define LINE_BUFFER_SIZE (4096)

#define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
#define IS_DIGIT(x) ((unsigned int)((x) - '0') < (unsigned int)10)
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

OBJ *
OBJ_Create()
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

    obj = OBJ_Create();
    CHECK_MEM(obj);

    DynArrVec3 verts;
    DynArrVec3_Init(&verts);

    DynArrVec3 norms;
    DynArrVec3_Init(&norms);

    DynArrVec2 texcoords;
    DynArrVec2_Init(&texcoords);

    char linebuf[LINE_BUFFER_SIZE];
    while (fgets(linebuf, LINE_BUFFER_SIZE, fp) != NULL) {
        char * line = linebuf;
        size_t len = strlen(line);

        if (len > 0 && line[len - 1] == '\n')
            line[--len] = '\0';
        if (len > 0 && line[len - 1] == '\r')
            line[--len] = '\0';

        if (len == 0)
            continue;

        // Skip leading whitespace
        line += strspn(line, " \t");
        CHECK(line, "Parsing line failed '%s'", line);

        if (line[0] == '\0') // Empty Line
            continue;

        if (line[0] == '#') // Comment
            continue;

        if (len > 2 && line[0] == 'v' && IS_SPACE(line[1])) {
            line += 2;
            DynArrVec3_Append(&verts, Vec3_GetParse(line));
            continue;
        }

        if (len > 2 && line[0] == 'v' && line[1] == 'n') {
            line += 2;
            DynArrVec3_Append(&norms, Vec3_GetParse(line));
            continue;
        }

        if (len > 2 && line[0] == 'v' && line[1] == 't') {
            line += 2;
            DynArrVec2_Append(&texcoords, Vec2_GetParse(line));
            continue;
        }
    }

    // Shrink to just what we need
    DynArrVec3_Shrink(&verts);
    DynArrVec3_Shrink(&norms);
    DynArrVec2_Shrink(&texcoords);

    printf("Vertices %d\n", verts.size);
    for (int i = 0; i < verts.size; ++i) {
        Vec3_Print(&(verts.data[i]));
    }
    printf("Normals %d\n", norms.size);
    for (int i = 0; i < norms.size; ++i) {
        Vec3_Print(&(norms.data[i]));
    }
    printf("TexCoords %d\n", texcoords.size);
    for (int i = 0; i < texcoords.size; ++i) {
        Vec2_Print(&(texcoords.data[i]));
    }

    DynArrVec3_Free(&verts);
    DynArrVec3_Free(&norms);
    DynArrVec2_Free(&texcoords);

    fclose(fp);
    return obj;

error:
    DynArrVec3_Free(&verts);
    DynArrVec3_Free(&norms);
    DynArrVec2_Free(&texcoords);

    fclose(fp);
    OBJ_Destroy(obj);

    return NULL;
}
