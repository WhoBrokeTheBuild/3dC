#include "vec3.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <util/parsing.h>
#include <debug.h>

Vec3 Vec3_ZERO = { { 0.0f, 0.0f, 0.0f } };

DYNARR_IMP(Vec3, Vec3, Vec3_ZERO);

void
Vec3_Print(const Vec3 * vec)
{
    assert(vec != NULL);

    printf("[ %f %f %f ]\n", vec->x, vec->y, vec->z);
}

void
Vec3_Parse(Vec3 * vec, const char * str)
{
    assert(vec != NULL);
    assert(str != NULL);

    char * endptr;
    CHECK(TryParseFloat(&(vec->x), str, &endptr), "Vec3 parsing failed");
    CHECK(endptr != NULL, "Vec3 parsing failed");
    CHECK(TryParseFloat(&(vec->y), endptr, &endptr), "Vec3 parsing failed");
    CHECK(endptr != NULL, "Vec3 parsing failed");
    CHECK(TryParseFloat(&(vec->z), endptr, NULL), "Vec3 parsing failed");

    return;

error:
    *vec = Vec3_ZERO;
}

Vec3
Vec3_GetParse(const char * str)
{
    assert(str != NULL);

    Vec3 tmp;
    Vec3_Parse(&tmp, str);
    return tmp;
}

bool
Vec3_Equals(const Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    return (vecA->x == vecB->x && vecA->y == vecB->y && vecA->z == vecB->z);
}

float
Vec3_Length(const Vec3 * vec)
{
    assert(vec != NULL);

    return sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
}

float
Vec3_Distance(const Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    float x = (vecB->x - vecA->x), y = (vecB->y - vecA->y), z = (vecB->z - vecA->z);
    return sqrt((x * x) + (y * y) + (z * z));
}

void
Vec3_AddVec3(Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
    vecA->z = vecA->z + vecB->z;
}

Vec3
Vec3_GetAddVec3(const Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec3 tmp = *vecA;
    Vec3_AddVec3(&tmp, vecB);
    return tmp;
}

void
Vec3_AddScalar(Vec3 * vec, float scalar)
{
    assert(vec != NULL);

    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
    vec->z = vec->z + scalar;
}

Vec3
Vec3_GetAddScalar(const Vec3 * vec, float scalar)
{
    assert(vec != NULL);

    Vec3 tmp = *vec;
    Vec3_AddScalar(&tmp, scalar);
    return tmp;
}

void
Vec3_SubVec3(Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = vecA->x + vecB->x;
    vecA->y = vecA->y + vecB->y;
    vecA->z = vecA->z + vecB->z;
}

Vec3
Vec3_GetSubVec3(const Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec3 tmp = *vecA;
    Vec3_SubVec3(&tmp, vecB);
    return tmp;
}

void
Vec3_SubScalar(Vec3 * vec, float scalar)
{
    assert(vec != NULL);

    vec->x = vec->x + scalar;
    vec->y = vec->y + scalar;
    vec->z = vec->z + scalar;
}

Vec3
Vec3_GetSubScalar(const Vec3 * vec, float scalar)
{
    assert(vec != NULL);

    Vec3 tmp = *vec;
    Vec3_SubScalar(&tmp, scalar);
    return tmp;
}

void
Vec3_Cross(Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec3 tmp = *vecA;
    vecA->x = (tmp.y * vecB->z) - (tmp.z * vecB->y);
    vecA->y = (tmp.z * vecB->x) - (tmp.x * vecB->z);
    vecA->z = (tmp.x * vecB->y) - (tmp.y * vecB->x);
}

Vec3
Vec3_GetCross(const Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec3 tmp = *vecA;
    Vec3_Cross(&tmp, vecB);
    return tmp;
}

void
Vec3_Dot(Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    vecA->x = (vecA->x * vecB->x);
    vecA->y = (vecA->y * vecB->y);
    vecA->z = (vecA->z * vecB->z);
}

Vec3
Vec3_GetDot(const Vec3 * vecA, const Vec3 * vecB)
{
    assert(vecA != NULL);
    assert(vecB != NULL);

    Vec3 tmp = *vecA;
    Vec3_Dot(&tmp, vecB);
    return tmp;
}

void
Vec3_Normalize(Vec3 * vec)
{
    assert(vec != NULL);

    float len = Vec3_Length(vec);
    vec->x /= len;
    vec->y /= len;
    vec->z /= len;
}

Vec3
Vec3_GetNormalize(const Vec3 * vec)
{
    assert(vec != NULL);

    Vec3 tmp = *vec;
    Vec3_Normalize(&tmp);
    return tmp;
}
