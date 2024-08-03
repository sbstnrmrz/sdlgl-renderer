#ifndef FONT_H
#define FONT_H

#include "defs.h"
#include "renderer.h"
#include "stb_truetype.h"
#include "stb_image_write.h"

typedef struct {
    stbtt_bakedchar *char_data;
    size_t char_count;
    texture bmp_tex;
} ffont;

ffont load_font(const char *ttf_file); 
void render_text(rrenderer renderer, ffont *font, char *text, rrect rect);

#endif // FONT_H
