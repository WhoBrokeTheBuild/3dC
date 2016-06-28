#ifndef OBJ_H
#define OBJ_H

#include "geom/vec.h"

typedef struct OBJ
{
    Vec3* vertices;
    Vec3* normals;
    Vec2* texCoords;
} OBJ;

OBJ* OBJ_Create(int vertCount);
void OBJ_Destroy(OBJ* obj);

OBJ* OBJ_Load(const char* filename);

#endif // OBJ_H
