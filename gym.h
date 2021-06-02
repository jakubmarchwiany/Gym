#ifndef UNTITLED3_GYM_H
#define UNTITLED3_GYM_H

#include <array>
#include <random>
#include <vector>
#include <memory>
#include <ncurses.h>
#include <iostream>
#include <thread>

#include "client.h"
#include "reception.h"
#include "place_in_line.h"
#include "screen_printer.h"
#include "receptionist.h"
#include "locker.h"
#include "crossfit.h"
#include "trainer.h"
#include "bench.h"
#include "load.h"

class client;
class receptionist;
class trainer;



class gym {
public:
    gym();
    void makeQueue();
    void run();

    reception rec;

    receptionist *recept;

    crossfit cross;

    trainer* trai;

    std::mutex mutex_print;
    std::mutex mutex_number;


    screen_printer printer;
    int getCurrentClients();

    std::array<place_in_line, 10> &getLine();


    std::array<load, 14> &getLoads();

    std::array<bench, 3> &getBenches();
    std::array<locker, 17> &getLockers();


    void setCurrentClients(int currentClients);

private:
    std::atomic<bool> done = false;
    int number_of_client{ 0 };
    int current_clients{0};


    std::mt19937 rng{ std::random_device{}() };

    std::array<bench,3> benches {
        bench(26,50),
        bench(41,50),
        bench(56,50)
    };

    std::array<load,14> loads {
            load(1, 20 , 65,5),
            load(2, 20 , 67,5),
            load(3, 20 , 69,5),
            load(4, 20 , 71,5),
            load(5, 25 , 65,10),
            load(6, 25 , 67,10),
            load(7, 25 , 69,10),
            load(8, 25 , 71,10),
            load(9, 25 , 65,20),
            load(10, 30 , 67,20),
            load(11, 30 , 69,20),
            load(12, 30 , 71,20),
            load(13, 35 , 65,40),
            load(14, 30 , 67,40),
    };



    std::vector<std::unique_ptr<client>> clients;
    std::array<place_in_line, 10> line {
            place_in_line(1,10,26),
            place_in_line(2,10,22),
            place_in_line(3,10,18),
            place_in_line(4,10,14),
            place_in_line(5,10,10),
            place_in_line(6,10,6),
            place_in_line(7,4,6),
            place_in_line(8,4,10),
            place_in_line(9,4,14),
            place_in_line(10,4,18)
    };

    std::array<locker, 17> lockers {
            locker(1,51,6),
            locker(2,58,6),
            locker(3,65,6),
            locker(4,72,6),
            locker(5,79,6),
            locker(6,86,6),
            locker(7,93,6),
            locker(8,100,6),
            locker(9,107,6),
            locker(10,114,6),
            locker(11,121,6),
            locker(12,86,13),
            locker(13,93,13),
            locker(14,100,13),
            locker(15,107,13),
            locker(16,114,13),
            locker(17,121,13)
    };


};

#endif //UNTITLED3_GYM_H
