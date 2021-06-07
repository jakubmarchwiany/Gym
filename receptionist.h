#ifndef UNTITLED3_RECEPTIONIST_H
#define UNTITLED3_RECEPTIONIST_H


#include "gym.h"
#include "ncurses.h"

class gym;

class receptionist {
public:
    receptionist(gym &g,std::atomic<bool> &done);


    std::thread &getLifeline();
private:
    int id = -1;
    std::thread lifeline;

    gym& g;
    std::atomic<bool> &done;


    void work();
    void browsingFacebook();
    void waitingForClient();
};


#endif
