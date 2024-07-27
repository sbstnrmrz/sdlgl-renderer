#include "shader.h"
#include "defs.h"

u32 compile_shader(const char *path, GLenum shader_type) {
    if (shader_type != GL_FRAGMENT_SHADER && shader_type != GL_VERTEX_SHADER) {
        fprintf(stderr, "shader type its not valid\n");
        exit(1);
    }
    
    int path_len = strlen(path);
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        fprintf(stderr, "error opening %s\n", path);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    int file_len = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *str = calloc(1, file_len);
    fread(str, 1, file_len, f);
    fclose(f);

    u32 shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, (const GLchar *const *)&str, &file_len);
    glCompileShader(shader);

    int compiled = 0;
    char log[512] = {0};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        fprintf(stderr, "error compiling %s. error: %s", shader_type == GL_FRAGMENT_SHADER ? "fragment shader"
                                                                                           : "vertex shader", log);
        exit(1);
    }
    free(str);

    return shader;
}

Shader create_shader() {
    Shader shader = {0};

    return shader;
}


