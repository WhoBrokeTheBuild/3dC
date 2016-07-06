#ifndef MESH_H
#define MESH_H

#include <opengl.h>
#include <geom/vec.h>
#include <util/dynarr.h>

typedef struct Mesh {
    char * name;
    int vertCount;

    GLuint vertBuffer;
    GLuint normBuffer;
    GLuint texcoordBuffer;
    GLuint vertArray;

} Mesh;

extern Mesh Mesh_EMPTY;

DYNARR_DEF(Mesh, Mesh);

bool Mesh_Init(
    Mesh * this, const char * name, int vertCount, Vec3 * verts, Vec3 * norms, Vec3 * texcoords);
void Mesh_Term(Mesh * this);

#endif // MESH_H
