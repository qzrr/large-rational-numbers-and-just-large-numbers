#ifndef COURSEWORK1_BIGNUMBER_H
#define COURSEWORK1_BIGNUMBER_H

#include "List.h"
#include <cstring>
#include <string>

class BigNumber : public List {

public:
    BigNumber(int value = 0);
    BigNumber(const BigNumber &other);
    BigNumber(const char *str);
    BigNumber(const List &list) : List(list) {}

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

    friend std::ostream &operator<<(std::ostream &os, const BigNumber &num);

    int Length() const override;
    int Length();

    ~BigNumber() = default;

    int getDigit(int index) const;

    static void reverseString(std::string &str);

};

#endif //COURSEWORK1_BIGNUMBER_H
