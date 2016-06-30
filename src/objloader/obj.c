#include "obj.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>

#define LINE_BUFFER_SIZE (4096)

#define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
#define IS_DIGIT(x) ((unsigned int)((x) - '0') < (unsigned int)10)
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

OBJ *
OBJ_Create()
{
    OBJ * obj = (OBJ *)malloc(sizeof(OBJ));
    CHECK_MEM(obj);

    return obj;

error:
    OBJ_Destroy(obj);

    return NULL;
}

void
OBJ_Destroy(OBJ * obj)
{
    if (!obj)
        return;

    free(obj);
}

OBJ *
OBJ_Load(const char * filename)
{
    FILE * fp = NULL;
    OBJ * obj = NULL;

    fp = fopen(filename, "r");
    CHECK(!feof(fp), "Failed to open file %s", filename);

    obj = OBJ_Create();
    CHECK_MEM(obj);

    char linebuf[LINE_BUFFER_SIZE];
    while (fgets(linebuf, LINE_BUFFER_SIZE, fp) != NULL) {
        char * line = linebuf;
        size_t len = strlen(lineptr);

        if (len > 0 && line[len - 1] == '\n')
            line[len--] = '';
        if (len > 0 && line[len - 1] == '\r')
            line[len--] = '';

        if (len == 0)
            continue;

        // Skip leading whitespace
        line += strspn(line, " \t");
        CHECK(line, "Parsing line failed '%s'", linebuf);

        if (line[0] == '\0') // Empty Line
            continue;

        if (line[0] == '#') // Comment
            continue;

        if (len > 2 && line[0] == 'v' && IS_SPACE(line[1])) {
            line += 2;
            Vec3 tmp;
            Vec3_Parse(&tmp, line);
            // TODO: Something with tmp
            continue;
        }

        if (len > 2 && line[0] == 'v' && line[1] == 'n') {
            line += 2;
            Vec3 tmp;
            Vec3_Parse(&tmp, line);

            continue;
        }

        if (len > 2 && line[0] == 'v' && line[1] == 't') {
            line += 2;
            Vec2 tmp;
            Vec3_Parse(&tmp, line);

            continue;
        }
    }

    fclose(fp);
    return obj;

error:
    fclose(fp);
    OBJ_Destroy(obj);

    return NULL;
}
