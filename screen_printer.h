#ifndef UNTITLED3_SCREEN_PRINTER_H
#define UNTITLED3_SCREEN_PRINTER_H

#include <mutex>



class screen_printer {
public:
    std::mutex &getMutex();

    void print_client(int x, int y, int id);

    void clear_client(int x, int y);

    void print_receptionist(int x, int y);

    void clear_receptionist(int x, int y);

    void print_trainer(int x, int y);

    void clear_trainer(int x, int y);


    void printLoad(int xPosition, int yPosition, int weight);

    void print_clear_load(int xPosition, int yPosition);

    void clear_bench(int xPosition, int yPosition);

    void clear_deadlift(int xPosition, int yPosition);

    void print_opened_locker(int x, int y);

    void print_closed_locker(int x, int y);

    void printBench(int xPosition, int yPosition);

    void printDeadlift(int xPosition, int yPosition);

    void printLocker(int xPosition, int yPosition, int number, int numberStart);

    void printMat(int xPosition, int yPosition);

    void printGym();

private:
    std::mutex print_mutex;



};

#endif
