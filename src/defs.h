#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <cglm/mat4.h>
#include <cglm/mat3.h>
#include <cglm/project.h>
#include <cglm/types.h>
#include <cglm/vec4.h>
#include <cglm/vec3.h>
#include <cglm/vec3.h>
#include <cglm/cam.h>
#include "stb_image.h"

#define LEN(x) sizeof(x)/sizeof(x[0])

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;
typedef unsigned char byte;

typedef struct {
    u32 vs;
    u32 fs;
    u32 program;
} Shader;

typedef struct {
    SDL_Window    *window;
    i32           win_w;
    i32           win_h;
    SDL_GLContext gl_ctx;
    Shader        *shaders;
    size_t        shaders_size;
    u32           vao;
    u32           vbo;
    u32           ebo;
    bool          initd;
    mat4          ortho_proj_mat;
    mat4          pers_proj_mat;
} rrenderer; 

#endif // DEFS_H
