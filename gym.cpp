#include "gym.h"

gym::gym() {

}

void gym::makeQueue() {

    while (true) {
        static thread_local std::uniform_int_distribution<> wait(5, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));


        if (clients.size() != line.size()) {
            int first_free{ 0 };

            while (!line.at(first_free).is_free()) {
                first_free++;
            }

//            if (number_of_client == 3)
//                rec.info();

            clients.emplace_back(std::make_unique<client>(number_of_client, first_free, *this));

            number_of_client++;
        } else {
            break;
        }

    }
}

void gym::run() {
    printer.printGym();
    std::thread sss(&gym::makeQueue,this);
    recept = new receptionist(*this);
    trai = new trainer(*this);


    sss.join();
}

std::array<place_in_line, 10> &gym::getLine() {
    return line;
}

int gym::getCurrentClients(){
    return current_clients;
}

void gym::setCurrentClients(int currentClients) {
    current_clients = currentClients;
}

std::array<locker, 17> &gym::getLockers()  {
    return lockers;
}

std::array<bench, 3> &gym::getBenches(){
    return benches;
}







