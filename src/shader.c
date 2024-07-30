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
        glGetShaderInfoLog(shader, 512, NULL, log);
        fprintf(stderr, "error compiling %s. error: %s", shader_type == GL_FRAGMENT_SHADER ? "fragment shader"
                                                                                           : "vertex shader", log);
        exit(1);
    }
    free(str);
    printf("shader from: %s compiled\n", path);

    return shader;
}

Shader create_shader(const char *vs_path, const char *fs_path) {
    Shader shader;
    
    shader.vs = compile_shader(vs_path, GL_VERTEX_SHADER);
    shader.fs = compile_shader(fs_path, GL_FRAGMENT_SHADER);
    shader.program = glCreateProgram();
    glAttachShader(shader.program, shader.vs);
    glAttachShader(shader.program, shader.fs);
    glLinkProgram(shader.program);

    i32 compiled = 0;
    char log[512] = {0};
    glGetProgramiv(shader.program, GL_LINK_STATUS, &compiled);
    if (!compiled) {
        glGetProgramInfoLog(shader.program, 512, NULL, log);
        fprintf(stderr, "error linking shader program. error: %s", log);
        exit(1);
    }

    return shader;
}
