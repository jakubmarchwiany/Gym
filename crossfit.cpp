#include <thread>
#include "crossfit.h"
#include "ncurses.h"

void crossfit::wait_for_training()
{
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        if (start) {
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        } else if (attempt == 5) {
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        } else{
            lock.unlock();
            channel.wait();
        }
    }
}

void crossfit::info()
{
    channel.notify_all();
}

bool crossfit::isStart(){
    return start;
}

int crossfit::getAttempt(){
    return attempt;
}

int crossfit::getClients(){
    return clients;
}

std::mutex &crossfit::getMutex(){
    return mutex;
}

void crossfit::setStart(bool start) {
    crossfit::start = start;
}

void crossfit::setAttempt(int attempt) {
    crossfit::attempt = attempt;
}

void crossfit::setClients(int clients) {
    crossfit::clients = clients;
}


