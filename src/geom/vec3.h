#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>
#include <util/dynarr.h>

typedef union Vec3 {
    float data[3];
    struct {
        float a, b, c;
    };
    struct {
        float x, y, z;
    };

} Vec3;

extern Vec3 Vec3_ZERO;

DYNARR_DEF(Vec3, Vec3);

Vec3 Vec3_Create(float x, float y, float z);

void Vec3_Print(const Vec3 * vec);
void Vec3_Parse(Vec3 * vec, const char * str);
Vec3 Vec3_GetParse(const char * str);

bool Vec3_Equals(const Vec3 * vecA, const Vec3 * vecB);

float Vec3_Length(const Vec3 * vec);
float Vec3_Distance(const Vec3 * vecA, const Vec3 * vecB);

void Vec3_AddVec3(Vec3 * vecA, const Vec3 * vecB);
void Vec3_AddScalar(Vec3 * vecA, float scalar);
Vec3 Vec3_GetAddVec3(const Vec3 * vecA, const Vec3 * vecB);
Vec3 Vec3_GetAddScalar(const Vec3 * vec, float scalar);

void Vec3_SubVec3(Vec3 * vecA, const Vec3 * vecB);
void Vec3_SubScalar(Vec3 * vecA, float scalar);
Vec3 Vec3_GetSubVec3(const Vec3 * vecA, const Vec3 * vecB);
Vec3 Vec3_GetSubScalar(const Vec3 * vec, float scalar);

void Vec3_MultScalar(Vec3 * this, float scalar);
Vec3 Vec3_GetMultScalar(const Vec3 * this, float scalar);

void Vec3_Cross(Vec3 * vecA, const Vec3 * vecB);
Vec3 Vec3_GetCross(const Vec3 * vecA, const Vec3 * vecB);

float Vec3_Dot(const Vec3 * vecA, const Vec3 * vecB);

void Vec3_Normalize(Vec3 * vec);
Vec3 Vec3_GetNormalize(const Vec3 * vec);

#endif // VEC3_H
