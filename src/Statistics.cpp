#include<iostream>
#include"Statistics.h"


void Statistics::recordPut() {
    puts++;
}

void Statistics::recordGet() {
    gets++;
}

void Statistics::recordDelete() {
    delets++;
}


size_t Statistics::getPuts() const {
    return puts.load();
}

size_t Statistics::getGets() const {
    return gets.load();
}

size_t Statistics::getDeletes() const {
    return delets.load();
}