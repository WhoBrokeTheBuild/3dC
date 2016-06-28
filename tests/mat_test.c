#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "geom/mat.h"

Suite*
mat_suite()
{
    Suite* s;
    TCase *tc_mat2x2, *tc_mat3x3, *tc_mat4x4;

    s = suite_create("Matricies");

    tc_mat2x2 = tcase_create("Mat2x2");
    suite_add_tcase(s, tc_mat2x2);

    tc_mat3x3 = tcase_create("Mat3x3");
    suite_add_tcase(s, tc_mat3x3);

    tc_mat4x4 = tcase_create("Mat4x4");
    suite_add_tcase(s, tc_mat4x4);

    return s;
}

int
main(int argc, char** argv)
{
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = mat_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
