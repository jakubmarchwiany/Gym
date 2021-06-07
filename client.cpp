#include "client.h"

//client::client(int id, int number_in_Line, gym& g) : id(id), number_in_Line(number_in_Line), g(g), lifeline(&client::visit, this) {}

client::client(int id, int numberInLine, gym& g, std::atomic<bool> &done) : id(id), number_in_Line(numberInLine), g(g), lifeline(&client::visit, this), done(done) {}

void client::visit() {

//    do {
        // Wejście do kolejki
        in_line();
        // Wejście do recepcji
        reception();
        // Wejście do szatni
        locker_room();
        // trening
        training();

//    }while(!done);

}




void client::in_line() {
    // Dostowanie następnego miejsca w kolejce
    while(number_in_Line >= 1){
        // Pobranie mutexu z akutalnego miejsca w kolejce
        std::unique_lock<std::mutex> lock(g.getLine().at(number_in_Line).getMutex());
//        lock.lock();

        // Zarządanie miejsca w kolejce
        g.getLine().at(number_in_Line).request(id);

        // Wyświetlenie klienta na aktualnej pozycji w kolejce
        g.printer.print_client(g.getLine().at(number_in_Line).getX(), g.getLine().at(number_in_Line).getY(), this->id);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        lock.unlock();

        std::unique_lock<std::mutex> lock2(g.getLine().at(number_in_Line - 1).getMutex());

        // Zarądzanie miejsca następnego w kolejce
        g.getLine().at(number_in_Line - 1).request(id);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        lock2.unlock();

        // Wyczyszczenie z poprzedniej pozycji w kolejce
        g.printer.clear_client(g.getLine().at(number_in_Line).getX(), g.getLine().at(number_in_Line).getY());

        // Zwolnienie aktualnego miejsca w kolejce
        g.getLine().at(number_in_Line).release();

        number_in_Line--;
    }
}

void client::reception() {

    std::unique_lock<std::mutex> lock2(g.getLine().at(number_in_Line).getMutex());

    g.getLine().at(number_in_Line).request(id);

    g.printer.print_client(g.getLine().at(number_in_Line).getX(), g.getLine().at(number_in_Line).getY(), this->id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    lock2.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::unique_lock<std::mutex> lockRec(g.rec.getMutex());

    g.rec.request();

    lockRec.unlock();

    g.printer.clear_client(g.getLine().at(number_in_Line).getX(), g.getLine().at(number_in_Line).getY());

    g.getLine().at(number_in_Line).release();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    g.printer.print_client(30, 18, this->id);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    g.printer.clear_client(30, 18);

    std::unique_lock<std::mutex> lockNumber(g.getMutexNumber());
    g.setCurrentClients(g.getCurrentClients() + 1);
    std::unique_lock<std::mutex> print(g.printer.getMutex());
    mvprintw(15,203,"Liczba klientow %d",g.getCurrentClients());
    print.unlock();
    lockNumber.unlock();

    g.rec.release();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));


}


void client::locker_room() {
    g.printer.print_client(60, 15, this->id);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));



    for(int i =0;i<17;i++){
        locker & loc = g.getLockers().at(i);
        if (loc.getMutex().try_lock()){
            if (loc.isFree()){
                g.printer.clear_client(60, 15);


                g.printer.print_client(loc.getX() + 2, loc.getY() + 2, this->id);
                g.printer.print_closed_locker(loc.getX(), loc.getY());
                number_lock = loc.getId() - 1;
                loc.setIsFree(false);
                loc.setOwner(id);
                loc.getMutex().unlock();

                // Czas przebierania
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                g.printer.clear_client(loc.getX() + 2, loc.getY() + 2);

                break;
            }
        }
        loc.getMutex().unlock();
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
//            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //wychodze
//
//        crossfit();
//
//        number_of_action++;
//    }

    crossfit();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    leave();



}




void client::crossfit(){
    std::unique_lock<std::mutex> lockNumber(g.cross.getMutex());
    if(g.cross.getClients() < 3) {
        int x = g.cross.getClients();
        g.printer.print_client(137 + x * 25, 17 + 1, id);
        g.cross.setClients(g.cross.getClients()+1);
        lockNumber.unlock();
        g.cross.wait_for_training();
        g.printer.clear_client(137 + x * 25, 17 + 1);

    }else{
        g.printer.print_client(123, 28, id);
        lockNumber.unlock();
    }
}

void client::take_bench(){
    int attempt = 0;
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        for (int i = 0; i < 3; i++) {
            bench &bench = g.getBenches().at(i);
            if (bench.getMutex().try_lock()) {
                g.printer.print_client(bench.getX(), bench.getY(), id);
                chest_press(bench);


                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                bench.getMutex().unlock();
                break;
            }

        }

        attempt++;
        if (attempt == 10)
            break;

    }
}



void client::chest_press(bench &ben){
//    mvprintw(20,205,"A");
//    //waga klienta 80 czyli 60 kg ciężarach
////    int chest_weight = int(weight * 0.8);
//
//    int chest_weight = 200;
//    //Waga klienta * 0.8 - 2 * waga ciężarka >= 0
//    if (chest_weight - 2 * 40 >= 0 ){
//        chest_weight -= 2 * 40;
//
//        disc &load1 = g.getLoads().at(12);
//
//        disc &load2 = g.getLoads().at(13);
//        mvprintw(20+id,206,"B");
//        int result = load1.request();
//        mvprintw(20+id,207,"C");
//        printLoad(ben.x - 3,ben.y + 3,load1.weight);
//
//        int result2 = load2.request();
//
//        printLoad(ben.x + 3,ben.y + 3,load1.weight);
//        mvprintw(20,208,"D");
//        printLoad(load2.x,load2.y,load2.weight);
//
//        std::unique_lock<std::mutex> lockLoad1(load1.getMutex());
//        std::unique_lock<std::mutex> lockLoad2(load2.getMutex());
//
//        if(result == 1 || result2 == 1){
//            lockLoad1.unlock();
//            lockLoad2.unlock();
//            load1.done_using();
//            load2.done_using();
//        }
//    }



//    if (chest_weight - 2 * 20 >= 0 ){
//        chest_weight -= 2 * 20;
//
//        int attempt = 0;
//        while(true) {
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//
//            for (int i = 0; i < 3; i++) {
//                disc &load3 = g.getLoads().at(i);
//                if (load3.getMutex().try_lock()) {
//                    print_client(bench.x,bench.y,id);
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

void client::leave(){

    g.printer.print_client(60, 15, this->id);

//    mvprintw(%id 20+id,205,"%dA",id);
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        locker &loc = g.getLockers().at(number_lock);
        if (loc.getMutex().try_lock()){
            g.printer.clear_client(60, 15);


            g.printer.print_client(loc.getX() + 2, loc.getY() + 2, this->id);
            g.printer.print_opened_locker(loc.getX(), loc.getY());
            std::this_thread::sleep_for(std::chrono::milliseconds(4000));
            loc.setIsFree(true);
            loc.setOwner(-1);
            g.printer.clear_client(loc.getX() + 2, loc.getY() + 2);
            loc.getMutex().unlock();
            break;
        }
    }

    g.printer.print_client(60, 15, this->id);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    g.printer.print_client(15, 26, this->id);

    std::unique_lock<std::mutex> lockNumber(g.getMutexNumber());

    g.setCurrentClients(g.getCurrentClients() - 1);

    lockNumber.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    g.printer.clear_client(15, 26);

//    lifeline.join();
}


int client::get_id() {
    return id;
}

std::thread &client::getLifeline(){
    return lifeline;
}
