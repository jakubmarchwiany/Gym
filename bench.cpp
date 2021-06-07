#include "bench.h"
bench::bench(int x, int y){
    this->x=x;
    this->y=y;
}

int bench::getX(){
    return x;
}

int bench::getY(){
    return y;
}

std::mutex &bench::getMutex(){
    return mutex;
}
