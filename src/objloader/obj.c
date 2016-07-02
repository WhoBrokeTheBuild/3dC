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

    int maxVertCount = 500;
    int vertCount = 0;
    Vec3 * verts = (Vec3 *)malloc(sizeof(Vec3) * maxVertCount);
    CHECK_MEM(verts);

    int maxNormCount = 500;
    int normCount = 0;
    Vec3 * norms = (Vec3 *)malloc(sizeof(Vec3) * maxNormCount);
    CHECK_MEM(norms);

    int maxTexcoordCount = 500;
    int texcoordCount = 0;
    Vec2 * texcoords = (Vec2 *)malloc(sizeof(Vec2) * maxTexcoordCount);
    CHECK_MEM(texcoords);

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

        // Resize if necessary

        if (vertCount >= maxVertCount) {
            maxVertCount *= 2;
            void * tmp = realloc(verts, sizeof(Vec3) * maxVertCount);
            CHECK_MEM(tmp);
            verts = (Vec3 *)tmp;
        }

        if (normCount >= maxNormCount) {
            maxNormCount *= 2;
            void * tmp = realloc(norms, sizeof(Vec3) * maxNormCount);
            CHECK_MEM(tmp);
            norms = (Vec3 *)tmp;
        }

        if (texcoordCount >= maxTexcoordCount) {
            maxTexcoordCount *= 2;
            void * tmp = realloc(texcoords, sizeof(Vec2) * maxTexcoordCount);
            CHECK_MEM(tmp);
            texcoords = (Vec2 *)tmp;
        }

        if (len > 2 && line[0] == 'v' && IS_SPACE(line[1])) {
            line += 2;
            Vec3_Parse(&verts[vertCount++], line);
            continue;
        }

        if (len > 2 && line[0] == 'v' && line[1] == 'n') {
            line += 2;
            Vec3_Parse(&norms[normCount++], line);
            continue;
        }

        if (len > 2 && line[0] == 'v' && line[1] == 't') {
            line += 2;
            Vec2_Parse(&texcoords[texcoordCount++], line);
            continue;
        }
    }

    // Shrink to just what we need

    verts = (Vec3 *)realloc(verts, sizeof(Vec3) * vertCount);
    norms = (Vec3 *)realloc(norms, sizeof(Vec3) * normCount);
    texcoords = (Vec2 *)realloc(texcoords, sizeof(Vec2) * texcoordCount);

    printf("Vertices %d\n", vertCount);
    for (int i = 0; i < vertCount; ++i) {
        Vec3_Print(&verts[i]);
    }
    printf("Normals %d\n", normCount);
    for (int i = 0; i < normCount; ++i) {
        Vec3_Print(&norms[i]);
    }
    printf("TexCoords %d\n", texcoordCount);
    for (int i = 0; i < texcoordCount; ++i) {
        Vec2_Print(&texcoords[i]);
    }

    free(verts);
    free(norms);
    free(texcoords);

    fclose(fp);
    return obj;

error:
    free(verts);
    free(norms);
    free(texcoords);

    fclose(fp);
    OBJ_Destroy(obj);

    return NULL;
}
