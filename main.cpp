#include "BigRacNumber.h"

int main() {

    std::cout << "==== BigNumber ====" << std::endl;
    BigNumber a(12345);
    BigNumber b("6789");
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    BigNumber c = a + b;
    std::cout << "a + b = " << c << std::endl;

    BigNumber d = a - BigNumber(1);
    std::cout << "a - 2345 = " << d << std::endl;

    BigNumber e = a * b;
    std::cout << "a * b = " << e << std::endl;

    a += b;
    std::cout << "a += b, a = " << a << std::endl;

    if (a > b) {
        std::cout << "a > b" << std::endl;
    } else {
        std::cout << "a <= b" << std::endl;
    }

    std::cout << "Digit b with index 2 (low-order digits): " << b.getDigit(2) << std::endl;

    std::cout << "\n==== BigRacNumber ====" << std::endl;
    BigRacNumber r1(5);
    BigRacNumber r2("3/4");
    BigRacNumber r(5, 6);
    std::cout << "r1 = " << r1 << std::endl;
    std::cout << "r2 = " << r2 << std::endl;

    BigRacNumber r3 = r1 + r2;
    std::cout << "r1 + r2 = " << r3 << std::endl;

    BigRacNumber r4 = r1 * r2;
    std::cout << "r1 * r2 = " << r4 << std::endl;

    BigRacNumber r5 = r3.inverse();
    std::cout << "inverse(r3) = " << r5 << std::endl;

    r3 += r1;
    std::cout << "r3 += r1, r3 = " << r3 << std::endl;
    if (r1 < r2) {
        std::cout << "r1 < r2" << std::endl;
    } else {
        std::cout << "r1 >= r2" << std::endl;
    }

    int index = 1;
    std::cout << "The digit of the numerator r2 with the index " << index << " = " << (r2 || index) << std::endl;
    return 0;
}
