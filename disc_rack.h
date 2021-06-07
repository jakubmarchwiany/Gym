//
// Created by kuba on 02.06.2021.
//

#ifndef UNTITLED3_DISC_RACK_H
#define UNTITLED3_DISC_RACK_H


#include <mutex>
#include "disc.h"

class disc_rack {
public:

    void request();
    void info();

    std::mutex mutex;
    sync_channel channel;

    std::array<disc,14> loads {
            disc(1,20 , 65, 5),
            disc(2,20 , 67, 5),
            disc(3,20 , 69, 5),
            disc(4,20 , 71, 5),
            disc(5,25 , 65, 10),
            disc(6,25 , 67, 10),
            disc(7,25 , 69, 10),
            disc(8,25 , 71, 10),
            disc(9,25 , 65, 20),
            disc(10,30 , 67, 20),
            disc(11,30 , 69, 20),
            disc(12,30 , 71, 20),
            disc(13,35 , 65, 40),
            disc(14,30 , 67, 40),
    };

    int request(int weight);

    std::vector<int> try_get_disces(int weight);

private:

};


#endif //UNTITLED3_DISC_RACK_H
