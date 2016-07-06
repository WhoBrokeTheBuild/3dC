#ifndef QUAT_H
#define QUAT_H

#include <stdbool.h>

#include <geom/vec.h>

typedef union Quat {
    float data[4];
    struct {
        float x, y, z, w;
    };
} Quat;

extern Quat Quat_ZERO;

Quat Quat_Create(float w, float x, float y, float z);

bool Quat_Equals(const Quat * this, const Quat * other);

float Quat_Length(const Quat * this);

void Quat_AddQuat();
Quat Quat_GetAddQuat();

void Quat_Normalize(Quat * this);
Quat Quat_GetNormalize(const Quat * this);

void Quat_Cross(Quat * this, const Quat * other);
Quat Quat_GetCross(const Quat * this, const Quat * other);

float Quat_Dot(const Quat * this, const Quat * other);

Vec3 Quat_RotateVec3(const Quat * this, const Vec3 * vec);

float Quat_GetAngle(const Quat * this);
Vec3 Quat_GetAxis(const Quat * this);

// Angle is in Rad
// Axis must be Normalized
Quat Quat_CreateFromAngleAxis(float angleRad, Vec3 * axis);

#endif // QUAT_H
