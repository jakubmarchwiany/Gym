#include "trainer.h"

trainer::trainer(gym& g,std::atomic<bool> &done) : g(g), lifeline(&trainer::work, this),done(done) {}

void trainer::work(){
    do{
        coffee_time();
        check();
    }while(!done);
}

void trainer::coffee_time() {
    g.printer.print_trainer(43, 13);
    g.printer.print_status(203,14,"Trainer: coffee_time");
    static thread_local std::uniform_int_distribution<> wait(40, 50);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));
    g.printer.clear_trainer(43, 13);
}

void trainer::check() {
    g.printer.print_trainer(162, 10);

    std::unique_lock<std::mutex> lock(g.cross.getMutex());
    if (g.cross.getClients()== 3){
        g.cross.setAttempt(0);
        g.cross.setStart(true);
        lock.unlock();
        g.cross.info();
        g.printer.print_status(203,14,"Trainer: crossfit   ");
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));

        std::unique_lock<std::mutex> lock2(g.cross.getMutex());
        g.cross.setStart(false);
        g.cross.setClients(0);
        lock2.unlock();

    }else if (g.cross.getClients() > 0){
//        mvprintw(15,205,"Ilosc prob %d",g.cross.attempt);
        g.cross.setAttempt(g.cross.getAttempt()+1);
        g.printer.print_status_value(203,14,"Trainer: try: %d    ",g.cross.getAttempt());
        lock.unlock();
        g.cross.info();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    }else{
        g.printer.print_status(203,14,"Trainer: check      ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        lock.unlock();
        g.cross.info();
    }

    g.printer.clear_trainer(162, 10);
}



std::thread &trainer::getLifeline(){
    return lifeline;
}
