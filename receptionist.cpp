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
    while(true)
    {
        waitingForClient();

        browsingFacebook();

    }
}

void receptionist::browsingFacebook() {
    printReceptionist(30,15);
    std::this_thread::sleep_for(std::chrono::milliseconds(2870));
    clear(30,15);
}

void receptionist::waitingForClient() {
    printReceptionist(20,10);

    std::this_thread::sleep_for(std::chrono::milliseconds(2960));

    std::unique_lock<std::mutex> number_lock(g.mutex_number);

    if(g.getCurrentClients() < 5) {
        g.rec.setFree(true);
        g.rec.release();
        number_lock.unlock();
    }
    clear(20,10);


}