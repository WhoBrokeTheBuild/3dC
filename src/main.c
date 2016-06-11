#include <stdio.h>
#include <stdbool.h>

#include "debug.h"
#include "util.h"
#include "shaders.h"

static void
Render(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

int 
main(int argc, char* argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitContextVersion(4, 3);
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

    ShaderInfo shaders[] = { 
        { .type = GL_VERTEX_SHADER,   .filename = "shaders/test.vs.glsl" },
        { .type = GL_FRAGMENT_SHADER, .filename = "shaders/test.fs.glsl" },
        { .type = GL_INVALID_ENUM,    .filename = NULL }
    };
    GLuint test_sp = LoadShaderProgram(shaders);

    glUseProgram(test_sp);

    glutDisplayFunc(Render);
    glutMainLoop();

	return 0;

error:

    return 1;
}
