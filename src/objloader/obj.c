#include "obj.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <debug.h>
#include <util/string.h>

#define LINE_BUFFER_SIZE (4096)
#define MAX_SHAPE_NAME_LEN (256)

#define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
#define IS_DIGIT(x) ((unsigned int)((x) - '0') < (unsigned int)10)
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

int
FixIndex(int index, int vertCount)
{
    if (index > 0)
        return index - 1;
    if (index == 0)
        return 0;
    return vertCount + index; // negative value = relative
}

bool
OBJ_Init(OBJ * this)
{
    CHECK(this != NULL, "OBJ is null");

    this->meshes = NULL;
    this->materials = NULL;

    return true;

error:
    OBJ_Term(this);

    return false;
}

void
OBJ_Term(OBJ * this)
{
    if (!this)
        return;
}

bool
OBJ_Load(OBJ * this, const char * filename)
{
    OBJ_Init(this);

    FILE * fp = NULL;

    fp = fopen(filename, "r");
    CHECK(!feof(fp), "Failed to open file %s", filename);

    char * shapeName = NULL;

    DynArrMesh meshes;
    DynArrMesh_Init(&meshes);

    DynArrVec3 allVerts;
    DynArrVec3_Init(&allVerts);
    DynArrVec3 allNorms;
    DynArrVec3_Init(&allNorms);
    DynArrVec2 allTexcoords;
    DynArrVec2_Init(&allTexcoords);

    DynArrVec3 curVerts;
    DynArrVec3_Init(&curVerts);
    DynArrVec3 curNorms;
    DynArrVec3_Init(&curNorms);
    DynArrVec2 curTexcoords;
    DynArrVec2_Init(&curTexcoords);

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

        if (line[0] == 'v' && IS_SPACE(line[1])) {
            line += 2;
            DynArrVec3_Append(&allVerts, Vec3_GetParse(line));
            continue;
        }

        if (line[0] == 'v' && line[1] == 'n' && IS_SPACE(line[2])) {
            line += 2;
            DynArrVec3_Append(&allNorms, Vec3_GetParse(line));
            continue;
        }

        if (line[0] == 'v' && line[1] == 't' && IS_SPACE(line[2])) {
            line += 2;
            DynArrVec2_Append(&allTexcoords, Vec2_GetParse(line));
            continue;
        }

        if (line[0] == 'f' && IS_SPACE(line[1])) {
            line += 2;
            line += strspn(line, " \t");

            int vertInd = -1;
            int normInd = -1;
            int texcoordInd = -1;

            // handles i, i/j/k, i//k, i/j
            while (!IS_NEW_LINE(line[0])) {
                vertInd = FixIndex(atoi(line), allVerts.size);

                // i
                line += strcspn(line, "/ \t\r");
                if (line[0] != '/') {
                    break;
                }
                ++line;

                // i//k
                if (line[0] == '/') {
                    ++line;
                    normInd = FixIndex(atoi(line), allNorms.size);
                    break;
                }

                // i/j/k or i/j
                texcoordInd = FixIndex(atoi(line), allTexcoords.size);
                line += strcspn(line, "/ \t\r");
                if (line[0] != '/') {
                    break;
                }

                // i/j/k
                ++line; // skip '/'
                FixIndex(atoi(line), allNorms.size);
                break;
            }
        }

        if (line[0] == 'o' || line[0] == 'g') {
            line += 2;
            line += strspn(line, " \t");

            if (shapeName) {
                free(shapeName);
                shapeName = NULL;
            }

            shapeName = StrDuplicate(line, MAX_SHAPE_NAME_LEN);
            printf("Shape: %s\n", shapeName);

            continue;
        }

        printf("Warning: Ignored line '%s'\n", line);
    }

    free(shapeName);

    // Shrink to just what we need
    DynArrVec3_Shrink(&allVerts);
    DynArrVec3_Shrink(&allNorms);
    DynArrVec2_Shrink(&allTexcoords);

    printf("Vertices %d\n", allVerts.size);
    // for (int i = 0; i < allVerts.size; ++i) {
    //    Vec3_Print(&(allVerts.data[i]));
    //}
    printf("Normals %d\n", allNorms.size);
    // for (int i = 0; i < allNorms.size; ++i) {
    //    Vec3_Print(&(allNorms.data[i]));
    //}
    printf("TexCoords %d\n", allTexcoords.size);
    // for (int i = 0; i < allTexcoords.size; ++i) {
    //    Vec2_Print(&(allTexcoords.data[i]));
    //}

    DynArrVec3_Free(&curVerts);
    DynArrVec3_Free(&curNorms);
    DynArrVec2_Free(&curTexcoords);

    DynArrVec3_Free(&allVerts);
    DynArrVec3_Free(&allNorms);
    DynArrVec2_Free(&allTexcoords);

    DynArrMesh_Free(&meshes);

    fclose(fp);
    return true;

error:
    DynArrVec3_Free(&curVerts);
    DynArrVec3_Free(&curNorms);
    DynArrVec2_Free(&curTexcoords);

    DynArrVec3_Free(&allVerts);
    DynArrVec3_Free(&allNorms);
    DynArrVec2_Free(&allTexcoords);

    fclose(fp);
    OBJ_Term(this);
    return false;
}
