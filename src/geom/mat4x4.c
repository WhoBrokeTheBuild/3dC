#include "mat4x4.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

Mat4x4 Mat4x4_IDENTITY = { { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } } };

void
Mat4x4_Print(Mat4x4 * mat)
{
    assert(mat != NULL);

    printf("[ [ %f %f %f %f ]\n"
           "  [ %f %f %f %f ]\n"
           "  [ %f %f %f %f ]\n"
           "  [ %f %f %f %f ] ]\n",
        mat->vecs[0].x, mat->vecs[0].y, mat->vecs[0].z, mat->vecs[0].w, mat->vecs[1].x,
        mat->vecs[1].y, mat->vecs[1].z, mat->vecs[1].w, mat->vecs[2].x, mat->vecs[2].y,
        mat->vecs[2].z, mat->vecs[2].w, mat->vecs[3].x, mat->vecs[3].y, mat->vecs[3].z,
        mat->vecs[3].w);
}

bool
Mat4x4_Equals(Mat4x4 * matA, Mat4x4 * matB)
{
    assert(matA != NULL);
    assert(matB != NULL);

    return (Vec4_Equals(&(matA->vecs[0]), &(matB->vecs[0]))
        && Vec4_Equals(&(matA->vecs[1]), &(matB->vecs[1]))
        && Vec4_Equals(&(matA->vecs[2]), &(matB->vecs[2]))
        && Vec4_Equals(&(matA->vecs[3]), &(matB->vecs[3])));
}

Mat4x4
Mat4x4_LookAt(Vec3 * eye, Vec3 * center, Vec3 * up)
{
    Mat4x4 res = Mat4x4_IDENTITY;
    Vec3 f, s, u;

    f = Vec3_GetSubVec3(center, eye);
    Vec3_Normalize(&f);

    s = Vec3_GetCross(&f, up);
    Vec3_Normalize(&s);

    u = Vec3_GetCross(&s, &f);

    res.data[0][0] = s.data[0];
    res.data[1][0] = s.data[1];
    res.data[2][0] = s.data[2];
    res.data[0][1] = u.data[0];
    res.data[1][1] = u.data[1];
    res.data[2][1] = u.data[2];
    res.data[0][2] = -f.data[0];
    res.data[1][2] = -f.data[1];
    res.data[2][2] = -f.data[2];
    res.data[3][0] = -Vec3_Dot(&s, eye);
    res.data[3][1] = -Vec3_Dot(&u, eye);
    res.data[3][2] = -Vec3_Dot(&f, eye);

    return res;
}
