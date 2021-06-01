#include <thread>
#include "crossfit.h"

void crossfit::wait_for_training()
{
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        if (start) {
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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