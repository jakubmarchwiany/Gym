#ifndef UNTITLED3_RECEPTION_H
#define UNTITLED3_RECEPTION_H

#include <atomic>
#include <mutex>
#include <random>
#include <thread>
#include "sync_channel.h"

class reception {
public:
    void request();
    void release();

    void setFree(bool free);
    std::mutex &getMutex();
private:
    int owner=-1;
    bool free {true};
    std::mutex mutex;
    sync_channel channel;
    std::mt19937 rng{ std::random_device{}() };
};

#endif
