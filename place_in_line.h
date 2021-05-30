//
// Created by kuba on 28.05.2021.
//

#ifndef UNTITLED3_PLACE_IN_LINE_H
#define UNTITLED3_PLACE_IN_LINE_H

#include <mutex>
#include "sync_channel.h"

class place_in_line
{
public:
    place_in_line(int num, int x, int y);

    void request(int other_owner);
    void release();
    std::mutex &getMutex();
    bool is_free();
    int get_owner();

    int getX() const;

    int getY() const;

private:
    int num;
    int x,y;
    int owner;
    bool free;
    std::mutex mutex;
    sync_channel channel;
    std::mt19937 rng{ std::random_device{}() };
};


#endif //UNTITLED3_PLACE_IN_LINE_H
