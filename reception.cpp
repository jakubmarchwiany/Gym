#include "reception.h"

void reception::request()
{
    while (true) {
        if (free) {
            free = false;
            break;
        } else {
            channel.wait();
        }
    }
}

void reception::release()
{
    channel.notify_all();
}



std::mutex &reception::getMutex(){
    return mutex;
}

void reception::setFree(bool free) {
    reception::free = free;
}
