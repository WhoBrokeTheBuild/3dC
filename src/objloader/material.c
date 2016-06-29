#include "material.h"

#include <stdlib.h>
#include <stdio.h>
#include <debug.h>

Material *
Material_Create()
{
    Material * mtl = (Material *)malloc(sizeof(Material));
    CHECK_MEM(mtl);

    mtl->ambient = Vec3_ZERO;
    mtl->diffuse = Vec3_ZERO;
    mtl->specular = Vec3_ZERO;
    mtl->transmittance = Vec3_ZERO;
    mtl->emission = Vec3_ZERO;

    mtl->shininess = 1.0f;
    mtl->ior = 1.0f;
    mtl->dissolve = 1.0f;
    mtl->illum = 0;

    mtl->name = NULL;
    mtl->ambient_texname = NULL;
    mtl->diffuse_texname = NULL;
    mtl->specular_texname = NULL;
    mtl->specular_highlight_texname = NULL;
    mtl->bump_texname = NULL;
    mtl->displacement_texname = NULL;
    mtl->alpha_texname = NULL;

    return mtl;

error:
    Material_Destroy(mtl);

    return NULL;
}

void
Material_Destroy(Material * mtl)
{
    if (!mtl)
        return;

    free(mtl->name);
    free(mtl->ambient_texname);
    free(mtl->diffuse_texname);
    free(mtl->specular_texname);
    free(mtl->specular_highlight_texname);
    free(mtl->bump_texname);
    free(mtl->displacement_texname);
    free(mtl->alpha_texname);
    free(mtl);
}

Material *
Material_Load(const char * filename)
{
    FILE * fp = NULL;
    Material * mtl = NULL;

    fp = fopen(filename, "r");
    CHECK(!feof(fp), "Failed to open file %s", filename);

    mtl = Material_Create(10);
    CHECK_MEM(mtl);

    fclose(fp);
    return mtl;

error:
    fclose(fp);
    Material_Destroy(mtl);

    return NULL;
}
