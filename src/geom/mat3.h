#ifndef MAT3_H
#define MAT3_H

#include <stdio.h>

#include "vec.h"

typedef union Mat3
{
    float data[9];
    Vec3 vecs[3];

} Mat3;

void PrintMat3(Mat3* mat);

#endif // MAT3_H
