#ifndef SHAPE_H
#define SHAPE_H

#include "mesh.h"

typedef struct Shape {
    char * name;
    Mesh * mesh;

} Shape;

Shape * Shape_Create();
void Shape_Destroy(Shape * shape);

#endif // SHAPE_H
