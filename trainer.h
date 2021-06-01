#ifndef UNTITLED3_TRAINER_H
#define UNTITLED3_TRAINER_H

#include "gym.h"
#include "ncurses.h"

class trainer {

    gym& g;
    std::thread lifeline;

    void coffee_time();

    void check();

    void lesson();

    void work();

    void clear(int x, int y);

    void printTrainer(int x, int y);

public:
    trainer(gym &g);
};


#endif
