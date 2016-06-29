#include "mesh.h"

#include <stdlib.h>
#include <debug.h>

Mesh *
Mesh_Create()
{
    Mesh * mesh = (Mesh *)malloc(sizeof(Mesh));
    CHECK_MEM(mesh);

    mesh->positions = NULL;
    mesh->normals = NULL;
    mesh->texcoords = NULL;
    mesh->indices = NULL;

    return mesh;

error:
    Mesh_Destroy(mesh);

    return NULL;
}

void
Mesh_Destroy(Mesh * mesh)
{
    if (!mesh)
        return;

    free(mesh->positions);
    free(mesh->normals);
    free(mesh->texcoords);
    free(mesh->indices);
    free(mesh);
}
