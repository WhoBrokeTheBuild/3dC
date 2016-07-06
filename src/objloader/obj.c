#include "obj.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <debug.h>
#include <util/types.h>
#include <util/string.h>

typedef struct {
    std::string name;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    Vec3 transmittance;
    Vec3 emission;
    float shininess;
    float ior; // index of refraction
    float dissolve; // 1 == opaque; 0 == fully transparent
    // illumination model (see http://www.fileformat.info/format/material/)
    int illum;

    int dummy; // Suppress padding warning.

    char * ambient_texname; // map_Ka
    char * diffuse_texname; // map_Kd
    char * specular_texname; // map_Ks
    char * specular_highlight_texname; // map_Ns
    char * bump_texname; // map_bump, bump
    char * displacement_texname; // disp
    char * alpha_texname; // map_d
} Material;

bool
Material_Init(Material * this)
{
    CHECK(this, "Invalid Material");

    this->name = NULL;
    this->ambient_texname = NULL;
    this->diffuse_texname = NULL;
    this->specular_texname = NULL;
    this->specular_highlight_texname = NULL;
    this->bump_texname = NULL;
    this->displacement_texname = NULL;
    this->alpha_texname = NULL;
    this->ambient = Vec3_ZERO;
    this->diffuse = Vec3_ZERO;
    this->specular = Vec3_ZERO;
    this->transmittance = Vec3_ZERO;
    this->emission = Vec3_ZERO;
    this->illum = 0;
    this->dissolve = 1.f;
    this->shininess = 1.f;
    this->ior = 1.f;

    return true;

error:
    Material_Term(this);
    return false;
}

void
Material_Term(Material * this)
{
    if (!this)
        return;

    free(this->name);
    free(this->ambient_texname);
    free(this->diffuse_texname);
    free(this->specular_texname);
    free(this->specular_highlight_texname);
    free(this->bump_texname);
    free(this->displacement_texname);
    free(this->alpha_texname);
    this->name = NULL;
    this->ambient_texname = NULL;
    this->diffuse_texname = NULL;
    this->specular_texname = NULL;
    this->specular_highlight_texname = NULL;
    this->bump_texname = NULL;
    this->displacement_texname = NULL;
    this->alpha_texname = NULL;
}

typedef struct {
    int vertInd;
    int normInd;
    int texcrdInd;
} VertexIndex;

typedef struct {
    DynArrVec3 positions;
    DynArrVec3 normals;
    DynArrVec3 texcoords;
    DynArrInt indices;
    DynArrInt num_vertices; // The number of vertices per face. Up to 255.
    DynArrInt material_ids; // per-face material ID
} Mesh;

bool
Mesh_Init(Mesh * this)
{
    CHECK(this, "Invalid Mesh");

    DynArrVec3_Init(&this->positions);
    DynArrVec3_Init(&this->normals);
    DynArrVec3_Init(&this->texcoords);
    DynArrInt_Init(&this->indices);
    DynArrInt_Init(&this->num_vertices);
    DynArrInt_Init(&this->material_ids);

    return true;

error:
    Mesh_Term(this);
    return false;
}

void
Mesh_Term(Mesh * this)
{
    if (!this)
        return;

    DynArrVec3_Free(&this->positions);
    DynArrVec3_Free(&this->normals);
    DynArrVec3_Free(&this->texcoords);
    DynArrInt_Free(&this->positions);
    DynArrInt_Free(&this->num_vertices);
    DynArrInt_Free(&this->material_ids);
}

typedef struct {
    char * name;
    Mesh mesh;
} Shape;

bool
Shape_Init(Shape * this)
{
    CHECK(this, "Invalid Shape");

    name = NULL;
    CHECK(Mesh_Init(&this->mesh), "Unable to init Mesh");

    return true;

error:
    Shape_Term(this);
    return false;
}

void
Shape_Term(Shape * this)
{
    if (!this)
        return;

    free(this->name);
    this->name = NULL;
    Mesh_Term(&this->mesh);
}

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
LoadOBJ(const char * filename)
{
    FILE * fp = NULL;

    fp = fopen(filename, "r");
    CHECK(!feof(fp), "Failed to open file %s", filename);

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
            Vec3 tmp = Vec3_GetParse(line);
            continue;
        }

        if (line[0] == 'v' && line[1] == 'n' && IS_SPACE(line[2])) {
            line += 2;
            Vec3 tmp = Vec3_GetParse(line);
            continue;
        }

        if (line[0] == 'v' && line[1] == 't' && IS_SPACE(line[2])) {
            line += 2;
            Vec2 tmp = Vec2_GetParse(line);
            continue;
        }

        if (line[0] == 'f' && IS_SPACE(line[1])) {
            line += 2;
            line += strspn(line, " \t");

            int vertInd = -1;
            int normInd = -1;
            int texcrdInd = -1;

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
                texcrdInd = FixIndex(atoi(line), alltexcrds.size);
                line += strcspn(line, "/ \t\r");
                if (line[0] != '/') {
                    break;
                }

                // i/j/k
                ++line; // skip '/'
                FixIndex(atoi(line), allNorms.size);
                break;
            }

            if (vertInd == -1) {
                // failed
                continue;
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
    DynArrVec2_Shrink(&alltexcrds);

    printf("Vertices %d\n", allVerts.size);
    // for (int i = 0; i < allVerts.size; ++i) {
    //    Vec3_Print(&(allVerts.data[i]));
    //}
    printf("Normals %d\n", allNorms.size);
    // for (int i = 0; i < allNorms.size; ++i) {
    //    Vec3_Print(&(allNorms.data[i]));
    //}
    printf("texcrds %d\n", alltexcrds.size);
    // for (int i = 0; i < alltexcrds.size; ++i) {
    //    Vec2_Print(&(alltexcrds.data[i]));
    //}

    DynArrVec3_Free(&curVerts);
    DynArrVec3_Free(&curNorms);
    DynArrVec2_Free(&curtexcrds);

    DynArrVec3_Free(&allVerts);
    DynArrVec3_Free(&allNorms);
    DynArrVec2_Free(&alltexcrds);

    DynArrMesh_Free(&meshes);

    fclose(fp);
    return true;

error:
    DynArrVec3_Free(&curVerts);
    DynArrVec3_Free(&curNorms);
    DynArrVec2_Free(&curtexcrds);

    DynArrVec3_Free(&allVerts);
    DynArrVec3_Free(&allNorms);
    DynArrVec2_Free(&alltexcrds);

    fclose(fp);
    OBJ_Term(this);
    return false;
}
