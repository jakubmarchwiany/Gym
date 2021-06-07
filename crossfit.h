#ifndef UNTITLED3_CROSSFIT_H
#define UNTITLED3_CROSSFIT_H

#include "sync_channel.h"

class crossfit {
public:

    void wait_for_training();
    void info();

    bool isStart();
    int getAttempt();
    int getClients();

    void setStart(bool start);
    void setAttempt(int attempt);
    void setClients(int clients);

    std::mutex &getMutex();

private:

    bool start = false;
    int attempt = 0;
    int clients = 0;

    std::mutex mutex;
    sync_channel channel;
};

#endif //UNTITLED3_CROSSFIT_H
