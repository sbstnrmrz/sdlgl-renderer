#ifndef SHADER_H
#define SHADER_H

#include "defs.h"

u32 compile_shader(const char *path, GLenum shader_type);
Shader create_shader(const char *vs_path, const char *fs_path);

#endif // SHADER_H
