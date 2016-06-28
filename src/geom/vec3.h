#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>

typedef union Vec3
{
    float data[3];
    struct
    {
        float a, b, c;
    };
    struct
    {
        float x, y, z;
    };

} Vec3;

void Vec3_Print(const Vec3* vec);

bool Vec3_Equals(const Vec3* vecA, const Vec3* vecB);

float Vec3_Length(const Vec3* vec);
float Vec3_Distance(const Vec3* vecA, const Vec3* vecB);

void Vec3_AddVec3(Vec3* vecA, const Vec3* vecB);
void Vec3_AddScalar(Vec3* vecA, float scalar);
Vec3 Vec3_GetAddVec3(const Vec3* vecA, const Vec3* vecB);
Vec3 Vec3_GetAddScalar(const Vec3* vec, float scalar);

void Vec3_SubVec3(Vec3* vecA, const Vec3* vecB);
void Vec3_SubScalar(Vec3* vecA, float scalar);
Vec3 Vec3_GetSubVec3(const Vec3* vecA, const Vec3* vecB);
Vec3 Vec3_GetSubScalar(const Vec3* vec, float scalar);

void Vec3_Cross(Vec3* vecA, const Vec3* vecB);
Vec3 Vec3_GetCross(const Vec3* vecA, const Vec3* vecB);

void Vec3_Dot(Vec3* vecA, const Vec3* vecB);
Vec3 Vec3_GetDot(const Vec3* vecA, const Vec3* vecB);

void Vec3_Normalize(Vec3* vec);
Vec3 Vec3_GetNormalize(const Vec3* vec);

#endif // VEC3_H
