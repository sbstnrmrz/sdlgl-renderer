#include "defs.h"
#include "renderer.h"
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

    stbtt_BakeFontBitmap(ttf_buffer, 0, 32, tmp_bmp, bmp_w, bmp_h, 32, 96, char_data);
    stbi_write_png("free_sans.png", 512, 512, 2, tmp_bmp, 512);
    printf("png writed\n");

    texture bmp_tex = {0};
    bmp_tex.width = bmp_w;
    bmp_tex.height = bmp_h;
    bmp_tex.format = GL_ALPHA;

    glGenTextures(1, &bmp_tex.id);
    glBindTexture(GL_TEXTURE_2D, bmp_tex.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bmp_tex.width, bmp_tex.height, 0, GL_RED, GL_UNSIGNED_BYTE, tmp_bmp);
    glGenerateMipmap(GL_TEXTURE_2D);

    printf("file_size: %zu\n", file_size);

    return (ffont) {
        .char_data = char_data,
        .char_count = char_count,
        .bmp_tex = bmp_tex,
    };
} 

// TODO: text overflow and etc
void render_text(rrenderer renderer, ffont *font, char *text, rrect text_rect) {
    while (*text) {
        if (*text >= 32 && *text <= 127) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(font->char_data, 
                               font->bmp_tex.width, 
                               font->bmp_tex.height, 
                               *text-32, 
                               &text_rect.x, 
                               &text_rect.y, 
                               &q, 
                               1);
//          float v[] = {
//              q.x0, q.y0, 0.0f, 
//              1, 0, 
//              q.x1, q.y0, 0.0f, 
//              0, 0, 
//              q.x0, q.y1, 0.0f, 
//              1, 1, 
//              q.x1, q.y1, 0.0f, 
//              0, 1, 
//          };

            float v[] = {
                q.x0, q.y0, 0.0f, 
                q.s0, q.t0, 
                q.x1, q.y0, 0.0f, 
                q.s1, q.t0, 
                q.x0, q.y1, 0.0f, 
                q.s0, q.t1, 
                q.x1, q.y1, 0.0f, 
                q.s1, q.t1, 

            };

            u32 indexes[] = {
                0, 1, 2, 
                2, 1, 3,
            };

            glUseProgram(renderer.shaders[SHADER_BASIC_TEXTURE].program);
            shader_uniform_vec4(renderer.shaders[SHADER_BASIC_TEXTURE].program, COLOR_WHITE); 
            shader_uniform_mat4(renderer.shaders[SHADER_BASIC_TEXTURE].program, renderer.ortho_proj_mat); 

            glBindVertexArray(renderer.vao);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(f32)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_DYNAMIC_DRAW);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, font->bmp_tex.id);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
            
        } else {
            fprintf(stderr, "error rendering text");
            exit(1);
        }
        text++;
    }
}
