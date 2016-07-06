#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

#include <opengl.h>
#include <debug.h>
#include <shaders.h>
#include <camera.h>
#include <geom/vec.h>
#include <geom/mat.h>
#include <objloader/obj.h>

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

    ShaderInfo shaders[] = { { GL_VERTEX_SHADER, "shaders/test.vs.glsl" },
        { GL_FRAGMENT_SHADER, "shaders/test.fs.glsl" }, { GL_NONE, NULL } };
    GLuint prog = LoadShaderProgram(shaders);

    glUseProgram(prog);

    Camera camera;
    Camera_Init(&camera, 1024, 768, Vec3_Create(20.0f, 150.0f, 20.0f),
        Vec3_Create(0.7f, 0.0f, 0.7f), Vec3_Create(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 10000.0f);

    OBJ cube;
    CHECK(OBJ_Load(&cube, "assets/cube.obj"), "Failed to load cube");

    Camera_Term(&camera);
    OBJ_Term(&cube);

    glutDisplayFunc(Render);
    glutMainLoop();

    return 0;

error:

    Camera_Term(&camera);
    OBJ_Term(&cube);

    return 1;
}

#endif // TEST_BUILD

#ifdef __cplusplus
} // extern "C"
#endif
