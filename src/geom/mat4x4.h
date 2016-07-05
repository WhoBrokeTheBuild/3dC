#ifndef MAT4X4_H
#define MAT4X4_H

#include <stdio.h>

#include "vec.h"

typedef union Mat4x4 {
    float data[4][4];
    float arr[16];
    Vec4 vecs[4];

} Mat4x4;

typedef Mat4x4 Mat4;

extern Mat4x4 Mat4x4_IDENTITY;

void Mat4x4_Print(Mat4x4 * mat);

bool Mat4x4_Equals(Mat4x4 * matA, Mat4x4 * matB);

Mat4x4 Mat4x4_LookAt(Vec3 * eye, Vec3 * center, Vec3 * up);

#endif // MAT4X4_H
