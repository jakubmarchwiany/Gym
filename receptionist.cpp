//
// Created by kuba on 30.05.2021.
//

#include "receptionist.h"

receptionist::receptionist(gym& g) : g(g), lifeline(&receptionist::work, this) {}

void receptionist::printReceptionist(int x, int y) {
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(9,COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(9));
    mvprintw(y,x,"    ");
    mvprintw(y+1,x,"    ");
    attroff(COLOR_PAIR(9));
    refresh();
}

void receptionist::clear(int x, int y) {
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(10,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(10));
    mvprintw(y,x,"    ");
    mvprintw(y+1,x,"    ");
    attroff(COLOR_PAIR(10));
    refresh();
}


void receptionist::work(){

    while(true){
        browsingFacebook();

        waitingForClient();

    }

}

void receptionist::browsingFacebook() {
    std::unique_lock<std::mutex> lockRec(g.rec.getMutex());
    // zajęcie siłowni
    g.rec.request(id);




    printReceptionist(20,10);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    clear(20,10);

    std::lock_guard<std::mutex> number_lock(g.mutex_number);
//    mvprintw(5,20,"%d",g.getCurrentClients());
    if(g.getCurrentClients() <= 3) {
        mvprintw(5,20,"%d",g.getCurrentClients());
        g.rec.release();
        lockRec.unlock();
    }


}

void receptionist::waitingForClient() {
    printReceptionist(30,15);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    clear(30,15);
}