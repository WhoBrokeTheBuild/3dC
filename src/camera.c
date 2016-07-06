#include "camera.h"

#include <assert.h>

void
Camera_Init(Camera * this, float width, float height, const Vec3 pos, const Vec3 dir, const Vec3 up,
    float fov, float near, float far)
{
    assert(this != NULL);

    this->pos = Vec3_ZERO;
    this->dir = Vec3_ZERO;
    this->up = Vec3_ZERO;

    this->_projUpdated = true;

    this->_fov = fov;
    this->_aspectWidth = width;
    this->_aspectHeight = height;
    this->_near = near;
    this->_far = far;
    this->_pitch = 0.0f;
    this->_yaw = 0.0f;

    this->_lookAt = Vec3_ZERO;

    this->_view = Mat4x4_IDENTITY;
    this->_proj = Mat4x4_IDENTITY;

    this->_orient = Quat_ZERO;
}

void
Camera_Term(Camera * this)
{
    if (!this)
        return;
}

Mat4x4
Camera_GetProjMatrix(Camera * this)
{
    if (!this->_projUpdated)
        return this->_proj;

    if (this->_aspectWidth <= 0.0f || this->_aspectHeight <= 0.0f || this->_fov <= 0.0f)
        return Mat4x4_IDENTITY;

    // this->_proj;

    this->_projUpdated = false;
    return this->_proj;
}

Mat4x4
Camera_GetViewMatrix(Camera * this)
{
    this->dir = this->_lookAt;
    Vec3_SubVec3(&this->dir, &this->pos);
    Vec3_Normalize(&this->dir);

    Vec3 pitchAxis = Vec3_GetCross(&this->dir, &this->up);

    Quat pitchQ = Quat_CreateFromAngleAxis(this->_pitch, &pitchAxis);
    Quat yawQ = Quat_CreateFromAngleAxis(this->_yaw, &this->up);

    Quat tmp = Quat_GetCross(&pitchQ, &yawQ);
    Quat_Normalize(&tmp);

    this->dir = Quat_RotateVec3(&tmp, &this->dir);

    this->_lookAt = Vec3_GetAddVec3(&this->pos, &this->dir);
    this->_view = Mat4x4_LookAt(&this->pos, &this->_lookAt, &this->up);

    this->_pitch *= 0.5f;
    this->_yaw *= 0.5f;

    return this->_view;
}
