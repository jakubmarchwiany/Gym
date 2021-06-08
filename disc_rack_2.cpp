//
// Created by kuba on 07.06.2021.
//

#include "disc_rack_2.h"

std::vector<int> disc_rack_2::request(int weight)
{

    int attempt = 0;
    while (true) {

        std::unique_lock<std::mutex> lock(mutex);
        if (std::vector<int> disces = try_get_disces(weight); !disces.empty()){

            lock.unlock();

            // udało się wziąć ciężar
            return disces;
        }else if (attempt == 5){
            lock.unlock();
            //nie udało się wziąc ciężarów

            return disces;
        }else{
            attempt++;
            lock.unlock();
            channel.wait();
        }
    }
}

void disc_rack_2::put_back(std::vector<int> disces)
{
    std::unique_lock<std::mutex> lock(mutex);
    for(const auto& d: disces)
        loads[d].setIsFree(true);
    lock.unlock();
    channel.notify_all();
}


std::vector<int> disc_rack_2::try_get_disces(int weight){

    //60kg

    int half_weight = weight / 2;
    std::vector<int> taken;
    int current_left_weight = 0;
    int current_right_weight = 0;
    bool not_found = false;
    for (int i = loads.size() - 1; i >= 0; --i) {
        if (loads[i].getIsFree() && loads[i].getWeight() + current_left_weight <= half_weight) {
            loads[i].setIsFree(false);
            current_left_weight += loads[i].getWeight();
            taken.push_back(i);
        }

        if (current_left_weight == half_weight)
            break;

        if (i == 0)
            not_found = true;
    }



    if (not_found){
        for (int i = taken.size() - 1; i >= 0; --i)
            loads[taken.at(i)].setIsFree(true);

        taken.clear();
        return taken;

    }else {
        for (int i = loads.size() - 1; i >= 0; --i) {
            if (loads[i].getIsFree() && loads[i].getWeight() + current_right_weight <= half_weight) {
                loads[i].setIsFree(false);
                current_right_weight += loads[i].getWeight();
                taken.push_back(i);
            }

            if (current_right_weight == half_weight)
                break;

            if (i == 0)
                not_found = true;
        }

    }

    if (not_found) {
        for (int i = taken.size() - 1; i >= 0; --i)
            loads[taken.at(i)].setIsFree(true);

        taken.clear();
    }


    return taken;


}

std::array<disc, 14> &disc_rack_2::getLoads(){
    return loads;
}