#ifndef UNTITLED3_CLIENT_H
#define UNTITLED3_CLIENT_H

#include <thread>
#include "gym.h"
#include <ncurses.h>

class gym;


class client
{
public:
    client(int id, int numberInline, gym &g);

    int get_id();
    void visit();
    void in_line();
    void reception();

private:

    int id;
    int weight;

    int numberInLine;

    gym& g;

    std::thread lifeline;
    std::mt19937 rng{ std::random_device{}() };

    void printClientClear(int x, int y);

    void printClient(int x, int y, int id);
};

#endif //UNTITLED3_CLIENT_H
