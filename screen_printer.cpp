#include "screen_printer.h"
#include "ncurses.h"
#include "client.h"


void screen_printer::print_client(int x, int y, int id) {
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(7,COLOR_BLACK, COLOR_YELLOW);
    attron(COLOR_PAIR(7));
    mvprintw(y,x,"    ");
    mvprintw(y+1,x,"  %2d",id);
    attroff(COLOR_PAIR(7));
    refresh();
}

void screen_printer::clear_client(int x, int y) {
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(8,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(8));
    mvprintw(y,x,"XXXX");
    mvprintw(y+1,x,"XXXX");
    attroff(COLOR_PAIR(8));
    refresh();
}

void screen_printer::printLoad(int xPosition, int yPosition,int weight){
    init_pair(15,COLOR_WHITE, 16);
    attron(COLOR_PAIR(15));

    mvprintw(yPosition,xPosition," %d ",weight);


    attroff(COLOR_PAIR(15));
}

void screen_printer::print_clear_load(int xPosition, int yPosition){
    init_pair(18,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(18));

    mvprintw(yPosition,xPosition,"   ");

    attroff(COLOR_PAIR(18));

}


void screen_printer::print_opened_locker(int x, int y) {
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(12, COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(12));
    mvprintw(y + 1, x + 1, "      ");
    attroff(COLOR_PAIR(12));
    refresh();
}

void screen_printer::print_closed_locker(int x, int y) {
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(12, COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(12));
    mvprintw(y + 1, x + 1, "      ");
    attroff(COLOR_PAIR(12));
    refresh();
}





void screen_printer::print_receptionist(int x, int y) {
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(9,COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(9));
    mvprintw(y,x,"    ");
    mvprintw(y+1,x,"    ");
    attroff(COLOR_PAIR(9));
    refresh();
}

void screen_printer::clear_receptionist(int x, int y) {
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(10,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(10));
    mvprintw(y,x,"    ");
    mvprintw(y+1,x,"    ");
    attroff(COLOR_PAIR(10));
    refresh();
}

void screen_printer::print_trainer(int x, int y) {
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(14,COLOR_BLACK, COLOR_GREEN);
    attron(COLOR_PAIR(14));
    mvprintw(y,x,"     ");
    mvprintw(y+1,x,"     ");

    attroff(COLOR_PAIR(14));
    refresh();
}

void screen_printer::clear_trainer(int x, int y) {
    std::lock_guard<std::mutex> print_lock(print_mutex);
    init_pair(10,COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(10));
    mvprintw(y,x,"     ");
    mvprintw(y+1,x,"     ");
    attroff(COLOR_PAIR(10));
    refresh();
}

void screen_printer::printBench(int xPosition,int yPosition){
    init_pair(2,COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(2));

    for (int x = 0;x < 4;x++ )
        for(int y = 0;y < 5;y++)
            mvprintw(y+yPosition,x+xPosition," ");

    attroff(COLOR_PAIR(2));
}

void screen_printer::printDeadlift(int xPosition,int yPosition){
    init_pair(3,COLOR_BLACK, COLOR_MAGENTA);
    attron(COLOR_PAIR(3));

    for (int x = 0;x < 12;x++ )
        for(int y = 0;y < 6;y++)
            mvprintw(y+yPosition,x+xPosition," ");

    attroff(COLOR_PAIR(3));

    init_pair(4,COLOR_BLACK, 8);
    attron(COLOR_PAIR(4));

    for (int i = 0;i<8;i++)
        mvprintw(yPosition + 2, i + xPosition + 2 , " ");

    attroff(COLOR_PAIR(4));
}

void screen_printer::printLocker(int xPosition, int yPosition, int number, int numberStart){
    init_pair(5,COLOR_WHITE, COLOR_GREEN);
    attron(COLOR_PAIR(5));
    for (int i = 0;i<8;i++) {

        mvprintw(yPosition, xPosition+(7 * number), "   %02d   ", numberStart);

        mvprintw(yPosition+1, xPosition+(7 * number), " ");
        mvprintw(yPosition+2, xPosition+(7 * number), " ");
        mvprintw(yPosition+3, xPosition+(7 * number), " ");

        mvprintw(yPosition+1, xPosition+7+(7 * number), " ");
        mvprintw(yPosition+2, xPosition+7+(7 * number), " ");
        mvprintw(yPosition+3, xPosition+7+(7 * number), " ");
    }
    attroff(COLOR_PAIR(5));
}

void screen_printer::printMat(int xPosition, int yPosition){
    init_pair(6,COLOR_WHITE, 12);
    attron(COLOR_PAIR(6));

    for (int x = 0;x < 8;x++ )
        for(int y = 0;y < 4;y++)
            mvprintw(y+yPosition,x+xPosition," ");


    attroff(COLOR_PAIR(6));
}

void screen_printer::printGym() {

//    Rysowanie Ścian

    init_pair(1,COLOR_BLACK, COLOR_WHITE);

    attron(COLOR_PAIR(1));
    for (int i = 15; i< 237 ;i++) {
        mvaddch(5, i, ' ');

        if (200 >= i)
            mvaddch(35, i, ' ');

        if (129 >= i)
            mvaddch(22, i, ' ');

        mvaddch(63, i, ' ');
    }

    for (int i = 5; i< 63 ;i++){
        if (i <= 22)
            mvaddch(i, 50, ' ');

        if (i <= 35)
            mvaddch(i, 129, ' ');

        if (i <= 24 || i>= 30)
            mvaddch(i,15,' ');

        mvaddch(i,200,' ');
        mvaddch(i,236,' ');
    }
    attroff(COLOR_PAIR(1));


// Rysowanie Ławek do klaty
    printBench(26,52);
    printBench(41,52);
//    printBench(56,52);

// Rysowanie miejsc do Martwego Ciągu
    printDeadlift(100,51);
    printDeadlift(125,51);
//    printDeadlift(150,51);


// Rysowanie ciężarów

    for(int i=0;i<8;){
        printLoad(20 , 37 + i,5);

        i += 2;
    }

    for(int i=0;i<8;){
        printLoad(25 , 37 + i,10);

        i += 2;
    }

    for(int i=0;i<8;){
        printLoad(30 , 37 + i,20);

        i += 2;
    }

    for(int i=0;i<4;){
        printLoad(35 , 37 + i,40);

        i += 2;
    }




//    Szafki

    for (int n=0; n<=10;n++)
        printLocker(51,6,n,n+1);

    for (int n=0; n<=5;n++)
        printLocker(86,13,n,n+12);

// Maty do ćwiczenia grupowego

    printMat(135,17);
    printMat(160,17);
    printMat(185,17);
//    printMat(135,27);
//    printMat(160,27);
//    printMat(185,27);


//    Napisy

    mvprintw(2,115,"Fabryka sportu");

    mvprintw(7,30,"Recepcja");

    mvprintw(20,85,"Szatnia");

    mvprintw(7,157,"Zajecia grupowe");

    mvprintw(61,40,"Klata");

    mvprintw(61,125,"Martwy  Ciag");

    mvprintw(7,215,"Status Bar");

    refresh();

}

std::mutex &screen_printer::getMutex(){
    return print_mutex;
}







