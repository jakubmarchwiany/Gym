#include "client.h"

client::client(int id, int numberInLine, gym& g) : id(id), numberInLine(numberInLine), g(g), lifeline(&client::visit, this) {}


void client::visit() {
    // Wejście do kolejki
    in_line();
    // Wejście do recepcji
    reception();
    // Wejście do szatni
    locker_room();
    // trening
    training();
}

void client::printClient(int x, int y,int id) {
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(7,COLOR_BLACK, COLOR_YELLOW);
    attron(COLOR_PAIR(7));
    mvprintw(y,x,"    ");
    mvprintw(y+1,x,"   %d",id);
    attroff(COLOR_PAIR(7));
    refresh();
}

void client::printClientClear(int x, int y) {
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
    while(numberInLine >= 1){
        // Pobranie mutexu z akutalnego miejsca w kolejce
        std::unique_lock<std::mutex> lock(g.getLine().at(numberInLine).getMutex());
//        lock.lock();

        // Zarządanie miejsca w kolejce
        g.getLine().at(numberInLine).request(id);

        // Wyświetlenie klienta na aktualnej pozycji w kolejce
        printClient(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY(),this->id);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        lock.unlock();

        std::unique_lock<std::mutex> lock2(g.getLine().at(numberInLine-1).getMutex());

        // Zarądzanie miejsca następnego w kolejce
        g.getLine().at(numberInLine - 1).request(id);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        lock2.unlock();

        // Wyczyszczenie z poprzedniej pozycji w kolejce
        printClientClear(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY());

        // Zwolnienie aktualnego miejsca w kolejce
        g.getLine().at(numberInLine).release();

        numberInLine--;
    }
}

void client::reception() {
    std::unique_lock<std::mutex> lock2(g.getLine().at(numberInLine).getMutex());

    g.getLine().at(numberInLine).request(id);

    printClient(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY(),this->id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    lock2.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::unique_lock<std::mutex> lockRec(g.rec.getMutex());

    g.rec.request();

    lockRec.unlock();

    printClientClear(g.getLine().at(numberInLine).getX(),g.getLine().at(numberInLine).getY());

    g.getLine().at(numberInLine).release();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    printClient(30,18,this->id);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    printClientClear(30,18);

    std::unique_lock<std::mutex> lockNumber(g.mutex_number);
    g.setCurrentClients(g.getCurrentClients() + 1);
    lockNumber.unlock();

    g.rec.release();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));


}

void client::print_lock_locker(int x, int y){
    std::lock_guard<std::mutex> print_lock(g.mutex_print);
    init_pair(12,COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(12));
    mvprintw(y+1, x+1, "      ");
    attroff(COLOR_PAIR(12));
    refresh();
}

void client::locker_room() {
    printClient(60,15,this->id);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    print_lock_locker(g.getLockers().at(0).getX(), g.getLockers().at(0).getY());
    g.getLockers().at(0).setIsFree(false);
    print_lock_locker(g.getLockers().at(1).getX(), g.getLockers().at(1).getY());
    g.getLockers().at(1).setIsFree(false);

    for(int i =0;i<17;i++){
        locker & loc = g.getLockers().at(i);
        if (loc.getMutex().try_lock()){
            if (loc.isFree()){
                printClientClear(60,15);


                printClient(loc.getX() + 2,loc.getY() + 2,this->id);
                print_lock_locker(loc.getX(), loc.getY());
                loc.setIsFree(false);
                loc.setOwner(id);
                loc.getMutex().unlock();

                // Czas przebierania
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                printClientClear(loc.getX() + 2,loc.getY() + 2);

                break;
            }

        }
    }






}

void client::training(){

    while(number_of_action < 4){
        int number = rand() % 101;

//        if (number <= 33)
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //klata
//        else if (number <= 66)
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //martwy
//        else if (number <= 99)
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //zajęcia grupowe
//        else
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //wychodze elo

        crossfit();

        number_of_action++;
    }
}


void client::crossfit(){

    std::unique_lock<std::mutex> lockNumber(g.cross.mutex);

    if(g.cross.clients < 3) {
        printClient(137 + g.cross.clients * 25,17 + 1,id);
        g.cross.clients++;


        lockNumber.unlock();
        g.cross.wait_for_training();
    }else{
        printClient(123,28,id);
    }
}



int client::get_id() {
    return id;
}
