#include "defs.h"
#include "renderer.h"

rrenderer renderer = {0};

int win_w = 800;
int win_h = 600;

int main(int argc, char *argv[]) {
    rrenderer renderer = init_renderer("window", win_w, win_h);
    texture tex = load_texture("awesomeface.png");

    while (renderer.initd) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                renderer.initd = false;
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                SDL_GetWindowSize(renderer.window, &renderer.win_w, &renderer.win_h);
                glViewport(0, 0, renderer.win_w, renderer.win_h);
            }

        }
        const u8 *state = SDL_GetKeyboardState(NULL);

        static float x = 0;
        static float y = 0;

        if (state[SDL_SCANCODE_UP]) {
            y -= 1;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            y += 1;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            x -= 1;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            x += 1;
        }
        static f32 x1 = 0;
        static f32 y1 = 0;
        rrect rect = {
            .x = x1,
            .y = y1,
            .w = 200,
            .h = 200,
        };

        x1 += 5;
        y1 += 5;
//      printf("x: %.2f | y: %.2f\n", x, y);
//      printf("win_w: %d | win_h: %d\n", renderer.win_w, renderer.win_h);
        if (x1 <= 0 || x1 >= renderer.win_w) {
            x1 *= -1; 
        }
        if (y1 <= 0 || y1+200 >= renderer.win_h) {
            y1 *= -1; 
        }

        rrect rect2 = {
            .x = 400 + x,
            .y = 300 + y,
            .w = 1,
            .h = 1,
        };

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        render_rect_color(renderer, rect2, COLOR_RED, true);
        render_rect_texture(renderer, rect, tex);

        SDL_GL_SwapWindow(renderer.window);
    }

    uninit_renderer(&renderer);

    return 0;
}
