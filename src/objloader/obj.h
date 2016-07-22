#ifndef OBJ_H
#define OBJ_H

#include <stdbool.h>
#include <geom/vec.h>
#include <util/types.h>
#include <util/string.h>

typedef struct {
    char * name;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    Vec3 transmittance;
    Vec3 emission;
    float shininess;
    float ior; // index of refraction
    float dissolve; // 1 == opaque; 0 == fully transparent
    // illumination model (see http://www.fileformat.info/format/material/)
    int illum;

    int dummy; // Suppress padding warning.

    char * ambient_texname; // map_Ka
    char * diffuse_texname; // map_Kd
    char * specular_texname; // map_Ks
    char * specular_highlight_texname; // map_Ns
    char * bump_texname; // map_bump, bump
    char * displacement_texname; // disp
    char * alpha_texname; // map_d
} Material;

extern const Material Material_EMPTY;

typedef struct {
    DynArrVec3 verts;
    DynArrVec3 normals;
    DynArrVec2 texcoords;
    DynArrInt indices;
    DynArrInt num_vertices; // The number of vertices per face. Up to 255.
    DynArrInt material_ids; // per-face material ID
} Mesh;

extern const Mesh Mesh_EMPTY;

typedef struct {
    char * name;
    Mesh mesh;
} Shape;

extern const Shape Shape_EMPTY;

DYNARR_DEF(Material, Material);
DYNARR_DEF(Shape, Shape);
DYNARR_DEF(Mesh, Mesh);

bool Material_Init(Material * this);
void Material_Term(Material * this);

bool Mesh_Init(Mesh * this);
void Mesh_Term(Mesh * this);

bool Shape_Init(Shape * this);
void Shape_Term(Shape * this);

bool LoadOBJ(const char * filename);

#endif // OBJ_H
