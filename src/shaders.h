#ifndef SHADERS_H
#define SHADERS_H

#include <opengl.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SHADER_COUNT 20
#define MAX_SHADER_SIZE 1000000
#define MAX_SHADER_LOG_SIZE 100000
#define MAX_PROGRAM_LOG_SIZE MAX_SHADER_LOG_SIZE

typedef struct ShaderInfo {
    GLenum type;
    const char * filename;

} ShaderInfo;

bool PrintShaderProgramLog(GLuint program);
bool PrintShaderLog(GLuint shader);

GLuint LoadShader(const char * filename, GLenum shader_type);
GLuint LoadShaderProgram(ShaderInfo * shaders);

#endif // SHADERS_H
