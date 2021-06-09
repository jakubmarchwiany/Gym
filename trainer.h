#ifndef UNTITLED3_TRAINER_H
#define UNTITLED3_TRAINER_H

#include "gym.h"
#include "ncurses.h"

class trainer {
public:
    std::thread &getLifeline();
    trainer(gym &g,std::atomic<bool> &done);
private:

    gym& g;
    std::thread lifeline;
    std::atomic<bool> &done;
    std::mt19937 rng{ std::random_device{}() };

    void coffee_time();
    void check();
    void work();
};


#endif
