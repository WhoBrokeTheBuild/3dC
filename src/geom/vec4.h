#ifndef VEC4_H
#define VEC4_H

#include <stdbool.h>

typedef union Vec4
{
    float data[4];
    struct
    {
        float a, b, c, d;
    };
    struct
    {
        float x, y, z, w;
    };

} Vec4;

void Vec4_Print(Vec4* vec);

bool Vec4_Equals(Vec4* vecA, Vec4* vecB);

float Vec4_Length(Vec4* vec);
float Vec4_Distance(Vec4* vecA, Vec4* vecB);

void Vec4_AddVec4(Vec4* vecA, Vec4* vecB);
void Vec4_AddScalar(Vec4* vecA, float scalar);
Vec4 Vec4_GetAddVec4(Vec4* vecA, Vec4* vecB);
Vec4 Vec4_GetAddScalar(Vec4* vec, float scalar);

void Vec4_SubVec4(Vec4* vecA, Vec4* vecB);
void Vec4_SubScalar(Vec4* vecA, float scalar);
Vec4 Vec4_GetSubVec4(Vec4* vecA, Vec4* vecB);
Vec4 Vec4_GetSubScalar(Vec4* vec, float scalar);

void Vec4_Dot(Vec4* vecA, Vec4* vecB);
Vec4 Vec4_GetDot(Vec4* vecA, Vec4* vecB);

void Vec4_Normalize(Vec4* vec);
Vec4 Vec4_GetNormalize(Vec4* vec);

#endif // VEC4_H