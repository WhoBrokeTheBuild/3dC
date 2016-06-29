#ifndef OBJ_H
#define OBJ_H

#include "geom/vec.h"

typedef struct Material {
    char * name;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    Vec3 transmittance;
    Vec3 emission;
    float shininess;
    float ior; // index of reflection
    float dissolve; // 1 = opaque, 0 = fully transparent
    // illumination model (see http://www.fileformat.info/format/material/)
    int illum;

    char * ambient_texname; // map_Ka
    char * diffuse_texname; // map_Kd
    char * specular_texname; // map_Ks
    char * specular_highlight_texname; // map_Ns
    char * bump_texname; // map_bump, bump
    char * displacement_texname; // disp
    char * alpha_texname; // map_d

} Material;

Material * Material_create();
void Material_destroy(Material * matl);
Material * Material_load(const char * filename);

typedef struct Mesh {
    Vec3 * positions;
    Vec3 * normals;
    Vec2 * texcoords;
    unsigned int * indices;

} Mesh;

Mesh * Mesh_create();
void Mesh_destroy(Mesh * mesh);

typedef struct Shape {
    char * name;
    Mesh * mesh;

} Shape;

Shape * Shape_create();
void Shape_destroy(Shape * shape);

typedef struct OBJ {
    Shape ** shapes;
    Material ** materials;

} OBJ;

OBJ * OBJ_create();
void OBJ_destroy(OBJ * obj);
OBJ * OBJ_load(const char * filename);

#endif // OBJ_H
