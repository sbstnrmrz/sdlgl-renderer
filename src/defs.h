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
#include <cglm/types-struct.h>
#include <cglm/cam.h>
#include "stb_image.h"
#include "types.h"

#define LEN(x) sizeof(x)/sizeof(x[0])

typedef struct {
    u32 vs;
    u32 fs;
    u32 program;
} Shader;

#endif // DEFS_H
