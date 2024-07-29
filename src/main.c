#include "defs.h"
#include "shader.h"
#include "renderer.h"

rrenderer renderer = {0};

int win_w = 800;
int win_h = 600;

int main(int argc, char *argv[]) {
    rrenderer renderer = init_renderer("window", win_w, win_h);

    while (renderer.initd) {
        SDL_Event event;
        SDL_PollEvent(&event);
        const uint8_t *state = SDL_GetKeyboardState(NULL);

        static float x = 0;
        static float y = 0;

        if (event.type == SDL_EVENT_QUIT) {
            renderer.initd = false;
        }
        if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            SDL_GetWindowSize(renderer.window, &win_w, &win_h);
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
        rrect rect = {
            .x = x,
            .y = y,
            .w = 0.5,
            .h = 0.5,
        };
        rrect rect2 = {
            .x = 0,
            .y = 0,
            .w = 0.5,
            .h = 0.5,
        };

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        render_rect(renderer, rect2, COLOR_RED, false);
        render_rect(renderer, rect, COLOR_BLUE, true);
        SDL_GL_SwapWindow(renderer.window);
    }

    uninit_renderer(&renderer);

    return 0;
}
