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

typedef struct {
    u32 vs;
    u32 fs;
    u32 program;
} Shader;

typedef struct {
    SDL_Window    *window;
    i32            win_w;
    i32            win_h;
    SDL_GLContext gl_ctx;
    Shader        *shaders;
    size_t        shaders_size;
    u32           vao;
    u32           vbo;
    u32           ebo;
    bool          initd;
} rrenderer; 

#endif // DEFS_H
