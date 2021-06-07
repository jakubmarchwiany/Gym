#include "gym.h"

gym::gym() {

}
void gym::stop(){

    done = true;

    for (auto & client : clients)
        client->getLifeline().join();

    trai->getLifeline().join();
    recept->getLifeline().join();

}

void gym::makeQueue() {

    while (!done) {
        static thread_local std::uniform_int_distribution<> wait(5, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));


        if (clients.size() != line.size()) {
            int first_free{ 0 };

            while (!line.at(first_free).is_free()) {
                first_free++;
            }


            clients.emplace_back(std::make_unique<client>(number_of_client, first_free, *this,done));

            number_of_client++;
        } else {
            break;
        }

    }
}

void gym::makeQueue2() {

    while (!done) {
        static thread_local std::uniform_int_distribution<> wait(5, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));
        int first_free{ 0 };

        while(true) {
            if (line.at(first_free).getMutex().try_lock()) {
                if (line.at(first_free).is_free()) {
                    clients.emplace_back(std::make_unique<client>(number_of_client, first_free, *this, done));
                    number_of_client++;
                }
                line.at(first_free).getMutex().unlock();
                break;
            }
            first_free++;

            if(first_free == 9){
                break;
            }
        }

    }
}

void gym::makeQueue3() {

    while (!done) {
        static thread_local std::uniform_int_distribution<> wait(5, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 200));


        if (line.at(9).getMutex().try_lock()){
            if(line.at(9).is_free()) {
                clients.emplace_back(std::make_unique<client>(number_of_client, 9, *this, done));
                number_of_client++;
            }
            line.at(9).getMutex().unlock();
        }

    }
}

void gym::run() {
    printer.printGym();
    printer.print_closed_locker(lockers.at(0).getX(), lockers.at(0).getY());
    lockers.at(0).setIsFree(false);
    printer.print_closed_locker(lockers.at(2).getX(), lockers.at(2).getY());
    lockers.at(2).setIsFree(false);

    recept = new receptionist(*this,done);
    trai = new trainer(*this,done);
    std::thread sss(&gym::makeQueue3,this);

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

std::mutex &gym::getMutexNumber(){
    return mutex_number;
}









