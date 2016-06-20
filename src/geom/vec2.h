#ifndef VEC2_H
#define VEC2_H

#include <stdbool.h>

typedef union Vec2
{
    float data[2];
    struct
    {
        float a, b;
    };
    struct
    {
        float x, y;
    };
    struct
    {
        float s, t;
    };

} Vec2;

void Vec2_Print(Vec2* vec);

bool Vec2_Equals(Vec2* vecA, Vec2* vecB);

float Vec2_Length(Vec2* vec);
float Vec2_Distance(Vec2* vecA, Vec2* vecB);

void Vec2_AddVec2(Vec2* vecA, Vec2* vecB);
void Vec2_AddScalar(Vec2* vecA, float scalar);
Vec2 Vec2_GetAddVec2(Vec2* vecA, Vec2* vecB);
Vec2 Vec2_GetAddScalar(Vec2* vec, float scalar);

void Vec2_SubVec2(Vec2* vecA, Vec2* vecB);
void Vec2_SubScalar(Vec2* vecA, float scalar);
Vec2 Vec2_GetSubVec2(Vec2* vecA, Vec2* vecB);
Vec2 Vec2_GetSubScalar(Vec2* vec, float scalar);

void Vec2_Dot(Vec2* vecA, Vec2* vecB);
Vec2 Vec2_GetDot(Vec2* vecA, Vec2* vecB);

void Vec2_Normalize(Vec2* vec);
Vec2 Vec2_GetNormalize(Vec2* vec);

#endif // VEC2_H
