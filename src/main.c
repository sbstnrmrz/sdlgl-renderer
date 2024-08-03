#include "defs.h"
#include "renderer.h"
#include "font.h"

rrenderer renderer = {0};

int win_w = 800;
int win_h = 600;

int main(int argc, char *argv[]) {
    rrenderer renderer = init_renderer("window", win_w, win_h);
    texture tex = load_texture("awesomeface.png");
    ffont font = load_font("fonts/FreeSans.ttf");

    while (renderer.initd) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                renderer.initd = false;
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                SDL_GetWindowSize(renderer.window, &renderer.win_w, &renderer.win_h);
                glViewport(0, 0, renderer.win_w, renderer.win_h);
                glm_ortho(0, renderer.win_w, renderer.win_h, 0, -1.f, 1.f, renderer.ortho_proj_mat);
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
            .w = 100,
            .h = 100,
        };

        rrect rect3 = {
            .x = 50,
            .y = 50,
            .w = 100,
            .h = 100,
        };

        rrect rect2 = {
            .x = 0 + x,
            .y = 0 + y,
            .w = 10,
            .h = 10,
        };

        lline line = {
            .p = {
                400, 300, 0,
                600, 400, 0
            }
        };

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
//      render_rect_color(renderer, rect2, COLOR_RED, true);
//      render_line(renderer, line, COLOR_RED);
//      render_rect_texture(renderer, rect, tex);
//      render_rect_texture(renderer, rect3, tex);
        rrect r = {
            .x = 30,
            .y = 30,
            .w = 1,
            .h = 2,
        };
        render_text(renderer, &font, "quesoconpan", r);

        SDL_GL_SwapWindow(renderer.window);
    }

    uninit_renderer(&renderer);

    return 0;
}
