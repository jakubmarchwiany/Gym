#ifndef UNTITLED3_DISC_H
#define UNTITLED3_DISC_H


#include <mutex>
#include "sync_channel.h"

class disc {
public:
    disc(int id, int x, int y, int weight);

    bool getIsFree();

    int getWeight();

    int getX();

    int getY();

    void setIsFree(bool isFree);
private:

    int id;
    int x,y;
    int weight;
    bool isFree = true;
};


#endif //UNTITLED3_DISC_H
