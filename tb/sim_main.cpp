#include <memory>
#include <iostream>
#include <fstream>

#include <verilated.h>
#include "Vtop_tb.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"
#include "renderer.h"

static inline void tick(std::unique_ptr<VerilatedContext> const& contextp, std::unique_ptr<Vtop_tb> const& top) {
    contextp->timeInc(1);
    top->clk = !top->clk;
    top->eval();
}

int main(int argc, char** argv, char** env) {
    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
    contextp->traceEverOn(true);
    contextp->commandArgs(argc, argv);
    contextp->fatalOnError(false);

    const std::unique_ptr<Vtop_tb> top{new Vtop_tb{contextp.get(), "vtop"}};

    screen_t screen;
    screen = start_screen();

    top->clk = 1;
    top->rst = 1;
    tick(contextp, top);
    tick(contextp, top);
    top->rst = 0;

    for (int i=0; i < 200; ++i) {
        while (top->draw_y < VERTICAL_RESOLUTION) {
            tick(contextp, top);
            tick(contextp, top);
            if (top->draw_x < HORIZONTAL_RESOLUTION) {
                screen[top->draw_y][top->draw_x][0] = ((int)top->VGA_R) << 4;
                screen[top->draw_y][top->draw_x][1] = ((int)top->VGA_G) << 4;
                screen[top->draw_y][top->draw_x][2] = ((int)top->VGA_B) << 4;
            }
        }

        draw_screen();

        while (top->draw_y != 0) {
            tick(contextp, top);
            tick(contextp, top);
        }
    }

    top->final();
    contextp->statsPrintSummary();

    close_screen();
    free(screen);

    return contextp->gotError() ? EXIT_FAILURE : 0;
}
