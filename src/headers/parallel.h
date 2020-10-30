#pragma once
#include <pthread.h>
#include <iostream>
#include "star.h"

class Parallel {
private:
    pthread_t thread;
    Star star;
    int x = 0;

    static void * staticEntryPoint(void * c);
    void entryPoint();

public:
    int join();
    void start();
    Parallel(Star &star);
};