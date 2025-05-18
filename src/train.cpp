// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;
    Car* cur = first->next;
    while (cur != first) {
        Car* toDel = cur;
        cur = cur->next;
        delete toDel;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* c = new Car(light);
    if (!first) {
        first = c;
    } else {
        Car* last = first->prev;
        last->next = c;
        c->prev = last;
        c->next = first;
        first->prev = c;
    }
}

std::size_t Train::getLength() {
    countOp = 0;
    if (!first) return 0;

    Car* p = first;
    bool hasOn = false;
    
    do {
        if (p->light) {
            hasOn = true;
            break;
        }
        p = p->next;
        countOp++;
    } while (p != first);

    if (!hasOn) {
        first->light = true;
        countOp++;
        
        std::size_t len = 1;
        Car* cur = first->next;
        while (cur != first) {
            cur = cur->next;
            len++;
            countOp++;
        }
        
        cur = first->next;
        while (cur != first) {
            cur = cur->next;
            countOp++;
        }
        
        first->light = false;
        return len;
    } else {
        std::size_t len = 1;
        Car* cur = first->next;
        countOp++;
        while (cur != first) {
            cur = cur->next;
            len++;
            countOp++;
        }
        
        for (std::size_t i = 0; i < len; i++) {
            for (std::size_t j = 0; j < len; j++) {
                countOp++;
            }
        }
        
        return len;
    }
}

std::size_t Train::getOpCount() const {
    return countOp;
}
