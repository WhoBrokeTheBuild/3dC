#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

#include "debug.h"
#include "util.h"
#include "shaders.h"
#include "geom/vec.h"
#include "geom/mat.h"

#define BUFFER_OFFSET(x) ((const void *)(x))

#ifndef TEST_BUILD

static void
Render(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

int
main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);

    glutInitWindowSize(1024, 768);
    glutCreateWindow("Test");

    LOG_INFO("Running GLUT Version %d", glutGet(GLUT_VERSION));

    glewExperimental = GL_TRUE;
    GLenum glew_ret = glewInit();
    CHECK(glew_ret == GLEW_OK, "Failed to initialize GLEW %s", glewGetErrorString(glew_ret));

    LOG_INFO("Running GLEW Version %s", glewGetString(GLEW_VERSION));
    LOG_INFO("Running OpenGL Version %s", glGetString(GL_VERSION));
    LOG_INFO("Running OpenGL GLSL Version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    ShaderInfo shaders[] = { { GL_VERTEX_SHADER, "shaders/PostProcessGodrayVS.glsl" },
        { GL_FRAGMENT_SHADER, "shaders/PostProcessGodrayFS.glsl" }, { GL_NONE, NULL } };
    GLuint prog = LoadShaderProgram(shaders);

    glUseProgram(prog);

    Vec3 testVec = { { 0.0f, 1.0f, 2.0f } };
    Vec3_Print(&testVec);

    testVec.data[0] = 5.0f;
    testVec.data[1] = 4.0f;
    testVec.data[2] = 3.0f;
    Vec3_Print(&testVec);

    testVec.x = 3.0f;
    testVec.y = 2.0f;
    testVec.z = 1.0f;
    Vec3_Print(&testVec);

    Vec3_Normalize(&testVec);
    Vec3_Print(&testVec);

    testVec.x = testVec.y = testVec.z = 0.0f;
    Vec3 testVec2 = { { 0.0f, 0.0f, 1.0f } };
    float dist = Vec3_Distance(&testVec, &testVec2);
    printf("dist %f\n", dist);

    Mat3 testMat = { {
        { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f },
    } };
    Mat3x3_Print(&testMat);

    glutDisplayFunc(Render);
    glutMainLoop();

    return 0;

error:

    return 1;
}

#endif // TEST_BUILD

#ifdef __cplusplus
} // extern "C"
#endif
