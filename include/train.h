// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <cstdint>

class Train {
 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;

    Car() : light(false), next(this), prev(this) {}
  };

  Car* first;         // указатель на первый вагон
  int countOp;        // количество переходов между вагонами

 public:
  Train();            // конструктор по умолчанию
  ~Train();           // деструктор

  void addCar(bool light); // добавление вагона с заданным светом
  int getLength();         // возвращает длину поезда
  int getOpCount();        // возвращает количество переходов
};

#endif  // INCLUDE_TRAIN_H_
