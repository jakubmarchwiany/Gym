#include "reception.h"
#include <iostream>
#include <thread>



void reception::request(int other_owner)
{
    while (owner != other_owner) {
        if (free) {
            free = false;
            owner = other_owner;
        } else {
            channel.wait();
        }
    }
}

void reception::release()
{
    owner= -1;
    free = true;
    channel.notify_all();
}



std::mutex &reception::getMutex(){
    return mutex;
}
