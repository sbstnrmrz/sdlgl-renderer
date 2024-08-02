#ifndef RENDERER_H
#define RENDERER_H

#include "defs.h"
#include "shader.h"

#define RGB2F(x) x / 256.f

#define COLOR_RED    (color_rgb) {255, 0, 0}
#define COLOR_GREEN  (color_rgb) {0, 255, 0}
#define COLOR_BLUE   (color_rgb) {0, 0, 255}
#define COLOR_YELLOW (color_rgb) {255, 255, 0}
#define COLOR_VIOLET (color_rgb) {255, 0, 255}
#define COLOR_CYAN   (color_rgb) {0, 255, 255}
#define COLOR_BLACK  (color_rgb) {0, 0, 0}
#define COLOR_WHITE  (color_rgb) {255, 255, 255}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} color_rgb;

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
void render_line(rrenderer renderer, lline line, color_rgb color);
void render_rect_color(rrenderer renderer, rrect rect, color_rgb color, bool fill);
void render_rect_texture(rrenderer renderer, rrect rect, texture tex);
void render_cicle(rrenderer renderer, ccircle circle, color_rgb color, bool wf);
void shader_uniform_vec4(u32 shader_program, color_rgb color);
void shader_uniform_mat4(u32 shader_program, mat4 proj_mat);

#endif // RENDERER_H
