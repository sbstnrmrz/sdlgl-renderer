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

rrenderer init_renderer(const char *win_title, int win_w, int win_h);
void uninit_renderer(rrenderer *renderer);
void render_rect(rrenderer renderer, rrect rect, color_rgb color, bool wf);
void shader_uniform_vec4(u32 shader_program, color_rgb color);

#endif // RENDERER_H
