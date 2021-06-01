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

    std::atomic<bool> receptionIsFree {false};
    std::array<place_in_line, 10> &getLine();



    int getCurrentClients();

    std::array<locker, 17> &getLockers();

    void setCurrentClients(int currentClients);

private:
    int number_of_client{ 0 };
    int current_clients{0};


    std::mt19937 rng{ std::random_device{}() };

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
