#include "camera.h"

Mat4x4
Camera_GetViewMatrix(Camera * this)
{
    this->m_Dir = this->m_LookAt;
    Vec3_SubVec3(&this->m_Dir, &this->m_Pos);
    Vec3_Normalize(&this->m_Dir);

    Vec3 pitchAxis = Vec3_GetCross(&this->m_Dir, &this->m_Up);

    Quat pitchQ = Quat_CreateFromAngleAxis(this->m_Pitch, &pitchAxis);
    Quat yawQ = Quat_CreateFromAngleAxis(this->m_Yaw, &this->m_Up);

    Quat tmp = Quat_GetCross(&pitchQ, &yawQ);
    Quat_Normalize(&tmp);

    this->m_Dir = Quat_RotateVec3(&tmp, &this->m_Dir);
    Vec3_AddVec3(&this->m_Pos, &this->m_PosDelta);

    this->m_LookAt = Vec3_GetAddVec3(&this->m_Pos, &this->m_Dir);
    this->m_View = Mat4x4_LookAt(&this->m_Pos, &this->m_LookAt, &this->m_Up);

    this->m_Pitch *= 0.5f;
    this->m_Yaw *= 0.5f;
    Vec3_MultScalar(&this->m_PosDelta, 0.8f);

    return this->m_View;
}
