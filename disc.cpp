#include "disc.h"

disc::disc(int id,int x, int y, int weight) : id(id), x(x), y(y), weight(weight) {}

bool disc::getIsFree(){
    return isFree;
}

void disc::setIsFree(bool isFree) {
    disc::isFree = isFree;
}

int disc::getWeight(){
    return weight;
}

int disc::getX(){
    return x;
}

int disc::getY(){
    return y;
}






