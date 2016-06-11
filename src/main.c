#include <stdio.h>
#include <stdbool.h>

#include "debug.h"
#include "util.h"
#include "shaders.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

#define NumVertices 6

static void
Render(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

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
        { GL_VERTEX_SHADER,   "shaders/test.vs.glsl" },
        { GL_FRAGMENT_SHADER, "shaders/test.fs.glsl" },
        { GL_NONE, NULL }
    };
    GLuint prog = LoadShaderProgram(shaders);

    glUseProgram(prog);

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat vertices[NumVertices][2] = {
        { -0.90, -0.90 }, // Trangle 1
        {  0.85, -0.90 },
        { -0.90,  0.85 },
        {  0.90, -0.85 }, // Trangle 2
        {  0.90,  0.90 },
        { -0.85,  0.90 }
    };
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);

    glutDisplayFunc(Render);
    glutMainLoop();

	return 0;

error:

    return 1;
}
