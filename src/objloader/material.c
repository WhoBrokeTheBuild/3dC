#include "material.h"

#include <stdlib.h>
#include <stdio.h>
#include <debug.h>

Material *
Material_Create()
{
    Material * matl = (Material *)malloc(sizeof(Material));
    CHECK_MEM(matl);

    matl->ambient = Vec3_ZERO;
    matl->diffuse = Vec3_ZERO;
    matl->specular = Vec3_ZERO;
    matl->transmittance = Vec3_ZERO;
    matl->emission = Vec3_ZERO;

    matl->shininess = 1.0f;
    matl->ior = 1.0f;
    matl->dissolve = 1.0f;
    matl->illum = 0;

    matl->name = NULL;
    matl->ambient_texname = NULL;
    matl->diffuse_texname = NULL;
    matl->specular_texname = NULL;
    matl->specular_highlight_texname = NULL;
    matl->bump_texname = NULL;
    matl->displacement_texname = NULL;
    matl->alpha_texname = NULL;

    return matl;

error:
    Material_Destroy(matl);

    return NULL;
}

void
Material_Destroy(Material * matl)
{
    if (!matl)
        return;

    free(matl->name);
    free(matl->ambient_texname);
    free(matl->diffuse_texname);
    free(matl->specular_texname);
    free(matl->specular_highlight_texname);
    free(matl->bump_texname);
    free(matl->displacement_texname);
    free(matl->alpha_texname);
    free(matl);
}

Material *
Material_Load(const char * filename)
{
    FILE * fp = NULL;
    Material * matl = NULL;

    fp = fopen(filename, "r");
    CHECK(!feof(fp), "Failed to open file %s", filename);

    matl = Material_Create(10);
    CHECK_MEM(matl);

    fclose(fp);
    return matl;

error:
    fclose(fp);
    Material_Destroy(matl);

    return NULL;
}
