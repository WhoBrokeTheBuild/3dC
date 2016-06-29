#ifndef MESH_H
#define MESH_H

#include <geom/vec.h>

typedef struct Mesh {
    Vec3 * positions;
    Vec3 * normals;
    Vec2 * texcoords;
    unsigned int * indices;

} Mesh;

Mesh * Mesh_Create();
void Mesh_Destroy(Mesh * mesh);

#endif // MESH_H
