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

class client;
class receptionist;

class gym {
public:
    gym();
    void makeQueue();
    void run();

    reception rec;

    receptionist *recept;

    std::mutex mutex_print;


    screen_printer printer;

    std::atomic<bool> receptionIsFree {false};
    std::array<place_in_line, 10> &getLine();

    std::mutex mutex_number;

    int getCurrentClients() const;

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
};

#endif //UNTITLED3_GYM_H
