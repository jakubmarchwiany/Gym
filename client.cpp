#include "client.h"


client::client(int id, int numberInLine, gym& g) : id(id), numberInLine(numberInLine), g(g), lifeline(&client::visit, this) {}

void client::visit() {
    // Wejście do kolejki
    in_line();
    // Wejście do recepcji
    reception();

}

void client::printClient(int x, int y,int id) {
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(7,COLOR_BLACK, COLOR_YELLOW);
    attron(COLOR_PAIR(7));
    mvprintw(y,x,"    ");
    mvprintw(y+1,x,"   %d",id);
    attroff(COLOR_PAIR(7));
    refresh();
}

void client::printClientClear(int x, int y) {
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(8,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(8));
    mvprintw(y,x,"XXXXX");
    mvprintw(y+1,x,"XXXXX");
    attroff(COLOR_PAIR(8));
    refresh();
}


void client::in_line() {

    // Dostowanie następnego miejsca w kolejce
    while(numberInLine != 0){
        // Pobranie mutexu z akutalnego miejsca w kolejce
        std::unique_lock<std::mutex> lock(g.getLine().at(numberInLine).getMutex());
//        lock.lock();

        // Zarządanie miejsca w kolejce
        g.getLine().at(numberInLine).request(id);

        // Wyświetlenie klienta na aktualnej pozycji w kolejce
        printClient(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY(),this->id);

        // Zarądzanie miejsca następnego w kolejce
        g.getLine().at(numberInLine - 1).request(id);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Wyczyszczenie z poprzedniej pozycji w kolejce
        printClientClear(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY());

        // Zwolnienie poprzedniego zasobu
        g.getLine().at(numberInLine).release();
        lock.unlock();
        numberInLine--;
    }


    std::unique_lock<std::mutex> lock2(g.getLine().at(numberInLine).getMutex());

    g.getLine().at(numberInLine).request(id);

    printClient(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY(),this->id);

    std::unique_lock<std::mutex> lockRec(g.rec.getMutex());

    g.rec.request(id);

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    printClientClear(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY());


    g.getLine().at(numberInLine).release();

    lock2.unlock();

    printClient(50,50,this->id);


    std::unique_lock<std::mutex> lockNumber(g.mutex_number);
    g.setCurrentClients(g.getCurrentClients() + 1);
    lockNumber.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    g.rec.release();
    lockRec.unlock();





}

void client::reception() {



}

int client::get_id() {
    return id;
}


