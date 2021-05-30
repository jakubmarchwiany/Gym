//
// Created by kuba on 30.05.2021.
//

#ifndef UNTITLED3_RECEPTIONIST_H
#define UNTITLED3_RECEPTIONIST_H


#include "gym.h"
#include "ncurses.h"

class gym;

class receptionist {

    void work();
    void browsingFacebook();
    void waitingForClient();


    gym& g;
    int id = -1;
    std::thread lifeline;

    void printReceptionist(int x, int y);

    void clear(int x, int y);



public:
    receptionist(gym &g);
};


#endif //UNTITLED3_RECEPTIONIST_H
