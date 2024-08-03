#define STB_IMAGE_IMPLEMENTATION
#include "renderer.h"
#include "defs.h"
#include "shader.h"

rrenderer init_renderer(const char *win_title, int win_w, int win_h) {
    rrenderer renderer = {0};
    renderer.initd = false;
    renderer.win_w = win_w;
    renderer.win_h = win_h;

    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "Failed to initialize SDL. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("Events initialized\n");
    SDL_SetHint(SDL_HINT_IME_IMPLEMENTED_UI, "1");

    renderer.window = SDL_CreateWindow(win_title, 
                                       win_w, win_h, 
                                       SDL_WINDOW_OPENGL | 
                                       SDL_WINDOW_RESIZABLE | 
                                       SDL_WINDOW_HIDDEN);
    if (renderer.window == NULL) {
        fprintf(stderr, "Failed to create SDL_Window. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("SDL_Window created\n");
//  SDL_SetWindowBordered(renderer.window, false);

#if defined(__APPLE__)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);   
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    renderer.gl_ctx = SDL_GL_CreateContext(renderer.window);
    if (renderer.gl_ctx == NULL) {
        fprintf(stderr, "Failed to create GL Context. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("glContext created\n");

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(1);
    }
    printf("GLEW initialized\n");

    SDL_GL_MakeCurrent(renderer.window,  renderer.gl_ctx);
    SDL_GL_SetSwapInterval(1);
    glViewport(0, 0, win_w, win_h);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glm_ortho(0, renderer.win_w, renderer.win_h, 0, -1.f, 1.f, renderer.ortho_proj_mat);

    glGenVertexArrays(1, &renderer.vao);
    glGenBuffers(1, &renderer.vbo);
    glGenBuffers(1, &renderer.ebo);

    renderer.shaders_size = 0;
    renderer.shaders = realloc(renderer.shaders, sizeof(Shader) * (renderer.shaders_size+1));
    renderer.shaders[renderer.shaders_size] = create_shader("shaders/basic_color.vs", "shaders/basic_color.fs");
    renderer.shaders_size++;

    renderer.shaders = realloc(renderer.shaders, sizeof(Shader) * (renderer.shaders_size+1));
    renderer.shaders[renderer.shaders_size] = create_shader("shaders/basic_texture.vs", "shaders/basic_texture.fs");
    renderer.shaders_size++;

    SDL_ShowWindow(renderer.window);

    renderer.initd = true;

    return renderer;
}

void uninit_renderer(rrenderer *renderer) {
    SDL_GL_DestroyContext(renderer->gl_ctx);
    printf("GL context destroyed\n");
    SDL_DestroyWindow(renderer->window);
    printf("SDL_Window destroyed\n");
    SDL_Quit();
}

void render_line(rrenderer renderer, lline line, color_rgb color, f32 alpha) {
    u32 indexes[] = {
        0, 1,
    };

    glUseProgram(renderer.shaders[SHADER_BASIC_COLOR].program);
    shader_uniform_color(renderer.shaders[SHADER_BASIC_COLOR].program, color, alpha);
    shader_uniform_mat4(renderer.shaders[SHADER_BASIC_COLOR].program, renderer.ortho_proj_mat); 

    glBindVertexArray(renderer.vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line), line.p, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_DYNAMIC_DRAW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
}

void render_rect_color(rrenderer renderer, rrect rect, color_rgb color, f32 alpha, bool fill) {
    vec3 v[] = {
        {rect.x,        rect.y,        0.0f},
        {rect.x+rect.w, rect.y,        0.0f},
        {rect.x,        rect.y+rect.h, 0.0f},
        {rect.x+rect.w, rect.y+rect.h, 0.0f},
    };

    u32 indexes[] = {
        0, 1, 2, 
        2, 1, 3,
    };

    glUseProgram(renderer.shaders[SHADER_BASIC_COLOR].program);
    shader_uniform_color(renderer.shaders[SHADER_BASIC_COLOR].program, color, alpha);
    shader_uniform_mat4(renderer.shaders[SHADER_BASIC_COLOR].program, renderer.ortho_proj_mat); 

    glBindVertexArray(renderer.vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_DYNAMIC_DRAW);

    glPolygonMode(GL_FRONT_AND_BACK, fill ? GL_FILL : GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void render_rect_texture(rrenderer renderer, rrect rect, texture tex, f32 alpha) {
    float v[] = {
        rect.x, rect.y, 0.0f, 
        1.0f, 0.0f, 
        rect.x+rect.w, rect.y, 0.0f, 
        0.0f, 0.0f, 
        rect.x, rect.y+rect.h, 0.0f, 
        1.0f, 1.0f, 
        rect.x+rect.w, rect.y+rect.h, 0.0f, 
        0.0f, 1.0f, 
    };


    u32 indexes[] = {
        0, 1, 2, 
        2, 1, 3,
    };

    glUseProgram(renderer.shaders[SHADER_BASIC_TEXTURE].program);
    shader_uniform_color(renderer.shaders[SHADER_BASIC_TEXTURE].program, COLOR_WHITE, alpha); 
    shader_uniform_mat4(renderer.shaders[SHADER_BASIC_TEXTURE].program, renderer.ortho_proj_mat); 

    glBindVertexArray(renderer.vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

//  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(f32)));
//  glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_DYNAMIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.id);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void render_cicle(rrenderer renderer, ccircle circle, color_rgb color, bool wf) {

}
 
texture load_texture(const char *img_file) {
    if (!stbi_info(img_file, 0, 0, 0)) {
        fprintf(stderr, "file %s is not supported\n", img_file);
        exit(1);
    }

    texture tex = {0};
    int channels = 0;

    unsigned char *data = stbi_load(img_file, &tex.width, &tex.height, &channels, 0);
    if (data == NULL) {
        fprintf(stderr, "error loading image: %s\n", img_file);
        exit(1);
    }

    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //check
    //
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    printf("texture from image: %s created\n", img_file);

    return tex;
}

void clear_screen(color_rgb clear_color) {
    glClearColor(clear_color.r, 
                 clear_color.g, 
                 clear_color.b, 
                 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

vec4s color_to_vec4(color_rgb color, f32 alpha) {
    return (vec4s) {
        .r = RGB2F(color.r),
        .g = RGB2F(color.g),
        .b = RGB2F(color.b),
        .a = alpha,
    };
}
