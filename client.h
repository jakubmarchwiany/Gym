#ifndef UNTITLED3_CLIENT_H
#define UNTITLED3_CLIENT_H

#include <thread>
#include "gym.h"
#include <ncurses.h>
#include "locker.h"

class gym;


class client
{
public:
    client(int id, int numberInline, gym &g);

    int get_id();
    void visit();
    void in_line();
    void reception();
    void locker_room();
    void training();

private:

    int id;
    int weight;

    int numberInLine;
    int number_of_action;

    gym& g;

    std::thread lifeline;
    std::mt19937 rng{ std::random_device{}() };

    void printClientClear(int x, int y);

    void printClient(int x, int y, int id);

    void print_lock_locker(int x, int y);


    void crossfit();

    void chest_press();
};

#endif //UNTITLED3_CLIENT_H
