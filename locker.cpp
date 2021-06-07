#include "locker.h"

locker::locker(int id, int x, int y) : id(id), x(x), y(y) {}

std::mutex &locker::getMutex(){
    return mutex;
}

int locker::getX(){
    return x;
}

int locker::getY(){
    return y;
}

bool locker::isFree(){
    return is_free;
}

void locker::setIsFree(bool isFree) {
    is_free = isFree;
}

void locker::setOwner(int owner) {
    locker::owner = owner;
}

int locker::getId(){
    return id;
}
