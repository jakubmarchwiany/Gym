#include <iostream>
#include <random>
#include <thread>
#include "place_in_line.h"


place_in_line::place_in_line(int num, int x, int y){
    this->num = num;
    this->x=x;
    this->y=y;
    free = true;
    owner = -1;
}


void place_in_line::request(int other_owner) {
    while (owner != other_owner) {
        if (free) {
            free = false;
            owner = other_owner;
        }
        else {
            channel.wait();
        }
    }
}

int place_in_line::get_owner() {
    return owner;
}

void place_in_line::release() {
    owner = -1;
    free = true;
    channel.notify_all();
}

bool place_in_line::is_free() {
    return free;
}

std::mutex &place_in_line::getMutex() {
    return mutex;
}

int place_in_line::getX(){
    return x;
}

int place_in_line::getY(){
    return y;
}


