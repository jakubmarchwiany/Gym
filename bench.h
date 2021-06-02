#ifndef UNTITLED3_BENCH_H
#define UNTITLED3_BENCH_H


#include <mutex>

class bench {


public:
    bench(int x, int y);

    int x,y;
    std::mutex mutex;
};


#endif //UNTITLED3_BENCH_H
