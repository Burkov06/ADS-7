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

  const Car* current = first;
  bool hasLight = false;

  do {
    if (current->light) {
      hasLight = true;
      break;
    }
    current = current->next;
  } while (current != first);

  if (hasLight) {
    int length = 1;
    const Car* temp = first->next;
    ++countOp;

    while (temp != first) {
      ++length;
      temp = temp->next;
      ++countOp;
    }

    countOp += length * length;
    return length;
  } else {
    first->light = true;

    int length = 1;
    const Car* forward = first->next;
    ++countOp;

    while (forward != first) {
      ++length;
      forward = forward->next;
      ++countOp;
    }

    const Car* backward = forward;
    for (int i = 0; i < length; ++i) {
      backward = backward->prev;
      ++countOp;
    }

    first->light = false;
    return length;
  }
}
int Train::getOpCount() {
  return countOp;
}
