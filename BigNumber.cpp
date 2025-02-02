#include "BigNumber.h"
#include <cstring>
#include <algorithm>

// Конструктор с параметром (целое число)
BigNumber::BigNumber(int value) {
    if (value == 0) {
        Add(0); // Если число равно нулю, добавляем одну цифру
    } else {
        while (value > 0) {
            Add(value % 10); // Добавляем младшую цифру
            value /= 10;
        }
    }
}

// Конструктор копирования
BigNumber::BigNumber(const BigNumber &other) : List(other) {}

// Конструктор из символьного массива
BigNumber::BigNumber(const char *str) {
    for (int i = strlen(str) - 1; i >= 0; --i) {
        if (isdigit(str[i])) {
            Add(str[i] - '0'); // Преобразуем символ в цифру
        }
    }
}

static int compareBigNumbers(const BigNumber &a, const BigNumber &b) {
    int lenA = a.Length();
    int lenB = b.Length();
    if (lenA < lenB)
        return -1;
    if (lenA > lenB)
        return 1;
    // Если длины равны – сравниваем, проходя от старшей цифры
    // Для этого собираем строку (так как цифры хранятся в обратном порядке)
    std::string sa, sb;
    {
        List temp(a);
        temp.Reset();
        while (!temp.EoList()) {
            sa += std::to_string(temp.GetCurrent());
            temp.Move();
        }
    }
    {
        List temp(b);
        temp.Reset();
        while (!temp.EoList()) {
            sb += std::to_string(temp.GetCurrent());
            temp.Move();
        }
    }
    std::reverse(sa.begin(), sa.end());
    std::reverse(sb.begin(), sb.end());
    if (sa < sb)
        return -1;
    if (sa > sb)
        return 1;
    return 0;
}

// Оператор сложения
BigNumber BigNumber::operator+(const BigNumber &other) const {
    BigNumber result;
    Node *a = top;
    Node *b = other.top;
    int carry = 0;

    while (a || b || carry) {
        int sum = carry;
        if (a) {
            sum += a->data;
            a = a->next;
        }
        if (b) {
            sum += b->data;
            b = b->next;
        }

        // Добавляем только значимую цифру
        result.Add(sum % 10);
        carry = sum / 10;
    }

    // Удаляем лишний ноль, если он есть в начале списка
    result.Reset(); // Ставим маркер на начало
    if (result.Length() > 1 && result.GetCurrent() == 0) {
        result.Del(); // Удаляем лишний ноль
    }

    return result;
}
BigNumber BigNumber::operator-(const BigNumber &other) const {
    if (*this < other)
        throw std::runtime_error("Negative result not supported");
    BigNumber result;
    int carry = 0;
    // Для вычитания проходим по цифрам (числа хранятся в обратном порядке)
    List temp1(*this), temp2(other);
    temp1.Reset();
    temp2.Reset();
    while (!temp1.EoList() || !temp2.EoList()) {
        int a = (!temp1.EoList() ? temp1.GetCurrent() : 0);
        int b = (!temp2.EoList() ? temp2.GetCurrent() : 0);
        int sub = a - b - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.Add(sub);
        if (!temp1.EoList()) temp1.Move();
        if (!temp2.EoList()) temp2.Move();
    }
    result.RemoveTrailingZeros();
    return result;
}

BigNumber BigNumber::operator*(const BigNumber &other) const {
    List result; // Результат в виде списка (цифры в обратном порядке)
    Node *b = other.top;  // Перебираем цифры второго числа (от младшего к старшему)
    int shift = 0;        // Сдвиг (количество нулей для умножения на 10^shift)

    while (b) {
        Node *a = top;
        List intermediate;
        for (int i = 0; i < shift; ++i) {
            intermediate.Add(0);
        }

        int carry = 0;
        while (a) {
            int product = a->data * b->data + carry;
            intermediate.Add(product % 10);
            carry = product / 10;
            a = a->next;
        }
        if (carry > 0) {
            intermediate.Add(carry);
        }

        // Складываем промежуточный результат с уже накопленным результатом
        result = addLists(result, intermediate);
        b = b->next;
        ++shift;
    }

    result.RemoveTrailingZeros();
    // Используем новый конструктор для копирования готового списка в BigNumber
    BigNumber finalResult(result);
    finalResult.RemoveTrailingZeros();
    return finalResult;
}

BigNumber &BigNumber::operator+=(const BigNumber &other) {
    *this = *this + other;
    return *this;
}

BigNumber &BigNumber::operator-=(const BigNumber &other) {
    *this = *this - other;
    return *this;
}

BigNumber &BigNumber::operator*=(const BigNumber &other) {
    *this = *this * other;
    return *this;
}

// Операторы сравнения
bool BigNumber::operator==(const BigNumber &other) const {
    return compareBigNumbers(*this, other) == 0;
}

bool BigNumber::operator!=(const BigNumber &other) const {
    return !(*this == other);
}

bool BigNumber::operator>(const BigNumber &other) const {
    return compareBigNumbers(*this, other) > 0;
}

bool BigNumber::operator<(const BigNumber &other) const {
    return compareBigNumbers(*this, other) < 0;
}

bool BigNumber::operator>=(const BigNumber &other) const {
    return !(*this < other);
}

bool BigNumber::operator<=(const BigNumber &other) const {
    return !(*this > other);
}


// Оператор вывода в поток
std::ostream &operator<<(std::ostream &os, const BigNumber &num) {
    List temp(num); // Создаём копию для обхода
    temp.Reset();
    std::string result;

    while (!temp.EoList()) {
        result += std::to_string(temp.GetCurrent());
        temp.Move();
    }

    std::reverse(result.begin(), result.end()); // Переворачиваем строку
    os << result;
    return os;
}

// Длина числа
int BigNumber::Length() const {
    int count = 0;
    Node *current = top;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}

int BigNumber::Length() {
    int count = 0;
    Node *current = top;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}
int BigNumber::getDigit(int index) const {
    int i = 0;
    List temp(*this);
    temp.Reset();
    while (!temp.EoList()) {
        if (i == index)
            return temp.GetCurrent();
        ++i;
        temp.Move();
    }
    throw std::out_of_range("Digit index out of range");
}