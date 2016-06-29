#include "shape.h"

#include <stdlib.h>
#include <debug.h>

Shape *
Shape_Create()
{
    Shape * shape = (Shape *)malloc(sizeof(Shape));
    CHECK_MEM(shape);

    shape->name = NULL;
    shape->mesh = Mesh_Create();

    return shape;

error:
    Shape_Destroy(shape);

    return NULL;
}

void
Shape_Destroy(Shape * shape)
{
    if (!shape)
        return;

    free(shape->name);
    Mesh_Destroy(shape->mesh);
    free(shape);
}
