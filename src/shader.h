#ifndef SHADER_H
#define SHADER_H

#include "defs.h"

typedef enum {
    SHADER_BASIC_COLOR,
    SHADER_BASIC_TEXTURE,
} shader_id;

u32 compile_shader(const char *path, GLenum shader_type);
Shader create_shader(const char *vs_path, const char *fs_path);
void shader_uniform_vec4(u32 shader_program, vec4 vec);
void shader_uniform_color(u32 shader_program, color_rgb color, f32 alpha);
void shader_uniform_mat4(u32 shader_program, mat4 mat);

#endif // SHADER_H
