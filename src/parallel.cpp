#include "headers/parallel.h"

Parallel::Parallel(Star &star) {
    this->star = star;
}

void Parallel::start() {
    pthread_create(&thread, NULL, Parallel::staticEntryPoint, this);
}

void * Parallel::staticEntryPoint(void * c) {
    ((Parallel *) c)->entryPoint();
    return NULL;
}

void Parallel::entryPoint() {
    star.draw();
    star.update(3);
    std::cout << star.getX() << std::endl;
    Sleep(10);
}

int Parallel::join() {
    return pthread_join(thread, NULL);
}