#include "mat3x3.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

void
Mat3x3_Print(Mat3x3* mat)
{
    assert(mat != NULL);

    printf("[ [ %f %f %f ]\n"
           "  [ %f %f %f ]\n"
           "  [ %f %f %f ] ]\n",
           mat->vecs[0].x, mat->vecs[0].y, mat->vecs[0].z, mat->vecs[1].x, mat->vecs[1].y,
           mat->vecs[1].z, mat->vecs[2].x, mat->vecs[2].y, mat->vecs[2].z);
}

bool
Mat3x3_Equals(Mat3x3* matA, Mat3x3* matB)
{
    assert(matA != NULL);
    assert(matB != NULL);

    return (Vec3_Equals(&(matA->vecs[0]), &(matB->vecs[0])) &&
            Vec3_Equals(&(matA->vecs[1]), &(matB->vecs[1])) &&
            Vec3_Equals(&(matA->vecs[2]), &(matB->vecs[2])));
}
