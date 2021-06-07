//
// Created by kuba on 02.06.2021.
//

#include <vector>
#include "disc_rack.h"
int disc_rack::request(int weight)
{
    int attempt = 0;
    while (true) {

        std::unique_lock<std::mutex> lock(mutex);
        if (try_get_disces(weight)) {
            lock.unlock();

            // udało się wziąć ciężar
            return 0;
        }else if (attempt == 5){
            lock.unlock();
            //nie udało się wziąc ciężarów

            return 0;
        }else{
            attempt++;
            lock.unlock();
            channel.wait();
        }
    }
}

void disc_rack::info()
{
    channel.notify_all();
}


std::vector<int> disc_rack::try_get_disces(int weight){

    //60kg

    int half_weight = weight / 2;
    std::vector<int> taken;
    int current_left_weight = 0;
    int current_right_weight = 0;
    bool not_found = false;
    for (std::size_t i = loads.size(); i > 0; --i) {
        if (loads[i].getIsFree() && loads[i].weight + current_left_weight <= half_weight) {
            loads[i].setIsFree(false);
            taken.push_back(i);
        }

        if (current_left_weight == half_weight)
            break;

        if (i == loads.size())
            not_found = true;
    }

    if (not_found){
        taken.clear();
        return taken;

    }else {
        for (std::size_t i = loads.size(); i > 0; --i) {
            if (loads[i].getIsFree() && loads[i].weight + current_right_weight <= half_weight) {
                loads[i].setIsFree(false);
                taken.push_back(i);
            }

            if (current_left_weight == half_weight)
                break;

            if (i == loads.size())
                not_found = true;
        }

    }


}