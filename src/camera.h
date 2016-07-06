#ifndef CAMERA_H
#define CAMERA_H

#include <geom/vec.h>
#include <geom/mat.h>
#include <geom/quat.h>

typedef struct Camera {

    Vec3 pos;
    Vec3 dir;
    Vec3 up;

    bool _projUpdated;

    float _fov;
    float _aspectWidth;
    float _aspectHeight;
    float _near;
    float _far;
    float _pitch;
    float _yaw;

    Vec3 _lookAt;

    Mat4x4 _view;
    Mat4x4 _proj;

    Quat _orient;

} Camera;

void Camera_Init(Camera * this, float width, float height, const Vec3 pos, const Vec3 dir,
    const Vec3 up, float fov, float near, float far);
void Camera_Term(Camera * this);

Mat4x4 Camera_GetProjMatrix(Camera * this);
Mat4x4 Camera_GetViewMatrix(Camera * this);

#endif // CAMERA_H
