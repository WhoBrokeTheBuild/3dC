#ifndef MAT3X3_H
#define MAT3X3_H

#include <stdio.h>

#include "vec.h"

typedef union Mat3x3 {
    float data[3][3];
    float arr[9];
    Vec3 vecs[3];

} Mat3x3;

typedef Mat3x3 Mat3;

void Mat3x3_Print(Mat3x3 * mat);

bool Mat3x3_Equals(Mat3x3 * matA, Mat3x3 * matB);

#endif // MAT3X3_H
