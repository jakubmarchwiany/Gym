#ifndef UNTITLED3_LOCKER_H
#define UNTITLED3_LOCKER_H

#include <mutex>
#include "sync_channel.h"
#include "ncurses.h"

class locker {
public:
    locker(int id, int x, int y);

    std::mutex &getMutex();


    int getX();
    int getY();

    bool isFree();
    void setIsFree(bool isFree);
    void setOwner(int owner);

private:


    int id;
    int x, y;
    int owner = -1;
    bool is_free = true;
    std::mutex mutex;
    sync_channel channel;
};


#endif //UNTITLED3_LOCKER_H
