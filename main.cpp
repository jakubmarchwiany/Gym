#include <iostream>
#include <ncurses.h>
#include "gym.h"

void prepareSimulation(){
    std::cout << "\e[8;65;238t";
    initscr();
    refresh();

    if(!has_colors())
        printw("not support color");

    start_color();
    resizeterm(64,237);

    gym g;

    g.run();

    int ch = 0;

    do {
        ch = getch();
    } while(ch != 27);

    g.stop();

}

int main() {

    prepareSimulation();

    return 0;
}



