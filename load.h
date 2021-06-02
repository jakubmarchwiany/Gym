#ifndef UNTITLED3_LOAD_H
#define UNTITLED3_LOAD_H


#include <mutex>
#include "sync_channel.h"

class load {

public:
    load(int id, int x, int y, int weight);

    int request();
    void done_using();

    std::mutex &getMutex();
    int x,y;
    int weight;
private:

    int id;


    int owner;

    bool isFree=true;
    int attempt = 0;

    std::mutex mutex;
    sync_channel channel;
};


#endif //UNTITLED3_LOAD_H
