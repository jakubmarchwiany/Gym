#include "receptionist.h"

receptionist::receptionist(gym& g,std::atomic<bool> &done) : g(g), lifeline(&receptionist::work, this),done(done) {}

void receptionist::work(){
    do{
        waitingForClient();

        browsingFacebook();
    }while(!done);

}

void receptionist::browsingFacebook() {
    g.printer.print_receptionist(20, 10);
    g.printer.print_status(203,12,"Receptionist: FB time           ");
    static thread_local std::uniform_int_distribution<> wait(30, 50);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));
    g.printer.clear_receptionist(20, 10);
}

void receptionist::waitingForClient() {


    g.printer.print_receptionist(30, 15);

    std::unique_lock<std::mutex> number_lock(g.getMutexNumber());


    if(g.getCurrentClients() < 10) {
        g.rec.setFree(true);
        g.rec.release();

    }
    number_lock.unlock();


    g.printer.print_status(203,12,"Receptionist: waiting for Client");
    static thread_local std::uniform_int_distribution<> wait(10, 30);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));

    g.printer.clear_receptionist(30, 15);
}

std::thread &receptionist::getLifeline(){
    return lifeline;
}
