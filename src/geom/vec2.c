#include "vec2.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <util/parsing.h>
#include <debug.h>

const Vec2 Vec2_ZERO = { { 0.0f, 0.0f } };

DYNARR_IMP(Vec2, Vec2, Vec2_ZERO);

void
Vec2_Print(const Vec2 * vec)
{
    assert(vec != NULL);

    printf("[ %f %f ]\n", vec->x, vec->y);
}

void
Vec2_Parse(Vec2 * vec, const char * str)
{
    assert(vec != NULL);
    assert(str != NULL);

    char * endptr;
    CHECK(TryParseFloat(&(vec->x), str, &endptr), "Vec2 parsing failed");
    CHECK(endptr != NULL, "Vec2 parsing failed");
    CHECK(TryParseFloat(&(vec->y), endptr, NULL), "Vec2 parsing failed");

    return;

error:
    *vec = Vec2_ZERO;
}

Vec2
Vec2_GetParse(const char * str)
{
    assert(str != NULL);

    Vec2 tmp;
    Vec2_Parse(&tmp, str);
    return tmp;
}

bool
Vec2_Equals(const Vec2 * vecA, const Vec2 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    return (vecA->x == vecB->x && vecA->y == vecB->y);
}

float
Vec2_Length(const Vec2 * vec)
{
    assert(vec != NULL);

    return sqrt((vec->x * vec->x) + (vec->y * vec->y));
}

float
Vec2_Distance(const Vec2 * vecA, const Vec2 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    float x = (vecB->x - vecA->x), y = (vecB->y - vecA->y);
    return sqrt((x * x) + (y * y));
}

void
Vec2_AddVec2(Vec2 * vecA, const Vec2 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
}

Vec2
Vec2_GetAddVec2(const Vec2 * vecA, const Vec2 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec2 tmp = *vecA;
    Vec2_AddVec2(&tmp, vecB);
    return tmp;
}

void
Vec2_AddScalar(Vec2 * vec, float scalar)
{
    assert(vec != NULL);

    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
}

Vec2
Vec2_GetAddScalar(const Vec2 * vec, float scalar)
{
    assert(vec != NULL);

    Vec2 tmp = *vec;
    Vec2_AddScalar(&tmp, scalar);
    return tmp;
}

void
Vec2_SubVec2(Vec2 * vecA, const Vec2 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
}

Vec2
Vec2_GetSubVec2(const Vec2 * vecA, const Vec2 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec2 tmp = *vecA;
    Vec2_SubVec2(&tmp, vecB);
    return tmp;
}

void
Vec2_SubScalar(Vec2 * vec, float scalar)
{
    assert(vec != NULL);

    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
}

Vec2
Vec2_GetSubScalar(const Vec2 * vec, float scalar)
{
    assert(vec != NULL);

    Vec2 tmp = *vec;
    Vec2_SubScalar(&tmp, scalar);
    return tmp;
}

float
Vec2_Dot(const Vec2 * vecA, const Vec2 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    return vecA->x * vecB->x + vecA->y * vecB->y;
}

void
Vec2_Normalize(Vec2 * vec)
{
    assert(vec != NULL);

    float len = Vec2_Length(vec);
    vec->x /= len;
    vec->y /= len;
}

Vec2
Vec2_GetNormalize(const Vec2 * vec)
{
    assert(vec != NULL);

    Vec2 tmp = *vec;
    Vec2_Normalize(&tmp);
    return tmp;
}
