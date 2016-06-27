#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "geom/vec.h"

const float FLOAT_ERR_THRESHOLD = 0.0005f;

START_TEST(test_Vec2_xy)
{
    Vec2 a = { { 123.0f, 456.0f } };

    ck_assert(a.x == 123.0f);
    ck_assert(a.y == 456.0f);
}
END_TEST

START_TEST(test_Vec2_ab)
{
    Vec2 a = { { 123.0f, 456.0f } };

    ck_assert(a.a == 123.0f);
    ck_assert(a.b == 456.0f);
}
END_TEST

START_TEST(test_Vec2_st)
{
    Vec2 a = { { 123.0f, 456.0f } };

    ck_assert(a.s == 123.0f);
    ck_assert(a.t == 456.0f);
}
END_TEST

START_TEST(test_Vec2_data)
{
    Vec2 a = { { 123.0f, 456.0f } };

    ck_assert(a.data[0] == 123.0f);
    ck_assert(a.data[1] == 456.0f);
}
END_TEST

START_TEST(test_Vec2_Equals)
{
    Vec2 a = { { 123.0f, 456.0f } };
    Vec2 b = { { 123.0f, 456.0f } };
    Vec2 c = { { 1.0f, 2.0f } };

    ck_assert(Vec2_Equals(&a, &b));
    ck_assert(!Vec2_Equals(&a, &c));
}
END_TEST

START_TEST(test_Vec2_Length)
{
    Vec2 a = { { 2.2f, 3.6f } };
    Vec2 b = { { -4.8f, -2.2f } };

    const float expLenA = 4.219f, expLenB = 5.28f;

    float lenA = Vec2_Length(&a);
    if (lenA < expLenA - FLOAT_ERR_THRESHOLD || lenA > expLenA + FLOAT_ERR_THRESHOLD) {
        fprintf(stderr, "Expected %f, got %f\n", expLenA, lenA);
        ck_abort_msg("Vec2_Length failed");
    }

    float lenB = Vec2_Length(&b);
    if (lenB < expLenB - FLOAT_ERR_THRESHOLD || lenB > expLenB + FLOAT_ERR_THRESHOLD) {
        fprintf(stderr, "Expected %f, got %f\n", expLenB, lenB);
        ck_abort_msg("Vec2_Length failed");
    }
}
END_TEST

START_TEST(test_Vec3_xyz)
{
    Vec3 a = { { 123.0f, 456.0f, 789.0f } };

    ck_assert(a.x == 123.0f);
    ck_assert(a.y == 456.0f);
    ck_assert(a.z == 789.0f);
}
END_TEST

START_TEST(test_Vec3_abc)
{
    Vec3 a = { { 123.0f, 456.0f, 789.0f } };

    ck_assert(a.a == 123.0f);
    ck_assert(a.b == 456.0f);
    ck_assert(a.c == 789.0f);
}
END_TEST

START_TEST(test_Vec3_data)
{
    Vec3 a = { { 123.0f, 456.0f, 789.0f } };

    ck_assert(a.data[0] == 123.0f);
    ck_assert(a.data[1] == 456.0f);
    ck_assert(a.data[2] == 789.0f);
}
END_TEST

START_TEST(test_Vec3_Equals)
{
    Vec3 a = { { 123.0f, 456.0f, 789.0f } };
    Vec3 b = { { 123.0f, 456.0f, 789.0f } };
    Vec3 c = { { 1.0f, 2.0f, 3.0f } };

    ck_assert(Vec3_Equals(&a, &b));
    ck_assert(!Vec3_Equals(&a, &c));
}
END_TEST

START_TEST(test_Vec3_Length)
{
    Vec3 a = { { 1.0f, 2.0f, 3.0f } };
    // Vec3 b = {{  }};

    const float expLenA = 3.742f;
    // expLenB = 5.28f;

    float lenA = Vec3_Length(&a);
    if (lenA < expLenA - FLOAT_ERR_THRESHOLD || lenA > expLenA + FLOAT_ERR_THRESHOLD) {
        fprintf(stderr, "Expected %f, got %f\n", expLenA, lenA);
        ck_abort_msg("Vec3_Length failed");
    }

    // float lenB = Vec2_Length(&b);
    // if (lenB < expLenB - FLOAT_ERR_THRESHOLD ||
    //    lenB > expLenB + FLOAT_ERR_THRESHOLD)
    //{
    //    fprintf(stderr, "Expected %f, got %f\n", expLenB, lenB);
    //    ck_abort_msg("Vec2_Length failed");
    //}
}
END_TEST

Suite*
vec_suite()
{
    Suite* s;
    TCase *tc_vec2, *tc_vec3, *tc_vec4;

    s = suite_create("Vectors");

    tc_vec2 = tcase_create("Vec2");
    tcase_add_test(tc_vec2, test_Vec2_xy);
    tcase_add_test(tc_vec2, test_Vec2_ab);
    tcase_add_test(tc_vec2, test_Vec2_st);
    tcase_add_test(tc_vec2, test_Vec2_data);
    tcase_add_test(tc_vec2, test_Vec2_Equals);
    tcase_add_test(tc_vec2, test_Vec2_Length);
    suite_add_tcase(s, tc_vec2);

    tc_vec3 = tcase_create("Vec3");
    tcase_add_test(tc_vec3, test_Vec3_xyz);
    tcase_add_test(tc_vec3, test_Vec3_abc);
    tcase_add_test(tc_vec3, test_Vec3_data);
    tcase_add_test(tc_vec3, test_Vec3_Equals);
    tcase_add_test(tc_vec3, test_Vec3_Length);
    suite_add_tcase(s, tc_vec3);

    tc_vec4 = tcase_create("Vec4");

    suite_add_tcase(s, tc_vec4);

    return s;
}

int
main(int argc, char** argv)
{
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = vec_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
