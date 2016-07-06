#include "mesh.h"

#include <string.h>
#include <stdlib.h>
#include <debug.h>
#include <assert.h>
#include <util/string.h>

Mesh Mesh_EMPTY = {};
#define MAX_SHAPE_NAME_LEN (256)

DYNARR_IMP(Mesh, Mesh, Mesh_EMPTY);

bool
Mesh_Init(
    Mesh * this, const char * name, int vertCount, Vec3 * verts, Vec3 * norms, Vec3 * texcoords)
{
    CHECK(vertCount > 0, "Cannot create a mesh with 0 vertCount");
    CHECK(verts != NULL, "Cannot create a mesh with null verts array");

    this->name = StrDuplicate(name, MAX_SHAPE_NAME_LEN);
    this->vertCount = vertCount;

    glGenVertexArrays(1, &this->vertArray);
    glBindVertexArray(this->vertArray);

    if (verts) {
        glGenBuffers(1, &this->vertBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertBuffer);
        glBufferData(
            GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * this->vertCount, verts, GL_DYNAMIC_DRAW);
    }

    if (norms) {
        glGenBuffers(1, &this->normBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->normBuffer);
        glBufferData(
            GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * this->vertCount, norms, GL_DYNAMIC_DRAW);
    }

    if (texcoords) {
        glGenBuffers(1, &this->texcoordBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->texcoordBuffer);
        glBufferData(
            GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * this->vertCount, texcoords, GL_DYNAMIC_DRAW);
    }

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

    free(this->name);
    this->name = NULL;

    if (this->vertBuffer != 0)
        glDeleteBuffers(1, &this->vertBuffer);

    if (this->normBuffer != 0)
        glDeleteBuffers(1, &this->normBuffer);

    if (this->texcoordBuffer != 0)
        glDeleteBuffers(1, &this->texcoordBuffer);

    if (this->vertArray != 0)
        glDeleteVertexArrays(1, &this->vertArray);

    this->vertBuffer = 0;
    this->normBuffer = 0;
    this->texcoordBuffer = 0;
    this->vertArray = 0;
}
