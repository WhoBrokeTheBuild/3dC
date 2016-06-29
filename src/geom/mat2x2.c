#include "mat2x2.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

void
Mat2x2_Print(Mat2x2 * mat)
{
    assert(mat != NULL);

    printf("[ [ %f %f ]\n"
           "  [ %f %f ] ]\n",
        mat->vecs[0].x, mat->vecs[0].y, mat->vecs[1].x, mat->vecs[1].y);
}

bool
Mat2x2_Equals(Mat2x2 * matA, Mat2x2 * matB)
{
    assert(matA != NULL);
    assert(matB != NULL);

    return (Vec2_Equals(&(matA->vecs[0]), &(matB->vecs[0])) && Vec2_Equals(&(matA->vecs[1]), &(matB->vecs[1])));
}
