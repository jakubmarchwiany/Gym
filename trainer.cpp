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
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        std::unique_lock<std::mutex> lock2(g.cross.getMutex());
        g.cross.setStart(false);
        g.cross.setClients(0);
        lock2.unlock();

    }else if (g.cross.getClients() > 0){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        mvprintw(15,205,"Ilosc prob %d",g.cross.attempt);
        g.cross.setAttempt(g.cross.getAttempt()+1);
        lock.unlock();
        g.cross.info();
    }else{
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        lock.unlock();
        g.cross.info();
    }

    g.printer.clear_trainer(162, 10);
}



std::thread &trainer::getLifeline(){
    return lifeline;
}
