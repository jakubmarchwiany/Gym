#include "screen_printer.h"
#include "ncurses.h"

void screen_printer::printBench(int xPosition,int yPosition){
    init_pair(2,COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(2));

    for (int x = 0;x < 3;x++ )
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
        mvprintw(yPosition, xPosition+(4 * number), " ");
        mvprintw(yPosition, xPosition+1+(4 * number), "%02d", numberStart);
        mvprintw(yPosition, xPosition+3+(4 * number), " ");

        mvprintw(yPosition+1, xPosition+(4 * number), " ");
        mvprintw(yPosition+1, xPosition+3+(4 * number), " ");

        mvprintw(yPosition+2, xPosition+(4 * number), " ");
        mvprintw(yPosition+2, xPosition+1+(4 * number), " ");
        mvprintw(yPosition+2, xPosition+2+(4 * number), " ");
        mvprintw(yPosition+2, xPosition+3+(4 * number), " ");
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

        if (127 >= i)
            mvaddch(22, i, ' ');

        mvaddch(63, i, ' ');
    }

    for (int i = 5; i< 63 ;i++){
        if (i <= 22)
            mvaddch(i, 50, ' ');

        if (i <= 35)
            mvaddch(i, 127, ' ');

        if (i <= 24 || i>= 30)
            mvaddch(i,15,' ');

        mvaddch(i,200,' ');
        mvaddch(i,236,' ');
    }
    attroff(COLOR_PAIR(1));


// Rysowanie Ławek do klaty
    printBench(26,52);
    printBench(41,52);
    printBench(56,52);

// Rysowanie miejsc do Martwego Ciągu
    printDeadlift(100,51);
    printDeadlift(125,51);
    printDeadlift(150,51);



//    Szafki

    for (int n=0; n<=18;n++)
        printLocker(51,8,n,n);

    for (int n=0; n<=16;n++)
        printLocker(59,19,n,n+19);

// Maty do ćwiczenia grupowego

    printMat(135,17);
    printMat(160,17);
    printMat(185,17);
    printMat(135,27);
    printMat(160,27);
    printMat(185,27);


//    Napisy

    mvprintw(2,115,"Fabryka sportu");

    mvprintw(7,30,"Recepcja");

    mvprintw(7,85,"Szatnia");

    mvprintw(7,157,"Zajecia grupowe");

    mvprintw(61,40,"Klata");

    mvprintw(61,125,"Martwy  Ciag");

    mvprintw(7,215,"Status Bar");

    refresh();

}
