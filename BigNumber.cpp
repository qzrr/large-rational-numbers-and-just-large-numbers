#include "BigNumber.h"

BigNumber::BigNumber(int value) {
    if (value == 0) {
        Add(0);
    } else {
        while (value > 0) {
            Add(value % 10);
            value /= 10;
        }
    }
}

BigNumber::BigNumber(const BigNumber &other) : List(other) {}

BigNumber::BigNumber(const char *str) {
    for (int i = strlen(str) - 1; i >= 0; --i) {
        if (isdigit(str[i])) {
            Add(str[i] - '0');
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
    std::string sa, sb;
    List temp1(a);
    temp1.Reset();
    while (!temp1.EoList()) {
        sa += std::to_string(temp1.GetCurrent());
        temp1.Move();
    }
    List temp2(b);
    temp2.Reset();
    while (!temp2.EoList()) {
        sb += std::to_string(temp2.GetCurrent());
        temp2.Move();
    }
    BigNumber::reverseString(sa);
    BigNumber::reverseString(sb);
    if (sa < sb)
        return -1;
    if (sa > sb)
        return 1;
    return 0;
}

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

        result.Add(sum % 10);
        carry = sum / 10;
    }

    result.Reset();
    if (result.Length() > 1 && result.GetCurrent() == 0) {
        result.Del();
    }

    return result;
}

BigNumber BigNumber::operator-(const BigNumber &other) const {
    if (*this < other)
        std::cout << "Negative result not supported\n";
    BigNumber result;
    int carry = 0;
    List temp1(*this), temp2(other);
    temp1.Reset();
    temp2.Reset();
    while (!temp1.EoList() || !temp2.EoList()) {
        int a = 0;
        if (!temp1.EoList()) {
            a = temp1.GetCurrent();
        }
        int b = 0;
        if (!temp2.EoList()) {
            b = temp2.GetCurrent();
        }
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
    List result;
    Node *b = other.top;
    int shift = 0;

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

        result = addLists(result, intermediate);
        b = b->next;
        ++shift;
    }

    result.RemoveTrailingZeros();
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


std::ostream &operator<<(std::ostream &os, const BigNumber &num) {
    List temp(num);
    temp.Reset();
    std::string result;

    while (!temp.EoList()) {
        result += std::to_string(temp.GetCurrent());
        temp.Move();
    }

    BigNumber::reverseString(result);
    os << result;
    return os;
}

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
    std::cout << "Digit index out of range\n";
    return -1;
}

void BigNumber::reverseString(std::string &str) {
    if (str.empty())return;

    size_t left = 0, right = str.size() - 1;
    while (left < right)
        std::swap(str[left++], str[right--]);
}

