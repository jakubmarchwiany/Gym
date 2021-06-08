//
// Created by kuba on 07.06.2021.
//

#include "deadlift_position.h"
deadlift_position::deadlift_position(int x, int y){
    this->x=x;
    this->y=y;
}

int deadlift_position::getX(){
    return x;
}

int deadlift_position::getY(){
    return y;
}

std::mutex &deadlift_position::getMutex(){
    return mutex;
}