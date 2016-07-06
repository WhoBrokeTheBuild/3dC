#ifndef OBJ_H
#define OBJ_H

#include <stdbool.h>
#include <geom/vec.h>

bool Material_Init(Material * this);
void Material_Term(Material * this);

bool Mesh_Init(Mesh * this);
void Mesh_Term(Mesh * this);

bool Shape_Init(Shape * this);
void Shape_Term(Shape * this);

bool LoadOBJ(const char * filename);

#endif // OBJ_H
