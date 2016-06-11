#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
    glutCreateWindow("Test");

    glewExperimental = GL_TRUE;
    GLenum glew_ret = glewInit();
    CHECK(glew_ret == GLEW_OK, "Failed to initialize GLEW %s", glewGetErrorString(glew_ret));

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
