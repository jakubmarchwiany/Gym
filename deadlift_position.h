//
// Created by kuba on 07.06.2021.
//

#ifndef UNTITLED3_DEADLIFT_POSITION_H
#define UNTITLED3_DEADLIFT_POSITION_H


#include <mutex>

class deadlift_position {
public:
    deadlift_position(int x, int y);

    int getX();

    int getY();

    std::mutex &getMutex();
private:
    int x;
    int y;
    std::mutex mutex;
};


#endif //UNTITLED3_DEADLIFT_POSITION_H
