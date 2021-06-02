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
    mvprintw(y,x,"XXXX");
    mvprintw(y+1,x,"XXXX");
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

//    while(number_of_action < 4){
//        int number = rand() % 101;
//
//        if (number <= 33)
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //klata
//        else if (number <= 66)
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //martwy
//        else if (number <= 99)
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //zajęcia grupowe
//        else
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //wychodze elo
//
//        crossfit();
//
//        number_of_action++;
//    }

    take_bench();



}


void client::crossfit(){
    std::unique_lock<std::mutex> lockNumber(g.cross.mutex);
    if(g.cross.clients < 3) {
        int x = g.cross.clients;
        printClient(137 + x * 25,17 + 1,id);
        g.cross.clients++;
        lockNumber.unlock();
        g.cross.wait_for_training();
        printClientClear(137 + x * 25,17 + 1);

    }else{
        printClient(123,28,id);
        lockNumber.unlock();
    }
}

void client::take_bench(){
    int attempt = 0;
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        for (int i = 0; i < 3; i++) {
            bench &bench = g.getBenches().at(i);
            if (bench.mutex.try_lock()) {
                printClient(bench.x,bench.y,id);
                chest_press(bench);


                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                bench.mutex.unlock();
                break;
            }
        }

        attempt++;
        if (attempt == 10)
            break;

    }
}

void client::printLoad(int xPosition, int yPosition,int weight){
    init_pair(15,COLOR_WHITE, 16);
    attron(COLOR_PAIR(15));

    mvprintw(yPosition,xPosition," %d ",weight);


    attroff(COLOR_PAIR(15));
}

void client::print_clear_load(int xPosition, int yPosition){
    init_pair(18,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(18));

    mvprintw(yPosition,xPosition,"   ");

    attroff(COLOR_PAIR(18));

}

void client::chest_press(bench &ben){
    mvprintw(20,205,"A");
    //waga klienta 80 czyli 60 kg ciężarach
//    int chest_weight = int(weight * 0.8);

    int chest_weight = 200;
    //Waga klienta * 0.8 - 2 * waga ciężarka >= 0
    if (chest_weight - 2 * 40 >= 0 ){
        chest_weight -= 2 * 40;

        load &load1 = g.getLoads().at(12);

        load &load2 = g.getLoads().at(13);
        mvprintw(20,206,"B");
        int result = load1.request();
        mvprintw(20,207,"C");
        printLoad(ben.x - 3,ben.y + 3,load1.weight);

        int result2 = load2.request();

        printLoad(ben.x + 3,ben.y + 3,load1.weight);
        mvprintw(20,208,"D");
        printLoad(load2.x,load2.y,load2.weight);

        std::unique_lock<std::mutex> lockLoad1(load1.getMutex());
        std::unique_lock<std::mutex> lockLoad2(load2.getMutex());

        if(result == 1 || result2 == 1){
            lockLoad1.unlock();
            lockLoad2.unlock();
            load1.done_using();
            load2.done_using();
        }
    }



//    if (chest_weight - 2 * 20 >= 0 ){
//        chest_weight -= 2 * 20;
//
//        int attempt = 0;
//        while(true) {
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//
//            for (int i = 0; i < 3; i++) {
//                load &load3 = g.getLoads().at(i);
//                if (load3.getMutex().try_lock()) {
//                    printClient(bench.x,bench.y,id);
//                    chest_press();
//
//
//                    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//                    bench.mutex.unlock();
//                    break;
//                }
//            }
//
//            attempt++;
//            if (attempt == 10)
//                break;
//
//        }
//
//
//    }
//
//    if (chest_weight - 2 * 10 >= 0 ){
//        chest_weight -= 2 * 10;
//
//    }
//
//    if (chest_weight - 2 * 5 >= 0 ){
//
//
//    }

    //ćwicz

}


int client::get_id() {
    return id;
}
