#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define CLEAN_ERRNO() (errno == 0 ? "None" : strerror(errno))

#define LOG_INFO(M, ...) printf("[INFO] (%s:%d) " M "\n", \
        __FILE__, __LINE__, ##__VA_ARGS__);

#define LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", \
        __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__);

#define LOG_ERR(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", \
        __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__);

#define CHECK(A, M, ...) if (!(A)) { LOG_ERR(M, ##__VA_ARGS__); errno = 0; goto error; }

#define CHECK_MEM(A) CHECK((A), "Out of memory.");

#define SENTINEL(M, ...) { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

#define MAX_SHADER_COUNT     20
#define MAX_SHADER_SIZE      1000000
#define MAX_SHADER_LOG_SIZE  100000
#define MAX_PROGRAM_LOG_SIZE MAX_SHADER_LOG_SIZE

typedef struct ShaderInfo
{
    const char * filename;
    GLenum type;

} ShaderInfo;

long int
GetFileSize(FILE * fp)
{
    CHECK(fp, "File isn't open");

    fseek(fp, 0L, SEEK_END);
    long int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;

error:

    return -1;
}

bool
PrintShaderProgramLog(GLuint program)
{
    char * program_log = NULL;

    CHECK(!glIsProgram(program), "Cannot print program log, %d is not a program", program);

    GLint log_size = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size); 
    CHECK(log_size < MAX_PROGRAM_LOG_SIZE, "Program log for %d exceeds maximum size allowed (%d > %d)",
            program, log_size, MAX_PROGRAM_LOG_SIZE);
    
    program_log = malloc((log_size + 1) * sizeof(char));
    CHECK_MEM(program_log);

    int ret_size = 0;
    glGetProgramInfoLog(program, log_size, &ret_size, program_log);
    CHECK(ret_size <= 0, "Failed to get program log for %d", program);
    program_log[log_size] = '\0';
    
    LOG_INFO("Log for program %d:\n%s", program, program_log);

    free(program_log);
    return true;

error:

    free(program_log);
    return false;
}

bool
PrintShaderLog(GLuint shader)
{
    char * shader_log = NULL;

    CHECK(!glIsShader(shader), "Cannot print shader log, %d is not a shader", shader);

    GLint log_size = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size); 
    CHECK(log_size < MAX_SHADER_LOG_SIZE, "Shader log for %d exceeds maximum size allowed (%d > %d)",
            shader, log_size, MAX_SHADER_LOG_SIZE);
    
    shader_log = malloc((log_size + 1) * sizeof(char));
    CHECK_MEM(shader_log);

    int ret_size = 0;
    glGetShaderInfoLog(shader, log_size, &ret_size, shader_log);
    CHECK(ret_size <= 0, "Failed to get shader log for %d", shader);
    shader_log[log_size] = '\0';
    
    LOG_INFO("Log for shader %d:\n%s", shader, shader_log);

    free(shader_log);
    return true;

error:

    free(shader_log);
    return false;
}

GLuint
LoadShader(const char * filename, GLenum shader_type)
{
    GLuint shader = 0;
    char * shader_str = NULL;
    FILE * fp = NULL;

    fp = fopen(filename, "r");
    CHECK(fp, "Failed to open shader '%s'", filename);

    long int file_size = GetFileSize(fp);
    CHECK(file_size < MAX_SHADER_SIZE, "Shader exceeds maximum size allowed (%ld > %d)",
           file_size, MAX_SHADER_SIZE);

    shader_str = malloc(file_size * sizeof(char));
    CHECK_MEM(shader_str);

    size_t bytes_read = fread(shader_str, 1, file_size, fp);
    CHECK(bytes_read == file_size, "Failed to read whole shader file '%s' read %zu/%ld",
            filename, bytes_read, file_size);

    shader = glCreateShader(shader_type);
    CHECK(shader != 0, "Failed to create shader object");
    CHECK(shader != GL_INVALID_ENUM, "Invalid shader type %d", shader_type);

    glShaderSource(shader, 1, (const GLchar**)&shader_str, NULL);
    glCompileShader(shader);

    GLint shader_compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
    CHECK(shader_compiled, "Failed to compile shader '%s'", filename);

    free(shader_str);
    fclose(fp);

    return shader;

error:

    if (shader) PrintShaderLog(shader);

    free(shader_str);
    fclose(fp);
    glDeleteShader(shader);

    return -1;
}

GLuint
LoadShaderProgram(ShaderInfo * shaders)
{
    GLuint program = 0;
    GLuint shader_ids[MAX_SHADER_COUNT];

    program = glCreateProgram();
    CHECK(program != 0, "Failed to create shader program object");

    for (int i = 0; shaders[i].filename; ++i) {
        CHECK(i < MAX_SHADER_COUNT, "Exceeded maximum number of shaders allowed %d", MAX_SHADER_COUNT);

        shader_ids[i] = LoadShader(shaders[i].filename, shaders[i].type);
        CHECK(shader_ids[i] != -1, "Failed to load shader program");

        glAttachShader(program, shader_ids[i]);
    }

    glLinkProgram(program);

    GLint program_linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
    CHECK(program_linked, "Failed to link program");
    
    return program;

error:

    if (program) PrintShaderProgramLog(program);

    for (int i = 0; i < MAX_SHADER_COUNT; ++i) {
        glDeleteShader(shader_ids[i]);
    }
    glDeleteProgram(program);

    return -1;
}

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
