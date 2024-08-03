#ifndef FONT_H
#define FONT_H

#include "defs.h"
#include "stb_truetype.h"
#include "stb_image_write.h"

typedef struct {
    stbtt_bakedchar *char_data;
    size_t char_count;
    byte *bmp;    
    i32  bmp_w;
    i32  bmp_h;
} ffont;

ffont load_font(const char *ttf_file); 
void render_text(rrenderer renderer, const char *text, f32 x, f32 y);

#endif // FONT_H
