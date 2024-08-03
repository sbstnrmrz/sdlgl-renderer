#ifndef RENDERER_H
#define RENDERER_H

#include "defs.h"
#include "shader.h"

#define RGB2F(x) x / 255.f

#define COLOR_RED    (color_rgb) {255, 0, 0}
#define COLOR_GREEN  (color_rgb) {0, 255, 0}
#define COLOR_BLUE   (color_rgb) {0, 0, 255}
#define COLOR_YELLOW (color_rgb) {255, 255, 0}
#define COLOR_VIOLET (color_rgb) {255, 0, 255}
#define COLOR_CYAN   (color_rgb) {0, 255, 255}
#define COLOR_ORANGE (color_rgb) {255, 165, 0}
#define COLOR_BLACK  (color_rgb) {0, 0, 0}
#define COLOR_WHITE  (color_rgb) {255, 255, 255}

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
    mat4          perspective_proj_mat;
} rrenderer; 

typedef struct {
    f32 x; 
    f32 y; 
    f32 w; 
    f32 h; 
} rrect;

typedef struct {
    vec3 p[2];
} lline;

typedef struct {
    f32 cx;
    f32 cy;
    f32 r;
} ccircle;

typedef struct {
    u32 id;
    u32 format;
    i32 channels; 
    i32 width;
    i32 height;
} texture;

rrenderer init_renderer(const char *win_title, int win_w, int win_h);
void uninit_renderer(rrenderer *renderer);
texture load_texture(const char *img_file);
void render_line(rrenderer renderer, lline line, color_rgb color, f32 alpha);
void render_rect_color(rrenderer renderer, rrect rect, color_rgb color, f32 alpha, bool fill);
void render_rect_texture(rrenderer renderer, rrect rect, texture tex, f32 alpha);
void render_cicle(rrenderer renderer, ccircle circle, color_rgb color, bool wf);
void shader_uniform_vec4(u32 shader_program, vec4 vec);
void shader_uniform_mat4(u32 shader_program, mat4 mat);
void clear_screen(color_rgb clear_color);
vec4s color_to_vec4(color_rgb color, f32 alpha);

#endif // RENDERER_H
