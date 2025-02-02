#ifndef COURSEWORK1_BIGRACNUMBER_H
#define COURSEWORK1_BIGRACNUMBER_H


#include "BigNumber.h"
#include <iostream>
#include <stdexcept>
#include <string>

class BigRacNumber {
private:
    BigNumber numerator;
    BigNumber denomator; // знаменатель

    // Вспомогательная функция для приведения дроби к каноническому виду
    // (Можно добавить сокращение, если реализована функция НОД – здесь опущено)
public:
    // Конструкторы с одним параметром – знаменатель равен 1
    BigRacNumber(int value);
    BigRacNumber(const char *str); // Если строка не содержит символ '/' считается целым

    // Конструкторы с двумя параметрами
    BigRacNumber(int num, int den);
    BigRacNumber(const char *numStr, const char *denStr);

    // Конструктор копирования
    BigRacNumber(const BigRacNumber &other);
    BigRacNumber(const BigNumber &num, const BigNumber &den);

    // Операторы арифметики
    BigRacNumber operator+(const BigRacNumber &other) const;
    BigRacNumber operator-(const BigRacNumber &other) const;
    BigRacNumber operator*(const BigRacNumber &other) const;

    BigRacNumber &operator+=(const BigRacNumber &other);
    BigRacNumber &operator-=(const BigRacNumber &other);
    BigRacNumber &operator*=(const BigRacNumber &other);

    // Операторы сравнения (сравнение дробей путем перекрёстного умножения)
    bool operator==(const BigRacNumber &other) const;
    bool operator!=(const BigRacNumber &other) const;
    bool operator>(const BigRacNumber &other) const;
    bool operator<(const BigRacNumber &other) const;
    bool operator>=(const BigRacNumber &other) const;
    bool operator<=(const BigRacNumber &other) const;

    // Оператор вывода в поток
    friend std::ostream &operator<<(std::ostream &os, const BigRacNumber &brn);

    // Метод inverse: возвращает обратную дробь
    BigRacNumber inverse() const;

    // Деструктор
    ~BigRacNumber() {}

    // Оператор || - возвращает значение цифры по её номеру в числителе (нумерация с младших разрядов)
    int operator||(int index) const;
};

#endif //COURSEWORK1_BIGRACNUMBER_H
