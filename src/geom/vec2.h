#ifndef VEC2_H
#define VEC2_H

#include <stdbool.h>
#include <util/dynarr.h>

typedef union Vec2 {
    float data[2];
    struct {
        float a, b;
    };
    struct {
        float x, y;
    };
    struct {
        float s, t;
    };

} Vec2;

extern const Vec2 Vec2_ZERO;

DYNARR_DEF(Vec2, Vec2);

void Vec2_Print(const Vec2 * vec);
void Vec2_Parse(Vec2 * vec, const char * str);
Vec2 Vec2_GetParse(const char * str);

bool Vec2_Equals(const Vec2 * vecA, const Vec2 * vecB);

float Vec2_Length(const Vec2 * vec);
float Vec2_Distance(const Vec2 * vecA, const Vec2 * vecB);

void Vec2_AddVec2(Vec2 * vecA, const Vec2 * vecB);
void Vec2_AddScalar(Vec2 * vecA, float scalar);
Vec2 Vec2_GetAddVec2(const Vec2 * vecA, const Vec2 * vecB);
Vec2 Vec2_GetAddScalar(const Vec2 * vec, float scalar);

void Vec2_SubVec2(Vec2 * vecA, const Vec2 * vecB);
void Vec2_SubScalar(Vec2 * vecA, float scalar);
Vec2 Vec2_GetSubVec2(const Vec2 * vecA, const Vec2 * vecB);
Vec2 Vec2_GetSubScalar(const Vec2 * vec, float scalar);

float Vec2_Dot(const Vec2 * vecA, const Vec2 * vecB);

void Vec2_Normalize(Vec2 * vec);
Vec2 Vec2_GetNormalize(const Vec2 * vec);

#endif // VEC2_H
