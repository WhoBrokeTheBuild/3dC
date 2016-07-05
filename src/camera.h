#ifndef CAMERA_H
#define CAMERA_H

#include <geom/vec.h>
#include <geom/mat.h>
#include <geom/quat.h>

typedef struct Camera {

    bool m_ProjUpdated;

    float m_FOV;
    float m_AspectWidth;
    float m_AspectHeight;
    float m_Near;
    float m_Far;
    float m_Pitch;
    float m_Yaw;

    Mat4x4 m_View;
    Mat4x4 m_Proj;

    Vec3 m_Pos;
    Vec3 m_Dir;
    Vec3 m_Up;
    Vec3 m_LookAt;
    Vec3 m_PosDelta;

    Quat m_Orient;

} Camera;

void Camera_Init(Camera * this);

Mat4x4 Camera_GetViewMatrix(Camera * this);

#endif // CAMERA_H
