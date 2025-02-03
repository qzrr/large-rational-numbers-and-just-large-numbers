#ifndef COURSEWORK1_BIGRACNUMBER_H
#define COURSEWORK1_BIGRACNUMBER_H


#include "BigNumber.h"


class BigRacNumber {
private:
    BigNumber numerator;
    BigNumber denominator;

public:
    BigRacNumber(int value);
    BigRacNumber(const char *str);


    BigRacNumber(int num, int den);
    BigRacNumber(const char *numStr, const char *denStr);


    BigRacNumber(const BigRacNumber &other);
    BigRacNumber(const BigNumber &num, const BigNumber &den);

    BigRacNumber operator+(const BigRacNumber &other) const;
    BigRacNumber operator-(const BigRacNumber &other) const;
    BigRacNumber operator*(const BigRacNumber &other) const;

    BigRacNumber &operator+=(const BigRacNumber &other);
    BigRacNumber &operator-=(const BigRacNumber &other);
    BigRacNumber &operator*=(const BigRacNumber &other);

    bool operator==(const BigRacNumber &other) const;
    bool operator!=(const BigRacNumber &other) const;
    bool operator>(const BigRacNumber &other) const;
    bool operator<(const BigRacNumber &other) const;
    bool operator>=(const BigRacNumber &other) const;
    bool operator<=(const BigRacNumber &other) const;

    friend std::ostream &operator<<(std::ostream &os, const BigRacNumber &brn);

    BigRacNumber inverse() const;

    ~BigRacNumber() = default;

    int operator||(int index) const;
};

#endif //COURSEWORK1_BIGRACNUMBER_H
