#include "defs.h"
#include "shader.h"

struct {
    SDL_Window    *window;
    SDL_Renderer  *renderer;
    SDL_GLContext ctx;
    bool running;
} sdl;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} rect2d;

int win_w = 800;
int win_h = 600;
u32 vao;
u32 vbo;
u32 ebo;
const char* glsl_version = "#version 330";

void init_renderer(const char *win_title, int win_w, int win_h) {
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "Failed to initialize SDL. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("Events initialized\n");
//  SDL_SetHint(SDL_HINT_IME_IMPLEMENTED_UI, "1");

    sdl.window = SDL_CreateWindow(win_title, win_w, win_h, SDL_WINDOW_OPENGL | 
                                                           SDL_WINDOW_RESIZABLE | 
                                                           SDL_WINDOW_HIDDEN);
    if (sdl.window == NULL) {
        fprintf(stderr, "Failed to create SDL_Window. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("Window created\n");

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
    sdl.ctx = SDL_GL_CreateContext(sdl.window);
    if (sdl.ctx == NULL) {
        fprintf(stderr, "Failed to create GL_Context. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("GL Context created\n");

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(1);
    }
    printf("GLEW initialized\n");

    SDL_GL_MakeCurrent(sdl.window,  sdl.ctx);
    SDL_GL_SetSwapInterval(1);
    glViewport(0, 0, win_w, win_h);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    SDL_ShowWindow(sdl.window);

    sdl.running = true;
}

void render_rect(rect2d rect, bool wireframe) {
    float v[] = {
        rect.x,         rect.y,        0.0f,
        rect.x+rect.w,  rect.y,        0.0f,
        rect.x,         rect.y+rect.h, 0.0f,
        rect.x+rect.w,  rect.y+rect.w, 0.0f,
    };

    u32 indexes[] = {
        0, 1, 2, 
        2, 1, 3,
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_DYNAMIC_DRAW);

    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

int main(int argc, char *argv[]) {
    init_renderer("window", win_w, win_h);

    unsigned int program = glCreateProgram();
    glAttachShader(program, compile_shader("shaders/basic_color.vs", GL_VERTEX_SHADER));
    glAttachShader(program, compile_shader("shaders/basic_color.fs", GL_FRAGMENT_SHADER));
    glLinkProgram(program); 

    while (sdl.running) {
        SDL_Event event;
        SDL_PollEvent(&event);
        const uint8_t *state = SDL_GetKeyboardState(NULL);

        static float x = 0;
        static float y = 0;

        if (event.type == SDL_EVENT_QUIT) {
            sdl.running = false;
        }
        if (state[SDL_SCANCODE_UP]) {
            y += 0.002;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            y -= 0.002;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            x -= 0.002;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            x += 0.002;
        }
        rect2d rect = {
            .x = x,
            .y = y,
            .w = 0.5,
            .h = 0.5,
        };
        rect2d rect2 = {
            .x = 0,
            .y = 0,
            .w = 0.5,
            .h = 0.5,
        };

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        render_rect(rect2, false);
        render_rect(rect, true);
        SDL_GL_SwapWindow(sdl.window);
    }

    SDL_GL_DestroyContext(sdl.ctx);
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();

    return 0;
}
