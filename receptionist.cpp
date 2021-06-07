#include "receptionist.h"

receptionist::receptionist(gym& g,std::atomic<bool> &done) : g(g), lifeline(&receptionist::work, this),done(done) {}

void receptionist::work(){
    do{
        waitingForClient();

        browsingFacebook();
    }while(!done);

}

void receptionist::browsingFacebook() {
    g.printer.print_receptionist(30, 15);
    std::this_thread::sleep_for(std::chrono::milliseconds(2870));
    g.printer.clear_receptionist(30, 15);
}

void receptionist::waitingForClient() {
    g.printer.print_receptionist(20, 10);

    std::this_thread::sleep_for(std::chrono::milliseconds(2960));

    std::unique_lock<std::mutex> number_lock(g.getMutexNumber());


    if(g.getCurrentClients() < 5) {
        g.rec.setFree(true);
        g.rec.release();

    }
    number_lock.unlock();
    g.printer.clear_receptionist(20, 10);


}

std::thread &receptionist::getLifeline(){
    return lifeline;
}
