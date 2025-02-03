
#include "BigRacNumber.h"

BigRacNumber::BigRacNumber(int value) : numerator(value), denominator(1) {}

BigRacNumber::BigRacNumber(const char *str) {
    std::string s(str);
    size_t pos = s.find('/');
    if (pos != std::string::npos) {
        std::string numStr = s.substr(0, pos);
        std::string denStr = s.substr(pos + 1);
        numerator = BigNumber(numStr.c_str());
        denominator = BigNumber(denStr.c_str());
    } else {
        numerator = BigNumber(str);
        denominator = BigNumber(1);
    }
}

BigRacNumber::BigRacNumber(int num, int den) : numerator(num), denominator(den) {
    if (den == 0)
        std::cout << "Denominator cannot be zero\n";
}

BigRacNumber::BigRacNumber(const BigNumber &num, const BigNumber &den) : numerator(num), denominator(den) {
    if (denominator == BigNumber(0))
        std::cout << "Denominator cannot be zero\n";
}

BigRacNumber::BigRacNumber(const char *numStr, const char *denStr): numerator(numStr), denominator(denStr) {
    if (denominator == BigNumber(0))
        std::cout<<"Denominator cannot be zero\n";
}

BigRacNumber::BigRacNumber(const BigRacNumber &other) = default;

BigRacNumber BigRacNumber::operator+(const BigRacNumber &other) const {
    BigNumber num = numerator * other.denominator + other.numerator * denominator;
    BigNumber den = denominator * other.denominator;
    return BigRacNumber(num, den);
}

BigRacNumber BigRacNumber::operator-(const BigRacNumber &other) const {
    BigNumber num = numerator * other.denominator - other.numerator * denominator;
    BigNumber den = denominator * other.denominator;
    if (num < BigNumber(0))
        std::cout<<"Negative result not supported in subtraction\n";
    return BigRacNumber(num, den);
}

BigRacNumber BigRacNumber::operator*(const BigRacNumber &other) const {
    BigNumber num = numerator * other.numerator;
    BigNumber den = denominator * other.denominator;
    return BigRacNumber(num, den);
}

BigRacNumber &BigRacNumber::operator+=(const BigRacNumber &other) {
    *this = *this + other;
    return *this;
}

BigRacNumber &BigRacNumber::operator-=(const BigRacNumber &other) {
    *this = *this - other;
    return *this;
}

BigRacNumber &BigRacNumber::operator*=(const BigRacNumber &other) {
    *this = *this * other;
    return *this;
}

bool BigRacNumber::operator==(const BigRacNumber &other) const {
    return numerator * other.denominator == other.numerator * denominator;
}

bool BigRacNumber::operator!=(const BigRacNumber &other) const {
    return !(*this == other);
}

bool BigRacNumber::operator>(const BigRacNumber &other) const {
    return (numerator * other.denominator) > (other.numerator * denominator);
}

bool BigRacNumber::operator<(const BigRacNumber &other) const {
    return (numerator * other.denominator) < (other.numerator * denominator);
}

bool BigRacNumber::operator>=(const BigRacNumber &other) const {
    return !(*this < other);
}

bool BigRacNumber::operator<=(const BigRacNumber &other) const {
    return !(*this > other);
}

std::ostream &operator<<(std::ostream &os, const BigRacNumber &brn) {
    os << brn.numerator << " / " << brn.denominator;
    return os;
}

BigRacNumber BigRacNumber::inverse() const {
    if (numerator == BigNumber(0))
        std::cout <<"Cannot inverse zero\n";
    return BigRacNumber(denominator, numerator);
}

int BigRacNumber::operator||(int index) const {
    return numerator.getDigit(index);
}


