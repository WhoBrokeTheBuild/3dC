#include "obj.h"

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

Material*
Material_create()
{
    Material* matl = (Material*)malloc(sizeof(Material));
    CHECK_MEM(matl);

    matl->name = NULL;
    matl->ambient = Vec3Zero;
    matl->diffuse = Vec3Zero;
    matl->specular = Vec3Zero;
    matl->transmittance = Vec3Zero;
    matl->emission = Vec3Zero;
    matl->shininess = 1.0f;
    matl->ior = 1.0f;
    matl->dissolve = 1.0f;
    matl->illum = 0;
    matl->ambient_texname = NULL;
    matl->diffuse_texname = NULL;
    matl->specular_texname = NULL;
    matl->specular_highlight_texname = NULL;
    matl->bump_texname = NULL;
    matl->displacement_texname = NULL;
    matl->alpha_texname = NULL;

    return matl;

error:
    Material_destroy(matl);

    return NULL;
}

void
Material_destroy(Material* matl)
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

Material*
Material_load(const char* filename)
{
    FILE* fp = NULL;
}

Mesh*
Mesh_create()
{
    Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
    CHECK_MEM(mesh);

    mesh->positions = NULL;
    mesh->normals = NULL;
    mesh->texcoords = NULL;
    mesh->indices = NULL;

    return mesh;

error:
    Mesh_destroy(mesh);

    return NULL;
}

void
Mesh_destroy(Mesh* mesh)
{
    if (!mesh)
        return;

    free(mesh->positions);
    free(mesh->normals);
    free(mesh->texcoords);
    free(mesh->indices);
    free(mesh);
}

Shape*
Shape_create()
{
    Shape* shape = (Shape*)malloc(sizeof(Shape));
    CHECK_MEM(shape);

    shape->name = NULL;
    shape->mesh = Mesh_create();

    return shape;

error:
    Shape_destroy(shape);

    return NULL;
}

void
Shape_destroy(Shape* shape)
{
    if (!shape)
        return;

    free(shape->name);
    Mesh_destroy(shape->mesh);
    free(shape);
}

OBJ*
OBJ_create(int vertCount)
{
    OBJ* obj = (OBJ*)malloc(sizeof(OBJ));
    CHECK_MEM(obj);

    return obj;

error:
    OBJ_destroy(obj);

    return NULL;
}

void
OBJ_destroy(OBJ* obj)
{
    if (!obj)
        return;

    free(obj);
}

OBJ*
OBJ_load(const char* filename)
{
    FILE* fp = NULL;
    OBJ* obj = NULL;

    fp = fopen(filename, "r");
    CHECK(!feof(fp), "Failed to open file %s", filename);

    obj = OBJ_create(10);
    CHECK_MEM(obj);

    fclose(fp);
    return obj;

error:
    fclose(fp);
    OBJ_Destroy(obj);

    return NULL;
}
