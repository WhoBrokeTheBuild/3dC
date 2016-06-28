#include "vec2.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

void
Vec2_Print(const Vec2* vec)
{
    assert(vec != NULL);

    printf("[ %f %f ]\n", vec->x, vec->y);
}

bool
Vec2_Equals(const Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    return (vecA->x == vecB->x && vecA->y == vecB->y);
}

float
Vec2_Length(const Vec2* vec)
{
    assert(vec != NULL);

    return sqrt((vec->x * vec->x) + (vec->y * vec->y));
}

float
Vec2_Distance(const Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    float x = (vecB->x - vecA->x), y = (vecB->y - vecA->y);
    return sqrt((x * x) + (y * y));
}

void
Vec2_AddVec2(Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
}

Vec2
Vec2_GetAddVec2(const Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec2 tmp = *vecA;
    Vec2_AddVec2(&tmp, vecB);
    return tmp;
}

void
Vec2_AddScalar(Vec2* vec, float scalar)
{
    assert(vec != NULL);

    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
}

Vec2
Vec2_GetAddScalar(const Vec2* vec, float scalar)
{
    assert(vec != NULL);

    Vec2 tmp = *vec;
    Vec2_AddScalar(&tmp, scalar);
    return tmp;
}

void
Vec2_SubVec2(Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
}

Vec2
Vec2_GetSubVec2(const Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec2 tmp = *vecA;
    Vec2_SubVec2(&tmp, vecB);
    return tmp;
}

void
Vec2_SubScalar(Vec2* vec, float scalar)
{
    assert(vec != NULL);

    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
}

Vec2
Vec2_GetSubScalar(const Vec2* vec, float scalar)
{
    assert(vec != NULL);

    Vec2 tmp = *vec;
    Vec2_SubScalar(&tmp, scalar);
    return tmp;
}

void
Vec2_Dot(Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = (vecA->x * vecB->x);
    vecA->y = (vecA->y * vecB->y);
}

Vec2
Vec2_GetDot(const Vec2* vecA, const Vec2* vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec2 tmp = *vecA;
    Vec2_Dot(&tmp, vecB);
    return tmp;
}

void
Vec2_Normalize(Vec2* vec)
{
    assert(vec != NULL);

    float len = Vec2_Length(vec);
    vec->x /= len;
    vec->y /= len;
}

Vec2
Vec2_GetNormalize(const Vec2* vec)
{
    assert(vec != NULL);

    Vec2 tmp = *vec;
    Vec2_Normalize(&tmp);
    return tmp;
}
