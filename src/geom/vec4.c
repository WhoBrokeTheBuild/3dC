#include "vec4.h"

#include <stdio.h>
#include <math.h>

Vec4 Vec4_ZERO = { { 0.0f, 0.0f, 0.0f } };

DYNARR_IMP(Vec4, Vec4, Vec4_ZERO);

void
Vec4_Print(const Vec4 * vec)
{
    printf("[ %f %f %f %f ]\n", vec->x, vec->y, vec->z, vec->w);
}

bool
Vec4_Equals(const Vec4 * vecA, const Vec4 * vecB)
{
    return (vecA->x == vecB->x && vecA->y == vecB->y && vecA->z == vecB->z && vecA->w == vecB->w);
}

float
Vec4_Length(const Vec4 * vec)
{
    return sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z) + (vec->w * vec->w));
}

float
Vec4_Distance(const Vec4 * vecA, const Vec4 * vecB)
{
    float x = (vecB->x - vecA->x), y = (vecB->y - vecA->y), z = (vecB->z - vecA->z),
          w = (vecB->w - vecA->w);
    return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

void
Vec4_AddVec4(Vec4 * vecA, const Vec4 * vecB)
{
    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
    vecA->z = vecA->z + vecB->z;
    vecA->w = vecA->w + vecB->w;
}

Vec4
Vec4_GetAddVec4(const Vec4 * vecA, const Vec4 * vecB)
{
    Vec4 tmp = *vecA;
    Vec4_AddVec4(&tmp, vecB);
    return tmp;
}

void
Vec4_AddScalar(Vec4 * vec, float scalar)
{
    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
    vec->z = vec->z + scalar;
    vec->w = vec->w + scalar;
}

Vec4
Vec4_GetAddScalar(const Vec4 * vec, float scalar)
{
    Vec4 tmp = *vec;
    Vec4_AddScalar(&tmp, scalar);
    return tmp;
}

void
Vec4_SubVec4(Vec4 * vecA, const Vec4 * vecB)
{
    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
    vecA->z = vecA->z + vecB->z;
    vecA->w = vecA->w + vecB->w;
}

Vec4
Vec4_GetSubVec4(const Vec4 * vecA, const Vec4 * vecB)
{
    Vec4 tmp = *vecA;
    Vec4_SubVec4(&tmp, vecB);
    return tmp;
}

void
Vec4_SubScalar(Vec4 * vec, float scalar)
{
    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
    vec->z = vec->z + scalar;
    vec->w = vec->w + scalar;
}

Vec4
Vec4_GetSubScalar(const Vec4 * vec, float scalar)
{
    Vec4 tmp = *vec;
    Vec4_SubScalar(&tmp, scalar);
    return tmp;
}

void
Vec4_Dot(Vec4 * vecA, const Vec4 * vecB)
{
    vecA->x = (vecA->x * vecB->x);
    vecA->y = (vecA->y * vecB->y);
    vecA->z = (vecA->z * vecB->z);
    vecA->w = (vecA->w * vecB->w);
}

Vec4
Vec4_GetDot(const Vec4 * vecA, const Vec4 * vecB)
{
    Vec4 tmp = *vecA;
    Vec4_Dot(&tmp, vecB);
    return tmp;
}

void
Vec4_Normalize(Vec4 * vec)
{
    float len = Vec4_Length(vec);
    vec->x /= len;
    vec->y /= len;
    vec->z /= len;
    vec->w /= len;
}

Vec4
Vec4_GetNormalize(const Vec4 * vec)
{
    Vec4 tmp = *vec;
    Vec4_Normalize(&tmp);
    return tmp;
}
