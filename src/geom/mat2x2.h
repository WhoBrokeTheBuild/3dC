#ifndef MATX2_H
#define MATX2_H

#include <stdio.h>

#include "vec.h"

typedef union Mat2x2
{
    float data[2][2];
    float arr[4];
    Vec2 vecs[2];

} Mat2x2;

typedef Mat2x2 Mat2;

void Mat2x2_Print(Mat2x2* mat);

bool Mat2x2_Equals(Mat2x2* matA, Mat2x2* matB);

#endif // MAT2X2_H
