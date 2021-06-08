//
// Created by kuba on 07.06.2021.
//

#ifndef UNTITLED3_DISC_RACK_2_H
#define UNTITLED3_DISC_RACK_2_H

#include <mutex>
#include <vector>
#include "disc.h"

class disc_rack_2 {
public:


    std::vector<int> request(int weight);
    void put_back(std::vector<int> disces);


    std::vector<int> try_get_disces(int weight);

    std::array<disc, 14> &getLoads();

private:
    std::mutex mutex;
    sync_channel channel;

    std::array<disc,14> loads {
            disc(0,94 , 37, 5),
            disc(1,94 , 39, 5),
            disc(2,94 , 41, 5),
            disc(3,94 , 43, 5),
            disc(4,99 , 37, 10),
            disc(5,99 , 39, 10),
            disc(6,99 , 41, 10),
            disc(7,99 , 43, 10),
            disc(8,104 , 37, 20),
            disc(9,104 , 39, 20),
            disc(10,104 , 41, 20),
            disc(11,104 , 43, 20),
            disc(12,109 , 37, 40),
            disc(13,109 , 39, 40),
    };

};


#endif //UNTITLED3_DISC_RACK_2_H
