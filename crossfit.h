#ifndef UNTITLED3_CROSSFIT_H
#define UNTITLED3_CROSSFIT_H

#include "sync_channel.h"

class crossfit {
public:
    bool start = false;
    int attempt = 0;
    int clients = 0;

    std::mutex mutex;
    sync_channel channel;

    void wait_for_training();
    void info();
};

#endif //UNTITLED3_CROSSFIT_H
