// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

Train::~Train() {
  if (!first) return;

  Car* ptr = first->next;
  while (ptr != first) {
    Car* toDelete = ptr;
    ptr = ptr->next;
    delete toDelete;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* node = new Car;
  node->light = light;

  if (!first) {
    node->next = node;
    node->prev = node;
    first = node;
  } else {
    Car* tail = first->prev;
    tail->next = node;
    node->prev = tail;
    node->next = first;
    first->prev = node;
  }
}

int Train::getLength() {
  countOp = 0;
  if (!first) return 0;

  Car* current = first;
  bool foundLight = false;

  do {
    if (current->light) {
      foundLight = true;
      break;
    }
    current = current->next;
  } while (current != first);

  if (foundLight) {
    int len = 1;
    Car* temp = first->next;
    ++countOp;
    while (temp != first) {
      ++len;
      temp = temp->next;
      ++countOp;
    }
    countOp += len * len;
    return len;
  } else {
    first->light = true;

    int size = 1;
    Car* walker = first->next;
    ++countOp;
    while (walker != first) {
      walker = walker->next;
      ++size;
      ++countOp;
    }

    Car* back = walker;
    for (int i = 0; i < size; ++i) {
      back = back->prev;
      ++countOp;
    }

    first->light = false;
    return size;
  }
}

int Train::getOpCount() {
  return countOp;
}
