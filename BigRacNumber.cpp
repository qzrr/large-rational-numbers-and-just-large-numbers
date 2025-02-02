
#include "BigRacNumber.h"

// Конструктор с одним параметром (целое число)
BigRacNumber::BigRacNumber(int value) : numerator(value), denomator(1) {}

// Конструктор с одним параметром (строка)
BigRacNumber::BigRacNumber(const char *str) {
    // Если в строке есть символ '/', то считаем, что задана дробь вида "num/den"
    std::string s(str);
    size_t pos = s.find('/');
    if (pos != std::string::npos) {
        std::string numStr = s.substr(0, pos);
        std::string denStr = s.substr(pos + 1);
        numerator = BigNumber(numStr.c_str());
        denomator = BigNumber(denStr.c_str());
    } else {
        numerator = BigNumber(str);
        denomator = BigNumber(1);
    }
}

// Конструктор с двумя целочисленными параметрами
BigRacNumber::BigRacNumber(int num, int den) : numerator(num), denomator(den) {
    if (den == 0)
        throw std::runtime_error("Denominator cannot be zero");
}
BigRacNumber::BigRacNumber(const BigNumber &num, const BigNumber &den)
        : numerator(num), denomator(den) {
    if (denomator == BigNumber(0))
        throw std::runtime_error("Denominator cannot be zero");
}

// Конструктор с двумя строковыми параметрами
BigRacNumber::BigRacNumber(const char *numStr, const char *denStr)
        : numerator(numStr), denomator(denStr) {
    // Проверяем, что знаменатель не равен 0
    if (denomator == BigNumber(0))
        throw std::runtime_error("Denominator cannot be zero");
}

// Конструктор копирования
BigRacNumber::BigRacNumber(const BigRacNumber &other)
        : numerator(other.numerator), denomator(other.denomator) {}

// Арифметика для рациональных чисел
// a/b + c/d = (a*d + c*b) / (b*d)
BigRacNumber BigRacNumber::operator+(const BigRacNumber &other) const {
    BigNumber num = numerator * other.denomator + other.numerator * denomator;
    BigNumber den = denomator * other.denomator;
    return BigRacNumber(num, den);
}

BigRacNumber BigRacNumber::operator-(const BigRacNumber &other) const {
    BigNumber num = numerator * other.denomator - other.numerator * denomator;
    BigNumber den = denomator * other.denomator;
    if (num < BigNumber(0))
        throw std::runtime_error("Negative result not supported in subtraction");
    return BigRacNumber(num, den);
}

BigRacNumber BigRacNumber::operator*(const BigRacNumber &other) const {
    BigNumber num = numerator * other.numerator;
    BigNumber den = denomator * other.denomator;
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

// Операторы сравнения (сравнение дробей по перекрёстному умножению)
bool BigRacNumber::operator==(const BigRacNumber &other) const {
    return numerator * other.denomator == other.numerator * denomator;
}

bool BigRacNumber::operator!=(const BigRacNumber &other) const {
    return !(*this == other);
}

bool BigRacNumber::operator>(const BigRacNumber &other) const {
    return (numerator * other.denomator) > (other.numerator * denomator);
}

bool BigRacNumber::operator<(const BigRacNumber &other) const {
    return (numerator * other.denomator) < (other.numerator * denomator);
}

bool BigRacNumber::operator>=(const BigRacNumber &other) const {
    return !(*this < other);
}

bool BigRacNumber::operator<=(const BigRacNumber &other) const {
    return !(*this > other);
}

// Оператор вывода в поток
std::ostream &operator<<(std::ostream &os, const BigRacNumber &brn) {
    os << brn.numerator << " / " << brn.denomator;
    return os;
}

// Метод inverse: возвращает обратную дробь
BigRacNumber BigRacNumber::inverse() const {
    if (numerator == BigNumber(0))
        throw std::runtime_error("Cannot inverse zero");
    return BigRacNumber(denomator, numerator);
}

// Оператор || возвращает цифру по индексу (из числителя)
int BigRacNumber::operator||(int index) const {
    return numerator.getDigit(index);
}


