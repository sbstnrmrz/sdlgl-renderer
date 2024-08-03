#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "font.h"

ffont load_font(const char *ttf_file) {
    if (strcasecmp(ttf_file + strlen(ttf_file)-4, ".ttf") ) {
        fprintf(stderr, "error loading font. file: %s is not a valid file\n", ttf_file);
        exit(1);
    }

    FILE *f = fopen(ttf_file, "rb");
    if (f == NULL) {
        fprintf(stderr, "error opening file: %s\n", ttf_file);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    byte ttf_buffer[file_size];
    // TODO: error checking
    fread(ttf_buffer, 1, file_size, f);
    fclose(f);

    i32 bmp_w = 512;
    i32 bmp_h = 512;
    byte *tmp_bmp = calloc(bmp_w * bmp_h, sizeof(byte));
    printf("asdasd\n");

    size_t char_count = 96;
    stbtt_bakedchar *char_data = calloc(char_count, sizeof(stbtt_bakedchar));

    stbtt_BakeFontBitmap(ttf_buffer, 0, 32, tmp_bmp, 512, 512, 32, 96, char_data);
    stbi_write_png("free_sans.png", 512, 512, 2, tmp_bmp, 512);
    printf("png writed\n");

    printf("file_size: %zu\n", file_size);

    ffont font = {0};

    return (ffont) {
        .char_data = char_data,
        .char_count = char_count,
        .bmp = tmp_bmp,
        .bmp_w = bmp_w,
        .bmp_h = bmp_h,
    };
} 

void render_text(rrenderer renderer, const char *text, f32 x, f32 y) {


}
