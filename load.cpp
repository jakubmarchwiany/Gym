#include "load.h"

load::load(int id, int x, int y, int weight) : id(id), x(x), y(y), weight(weight) {}

int load::request()
{
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        if (isFree) {
            isFree = false;
            lock.unlock();
            return 0;
        } else if (attempt == 5) {
            lock.unlock();
            return 1;
        } else{
            lock.unlock();
            channel.wait();
        }
    }
}

void load::done_using()
{
    isFree = true;
    channel.notify_all();
}

std::mutex &load::getMutex(){
    return mutex;
}

