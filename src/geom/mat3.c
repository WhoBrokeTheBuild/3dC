#include "mat3.h"

void
PrintMat3(Mat3* mat)
{
    printf("[ [ %f %f %f ]\n"
           "  [ %f %f %f ]\n"
           "  [ %f %f %f ] ]\n",
           mat->vecs[0].x, mat->vecs[0].y, mat->vecs[0].z, mat->vecs[1].x, mat->vecs[1].y,
           mat->vecs[1].z, mat->vecs[2].x, mat->vecs[2].y, mat->vecs[2].z);
}
