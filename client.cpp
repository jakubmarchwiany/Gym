#include "client.h"

//client::client(int id, int number_in_Line, gym& g) : id(id), number_in_Line(number_in_Line), g(g), lifeline(&client::visit, this) {}

client::client(int id, int numberInLine, gym& g, std::atomic<bool> &done) : id(id), number_in_Line(numberInLine), g(g), lifeline(&client::visit, this), done(done) {}

void client::visit() {

    // Wejście do kolejki
//    in_line();
//    // Wejście do recepcji
//
//    reception();
//    // Wejście do szatni
//    locker_room();
//    // trening
//    training();

}


void client::in_line() {
    g.printer.print_client_status(id);
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

    g.printer.print_number_of_clients(g.getCurrentClients());

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
                g.printer.print_status(208,17+id*2,"dressing up   ");
                static thread_local std::uniform_int_distribution<> wait(30, 60);
                std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));

                g.printer.clear_client(loc.getX() + 2, loc.getY() + 2);

                break;
            }
        }
        loc.getMutex().unlock();
    }
}

void client::training(){

    while(number_of_action < 4){
        int number = rand() % 101;

        if (number <= 33)
            take_bench();
        else if (number <= 66)
            take_deadlift_spot();
        else if (number <= 99)
            crossfit();
        else
            leave();

        number_of_action++;
    }

    leave();

}


void client::crossfit(){
    std::unique_lock<std::mutex> lockNumber(g.cross.getMutex());
    if(g.cross.getClients() < 3) {
        int x = g.cross.getClients();
        g.printer.print_client(137 + x * 25, 17 + 1, id);
        g.cross.setClients(g.cross.getClients()+1);
        lockNumber.unlock();
        g.printer.print_status(208,17+id*2,"wait cross    ");
        g.cross.wait_for_training();
        g.printer.print_status(208,17+id*2,"cross time    ");
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));

        g.printer.clear_client(137 + x * 25, 17 + 1);

    }else{
        g.printer.print_client(123, 28, id);
        lockNumber.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        g.printer.clear_client(123, 28);
    }
}

void client::take_deadlift_spot(){
    int attempt = 0;
    bool end = false;
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        for (int i = 0; i < 3; i++) {
            deadlift_position &d_l_position = g.getDeadliftes().at(i);
            if (d_l_position.getMutex().try_lock()) {
                g.printer.print_client(d_l_position.getX()+4, d_l_position.getY()+3, id);

                deadlift(d_l_position);

                g.printer.clear_client(d_l_position.getX()+4, d_l_position.getY()+3);
                d_l_position.getMutex().unlock();
                end = true;
                break;
            }

        }

        attempt++;
        if (attempt == 10 || end)
            break;

    }

}

void client::take_bench(){
    int attempt = 0;
    bool end = false;
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        for (int i = 0; i < 3; i++) {
            bench &bench = g.getBenches().at(i);
            if (bench.getMutex().try_lock()) {
                g.printer.print_client(bench.getX(), bench.getY(), id);
                chest_press(bench);
                g.printer.clear_client(bench.getX(), bench.getY());
                bench.getMutex().unlock();
                end = true;
                break;
            }

        }

        attempt++;
        if (attempt == 10 || end)
            break;

    }
}

void client::deadlift(deadlift_position &d_l_Position){
//    int weight = rand() % 9;

    int weight =  g.getIntsWeight()[rand() % 9];

    g.printer.print_status_value(208,17+id*2,"request w: %d",weight);

    auto disces_index = g.disces_deadlift.request(weight);



    int weight_left=0;
    int l = 0;
    int r = 0;
    for(const auto& d: disces_index){
        disc disc1 = g.disces_deadlift.getLoads().at(d);
        g.printer.print_clear_load(disc1.getX(),disc1.getY());


        if (weight_left < weight/2){
            g.printer.printLoad(d_l_Position.getX() - 5, d_l_Position.getY() - l + 5, disc1.getWeight());
            weight_left+=disc1.getWeight();
            l += 2;
        }else{
            g.printer.printLoad(d_l_Position.getX() + 13, d_l_Position.getY() - r + 5, disc1.getWeight());
            r +=2;
        }
    }
    g.printer.print_status(208,17+id*2,"deadlift      ");
    static thread_local std::uniform_int_distribution<> wait(50, 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 100));


    g.printer.clear_deadlift(d_l_Position.getX(), d_l_Position.getY() + 6);


    for(const auto& d: disces_index) {
        disc disc1 = g.disces_deadlift.getLoads().at(d);

        g.printer.printLoad(disc1.getX(),disc1.getY(),disc1.getWeight());
    }

    g.disces_deadlift.put_back(disces_index);

}

void client::chest_press(bench &ben){
    int weight =  g.getIntsWeight()[rand() % 9];

    g.printer.print_status_value(208,17+id*2,"request w: %d",weight);

    auto disces_index = g.disces_chest_press.request(weight);

//    for (int i = 0; i < disces_index.size(); ++i) {
//        mvprintw(20+i,200+id*3,"%d",disces_index[i]);
//    }
    int weight_left=0;
    int l = 0;
    int r = 0;
    for(const auto& d: disces_index){
        disc disc1 = g.disces_chest_press.getLoads().at(d);
        g.printer.print_clear_load(disc1.getX(),disc1.getY());


        if (weight_left < weight/2){
            g.printer.printLoad(ben.getX()-5, ben.getY()-l+6,disc1.getWeight());
            weight_left+=disc1.getWeight();
            l += 2;
        }else{
            g.printer.printLoad(ben.getX()+5,ben.getY()-r+6,disc1.getWeight());
            r +=2;
        }
    }
    g.printer.print_status(208,17+id*2,"chest press   ");
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    g.printer.clear_bench(ben.getX(),ben.getY()+6);


    for(const auto& d: disces_index) {
        disc disc1 = g.disces_chest_press.getLoads().at(d);

        g.printer.printLoad(disc1.getX(),disc1.getY(),disc1.getWeight());
    }

    g.disces_chest_press.put_back(disces_index);

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

            g.printer.print_status(208,17+id*2,"dressing up   ");
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

    g.printer.print_number_of_clients(g.getCurrentClients());

    lockNumber.unlock();

    g.printer.print_status(208,17+id*2,"going out     ");

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    g.printer.clear_client(15, 26);

}

int client::get_id() {
    return id;
}

std::thread &client::getLifeline(){
    return lifeline;
}
