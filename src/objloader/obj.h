#ifndef OBJ_H
#define OBJ_H

#include <stdbool.h>
#include <geom/vec.h>
#include <objloader/mesh.h>
#include <objloader/material.h>

struct Material;

typedef struct OBJ {
    Mesh * meshes;
    Material * materials;

} OBJ;

bool OBJ_Init(OBJ * this);
void OBJ_Term(OBJ * this);

bool OBJ_Load(OBJ * this, const char * filename);

#endif // OBJ_H
