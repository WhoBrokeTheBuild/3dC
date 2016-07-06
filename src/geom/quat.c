#include "quat.h"

#include <math.h>
#include <assert.h>

Quat Quat_ZERO = { { 0.0f, 0.0f, 0.0f, 0.0f } };

Quat
Quat_Create(float w, float x, float y, float z)
{
    Quat tmp = { { w, x, y, z } };
    return tmp;
}

float
Quat_Length(const Quat * this)
{
    assert(this != NULL);

    return sqrtf(Quat_Dot(this, this));
}

void
Quat_Normalize(Quat * this)
{
    assert(this != NULL);

    float len = Quat_Length(this);
    if (len <= 0.0f)
        *this = Quat_Create(1.0f, 0.0f, 0.0f, 0.0f);

    float oneOverLen = 1.0f / len;
    *this = Quat_Create(
        this->w * oneOverLen, this->x * oneOverLen, this->y * oneOverLen, this->z * oneOverLen);
}

Quat
Quat_GetNormalize(const Quat * this)
{
    assert(this != NULL);

    Quat tmp = *this;
    Quat_Normalize(&tmp);
    return tmp;
}

void
Quat_Cross(Quat * this, const Quat * other)
{
    assert(this != NULL);

    *this = Quat_Create(
        this->w * other->w - this->x * other->x - this->y * other->y - this->z * other->z,
        this->w * other->x + this->x * other->w + this->y * other->z - this->z * other->y,
        this->w * other->y + this->y * other->w + this->z * other->x - this->x * other->z,
        this->w * other->z + this->z * other->w + this->x * other->y - this->y * other->x);
}

Quat
Quat_GetCross(const Quat * this, const Quat * other)
{
    assert(this != NULL);
    assert(other != NULL);

    Quat tmp = *this;
    Quat_Cross(&tmp, other);
    return tmp;
}

float
Quat_Dot(const Quat * this, const Quat * other)
{
    assert(this != NULL);
    assert(other != NULL);

    return this->x * other->x + this->y * other->y + this->z * other->z + this->w * other->w;
}

Vec3
Quat_RotateVec3(const Quat * this, const Vec3 * vec)
{
    // TODO: Implement
    return Vec3_ZERO;
}

float
Quat_GetAngle(const Quat * this)
{
    assert(this != NULL);

    return acosf(this->w) * 2.0f;
}

Vec3
Quat_GetAxis(const Quat * this)
{
    assert(this != NULL);

    float tmp1 = 1.0f - (this->w * this->w);
    if (tmp1 <= 0.0f)
        return Vec3_Create(0.0f, 0.0f, 1.0f);
    float tmp2 = 1.0f / sqrtf(tmp1);
    return Vec3_Create(this->x * tmp2, this->y * tmp2, this->z * tmp2);
}

Quat
Quat_CreateFromAngleAxis(float angle, Vec3 * axis)
{
    assert(axis != NULL);

    Quat res;
    float s = sinf(angle * 0.5f);

    res.w = cosf(angle * 0.5f);
    res.x = axis->x * s;
    res.y = axis->y * s;
    res.z = axis->z * s;

    return res;
}
