#ifndef OBJ_H
#define OBJ_H

#include <geom/vec.h>
#include "material.h"
#include "shape.h"

typedef struct OBJ {
    Shape ** shapes;
    Material ** materials;

} OBJ;

OBJ * OBJ_Create();
void OBJ_Destroy(OBJ * obj);
OBJ * OBJ_Load(const char * filename);

#endif // OBJ_H
