#ifndef UNTITLED3_CLIENT_H
#define UNTITLED3_CLIENT_H

#include <thread>
#include "gym.h"
#include <ncurses.h>
#include "locker.h"
#include "disc.h"
#include "bench.h"

class gym;

class client
{
public:
    client(int id, int numberInline, gym &g,std::atomic<bool> &done);

    int get_id();
    std::thread &getLifeline();

private:

    int id;
    int weight;
    int number_in_Line, number_lock, number_of_action;

    gym& g;

    std::atomic<bool> &done;
    std::thread lifeline;
    std::mt19937 rng{ std::random_device{}() };

// Metody używane do życia wątku
    void visit();
    void in_line();
    void reception();
    void locker_room();
    void training();
    void crossfit();
    void take_bench();
    void chest_press(bench &ben);
    void leave();
};

#endif //UNTITLED3_CLIENT_H
