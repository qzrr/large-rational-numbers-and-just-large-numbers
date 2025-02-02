#ifndef COURSEWORK1_BIGNUMBER_H
#define COURSEWORK1_BIGNUMBER_H

#include "List.h"
#include <string>

class BigNumber : public List {
public:
    // Конструктор с параметром (целое число)
    BigNumber(int value = 0);

    // Конструктор копирования
    BigNumber(const BigNumber &other);

    // Конструктор из символьного массива
    BigNumber(const char *str);

    BigNumber(const List &list) : List(list) {}

    // Оператор сложения
    BigNumber operator+(const BigNumber &other) const;
    BigNumber operator-(const BigNumber &other) const;
    BigNumber operator*(const BigNumber &other) const;

    BigNumber &operator+=(const BigNumber &other);
    BigNumber &operator-=(const BigNumber &other);
    BigNumber &operator*=(const BigNumber &other);

    bool operator==(const BigNumber &other) const;
    bool operator!=(const BigNumber &other) const;
    bool operator>(const BigNumber &other) const;
    bool operator<(const BigNumber &other) const;
    bool operator>=(const BigNumber &other) const;
    bool operator<=(const BigNumber &other) const;

    // Оператор вывода в поток
    friend std::ostream &operator<<(std::ostream &os, const BigNumber &num);

    // Длина числа
    int Length() const override;

    int Length();
    ~BigNumber() {};
    int getDigit(int index) const;
};

#endif //COURSEWORK1_BIGNUMBER_H
