//
// Created by kuba on 02.06.2021.
//

#ifndef UNTITLED3_DISC_RACK_H
#define UNTITLED3_DISC_RACK_H


#include <mutex>
#include "disc.h"

class disc_rack {
public:


    std::vector<int> request(int weight);
    void put_back(std::vector<int> disces);


    std::vector<int> try_get_disces(int weight);

    std::array<disc, 14> &getLoads();

private:
    std::mutex mutex;
    sync_channel channel;

    std::array<disc,14> loads {
            disc(0,20 , 37, 5),
            disc(1,20 , 39, 5),
            disc(2,20 , 41, 5),
            disc(3,20 , 43, 5),
            disc(4,25 , 37, 10),
            disc(5,25 , 39, 10),
            disc(6,25 , 41, 10),
            disc(7,25 , 43, 10),
            disc(8,25 , 37, 20),
            disc(9,30 , 39, 20),
            disc(10,30 , 41, 20),
            disc(11,30 , 43, 20),
            disc(12,35 , 37, 40),
            disc(13,35 , 39, 40),
    };

};


#endif //UNTITLED3_DISC_RACK_H
