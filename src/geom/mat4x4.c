#include "mat4x4.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

void
Mat4x4_Print(Mat4x4* mat)
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
Mat4x4_Equals(Mat4x4* matA, Mat4x4* matB)
{
    assert(matA != NULL);
    assert(matB != NULL);

    return (Vec4_Equals(&(matA->vecs[0]), &(matB->vecs[0])) &&
            Vec4_Equals(&(matA->vecs[1]), &(matB->vecs[1])) &&
            Vec4_Equals(&(matA->vecs[2]), &(matB->vecs[2])) &&
            Vec4_Equals(&(matA->vecs[3]), &(matB->vecs[3])));
}
