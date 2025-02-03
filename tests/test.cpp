#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstring>
#include "../BigNumber.h"
#include "../BigRacNumber.h"
#include "../List.h"

// Глобальная переменная для подсчёта ошибок
static int testFailures = 0;

#define CHECK(cond) do { \
    if (!(cond)) { \
        std::cerr << "[FAILED] " << __FILE__ << ":" << __LINE__ << " - " << #cond << std::endl; \
        ++testFailures; \
    } else { \
        std::cout << "[PASSED] " << __FILE__ << ":" << __LINE__ << " - " << #cond << std::endl; \
    } \
} while(0)

#define CHECK_EQ(val, expected) do { \
    auto _val = (val); \
    auto _expected = (expected); \
    if (_val != _expected) { \
        std::cerr << "[FAILED] " << __FILE__ << ":" << __LINE__ << " - Expected: " << _expected << ", got: " << _val << std::endl; \
        ++testFailures; \
    } else { \
        std::cout << "[PASSED] " << __FILE__ << ":" << __LINE__ << " - " << _val << " == " << _expected << std::endl; \
    } \
} while(0)

// ======================
// Тесты для BigNumber
// ======================

void testBigNumberConstructorsAndMethods() {
    std::stringstream ss;

    // Конструктор с int: значение 0
    BigNumber bn0(0);
    CHECK_EQ(bn0.Length(), 1);
    ss.str("");
    ss << bn0;
    CHECK_EQ(ss.str(), "0");

    // Конструктор с int: положительное число
    BigNumber bn1(12345);
    ss.str("");
    ss << bn1;
    CHECK_EQ(ss.str(), "12345");

    // Тест нецифровых символов в строке: должны игнорироваться
    BigNumber bnNonDigit("a1b2c3");
    ss.str("");
    ss << bnNonDigit;
    // При обработке строки "a1b2c3": цикл идёт с конца,
    // добавляются только символы '3','2','1' → вывод: "123"
    CHECK_EQ(ss.str(), "123");

    // Конструктор из строки
    BigNumber bn2("9876543210");
    ss.str("");
    ss << bn2;
    CHECK_EQ(ss.str(), "9876543210");

    // Конструктор копирования
    BigNumber bn3(bn1);
    ss.str("");
    ss << bn3;
    CHECK_EQ(ss.str(), "12345");

    // Тест getDigit: внутреннее хранение – обратный порядок.
    // Для bn1 ("12345") ожидаем: getDigit(0)==5, getDigit(4)==1.
    CHECK_EQ(bn1.getDigit(0), 5);
    CHECK_EQ(bn1.getDigit(4), 1);
    // При неверном индексе: вывод сообщения и возвращается -1.
    CHECK_EQ(bn1.getDigit(100), -1);

    // Вызов не-константного метода Length() (на не-const объекте)
    {
        BigNumber temp(6789);
        int len = temp.Length(); // вызов non-const перегрузки
        CHECK_EQ(len, 4);
    }

    // Тест статического метода reverseString для непустой строки
    std::string str = "abcde";
    BigNumber::reverseString(str);
    CHECK_EQ(str, "edcba");
    // Тест reverseString для пустой строки – должна остаться пустой
    std::string empty = "";
    BigNumber::reverseString(empty);
    CHECK_EQ(empty, "");
}

void testBigNumberArithmeticOperators() {
    std::stringstream ss;
    // Оператор +
    BigNumber a(123);
    BigNumber b(456);
    BigNumber sum = a + b; // 123 + 456 = 579
    ss.str("");
    ss << sum;
    CHECK_EQ(ss.str(), "579");

    // Оператор -
    BigNumber diff = b - a; // 456 - 123 = 333
    ss.str("");
    ss << diff;
    CHECK_EQ(ss.str(), "333");

    // Отрицательный результат: 123 - 456.
    // По реализации: выводится сообщение и возвращается BigNumber(-1).
    // Конструктор BigNumber(int) с -1 не входит в цикл (while(value > 0)),
    // поэтому результирующий список остаётся пустым и operator<< выводит пустую строку.
    BigNumber diffNeg = a - b;
    ss.str("");
    ss << diffNeg;
    CHECK_EQ(ss.str(), "");

    // Оператор *
    BigNumber prod = BigNumber(12) * BigNumber(34); // 12 * 34 = 408
    ss.str("");
    ss << prod;
    CHECK_EQ(ss.str(), "408");

    // Операторы +=, -=, *=
    BigNumber tmp(100);
    tmp += BigNumber(23); // 100 + 23 = 123
    ss.str("");
    ss << tmp;
    CHECK_EQ(ss.str(), "123");

    tmp -= BigNumber(23); // 123 - 23 = 100
    ss.str("");
    ss << tmp;
    CHECK_EQ(ss.str(), "100");

    tmp *= BigNumber(2); // 100 * 2 = 200
    ss.str("");
    ss << tmp;
    CHECK_EQ(ss.str(), "200");
}

void testBigNumberComparisons() {
    BigNumber bn1(12345);
    BigNumber bn2(12345);
    BigNumber bn3(54321);
    CHECK(bn1 == bn2);
    CHECK(!(bn1 != bn2));
    CHECK(bn1 < bn3);
    CHECK(bn3 > bn2);
    CHECK(bn1 <= bn2);
    CHECK(bn3 >= bn1);
}

// ======================
// Тесты для BigRacNumber
// ======================

void testBigRacNumberConstructorsAndMethods() {
    std::stringstream ss;

    // Конструктор с int
    BigRacNumber br1(5);
    ss.str("");
    ss << br1;
    CHECK_EQ(ss.str(), "5 / 1");

    // Конструктор из строки с разделителем '/'
    BigRacNumber br2("3/4");
    ss.str("");
    ss << br2;
    CHECK_EQ(ss.str(), "3 / 4");

    // Конструктор с двумя строковыми параметрами
    BigRacNumber br3("7", "8");
    ss.str("");
    ss << br3;
    CHECK_EQ(ss.str(), "7 / 8");

    // Конструктор копирования
    BigRacNumber br4(br2);
    ss.str("");
    ss << br4;
    CHECK_EQ(ss.str(), "3 / 4");

    // Конструктор с BigNumber
    BigNumber num(11), den(13);
    BigRacNumber br5(num, den);
    ss.str("");
    ss << br5;
    CHECK_EQ(ss.str(), "11 / 13");

    // Случай, когда знаменатель равен нулю (вывод сообщения, но объект создаётся)
    BigRacNumber brZero("5", "0");
    ss.str("");
    ss << brZero;
    CHECK_EQ(ss.str(), "5 / 0");

    // Тест оператора inverse()
    BigRacNumber br6("3/5");
    BigRacNumber inv = br6.inverse(); // должно дать 5/3
    ss.str("");
    ss << inv;
    CHECK_EQ(ss.str(), "5 / 3");

    // Если числитель равен 0, inverse() выводит сообщение и возвращает инверсию.
    BigRacNumber brZeroNum("0/7");
    BigRacNumber invZero = brZeroNum.inverse();
    ss.str("");
    ss << invZero;
    // Ожидаем: знаменатель становится числителем, а числитель – 0, т.е. "7 / 0"
    CHECK_EQ(ss.str(), "7 / 0");

    // Оператор ||: возвращает цифру из числителя (BigNumber).
    // Для br2 = "3/4" числитель равен 3.
    CHECK_EQ(br2 || 0, 3);
    // Если индекс выходит за границы, getDigit() возвращает -1.
    CHECK_EQ(br2 || 5, -1);
}

void testBigRacNumberArithmeticAndComparisons() {
    std::stringstream ss;

    BigRacNumber br1("1/2");
    BigRacNumber br2("1/3");

    // Оператор +
    BigRacNumber sum = br1 + br2; 
    // (1*3 + 1*2) / (2*3) = 5/6
    ss.str("");
    ss << sum;
    CHECK_EQ(ss.str(), "5 / 6");

    // Оператор -
    BigRacNumber diff = br1 - br2; 
    // (1*3 - 1*2) / (2*3) = 1/6
    ss.str("");
    ss << diff;
    CHECK_EQ(ss.str(), "1 / 6");

    // Отрицательный результат: 1/3 - 1/2.
    // В этом случае, по реализации, выводится сообщение, а числитель становится BigNumber(-1),
    // что приводит к пустому выводу для числителя.
    BigRacNumber diffNeg = br2 - br1;
    ss.str("");
    ss << diffNeg;
    // Ожидаемый вывод: пустой числитель, разделитель " / " и знаменатель равный 6.
    CHECK_EQ(ss.str(), " / 6");

    // Оператор *
    BigRacNumber prod = br1 * br2; // 1/2 * 1/3 = 1/6
    ss.str("");
    ss << prod;
    CHECK_EQ(ss.str(), "1 / 6");

    // Операторы +=, -=, *=
    BigRacNumber tmp("2/3");
    tmp += BigRacNumber("1/3"); // 2/3 + 1/3 = 3/3 = 1/1
    ss.str("");
    ss << tmp;
    CHECK_EQ(ss.str(), "1 / 1");

    tmp -= BigRacNumber("1/2"); // 1 - 1/2 = 1/2 (без сокращения)
    ss.str("");
    ss << tmp;
    CHECK_EQ(ss.str(), "1 / 2");

    tmp *= BigRacNumber("2/1"); // 1/2 * 2 = 2/2 = 1/1
    ss.str("");
    ss << tmp;
    CHECK_EQ(ss.str(), "1 / 1");

    // Тест сравнений
    BigRacNumber brA("3/5"), brB("6/10");
    CHECK(brA == brB);
    CHECK(!(brA != brB));
    CHECK(brA <= brB);
    CHECK(brA >= brB);
    CHECK(!(brA < brB));
    CHECK(!(brA > brB));
}

// ======================
// Тесты для List
// ======================

void testListOperations() {
    std::stringstream ss;

    // Тест конструктора и Add() на пустом списке
    List list;
    CHECK_EQ(list.Length(), 0);
    list.Add(1);
    list.Add(2);
    list.Add(3);
    CHECK_EQ(list.Length(), 3);

    // Тест Reset, GetCurrent, Move и EoList
    list.Reset();
    CHECK_EQ(list.GetCurrent(), 1);
    list.Move();
    CHECK_EQ(list.GetCurrent(), 2);
    list.Move();
    CHECK_EQ(list.GetCurrent(), 3);
    list.Move();
    CHECK(list.EoList());

    // Тест Del() – удаление первого элемента (когда marker указывает на начало)
    list.Reset();
    list.Del(); // удаляем элемент "1"
    CHECK_EQ(list.Length(), 2);
    list.Reset();
    CHECK_EQ(list.GetCurrent(), 2);

    // Тест AddBefore(): вставка элемента перед marker
    list.Reset();
    list.Move(); // marker указывает на второй элемент (значение  ?)
    list.AddBefore(99); // вставляем перед текущим элементом
    ss.str("");
    ss << list;
    // Ожидаем последовательность: 2 -> 99 -> оставшийся элемент(был 3)
    CHECK_EQ(ss.str(), "2 -> 99 -> 3");

    // Тест метода addLists()
    List listA;
    listA.Add(1);
    listA.Add(2);
    List listB;
    listB.Add(3);
    listB.Add(4);
    List listSum = listA.addLists(listA, listB);
    // Складываем: (1+3), (2+4) = 4,6
    ss.str("");
    ss << listSum;
    CHECK_EQ(ss.str(), "4 -> 6");

    // Тест оператора присваивания operator=
    List listC;
    listC.Add(7);
    listC.Add(8);
    List listD;
    listD = listC;
    ss.str("");
    ss << listD;
    CHECK_EQ(ss.str(), "7 -> 8");

    // Тест self-assignment operator=
    listD = listD;
    ss.str("");
    ss << listD;
    CHECK_EQ(ss.str(), "7 -> 8");

    // Тест конструктора копирования для пустого списка
    List listEmpty;
    List listEmptyCopy(listEmpty);
    ss.str("");
    ss << listEmptyCopy;
    CHECK_EQ(ss.str(), "");

    // Тест RemoveTrailingZeros()
    List listE;
    listE.Add(1);
    listE.Add(0);
    listE.Add(0);
    listE.Add(2);
    listE.Add(0);
    listE.RemoveTrailingZeros();
    ss.str("");
    ss << listE;
    // Ожидаем: 1 -> 0 -> 0 -> 2
    CHECK_EQ(ss.str(), "1 -> 0 -> 0 -> 2");

    // Тест GetCurrent() и Move() на пустом списке
    List listF;
    // Попытка получить текущий элемент из пустого списка – должно вывести сообщение и вернуть -1.
    CHECK_EQ(listF.GetCurrent(), -1);
    // Попытка Move() – ничего не должно измениться.
    listF.Move();
    
    // Тест Del() на пустом списке – должно вывести сообщение, не менять длину.
    listF.Del();
    CHECK_EQ(listF.Length(), 0);
}

// ======================
// main
// ======================

int main() {
    std::cout << "Запуск тестов для BigNumber...\n";
    testBigNumberConstructorsAndMethods();
    testBigNumberArithmeticOperators();
    testBigNumberComparisons();

    std::cout << "\nЗапуск тестов для BigRacNumber...\n";
    testBigRacNumberConstructorsAndMethods();
    testBigRacNumberArithmeticAndComparisons();

    std::cout << "\nЗапуск тестов для List...\n";
    testListOperations();

    if (testFailures == 0) {
        std::cout << "\nВсе тесты пройдены успешно.\n";
    } else {
        std::cerr << "\nВсего ошибок: " << testFailures << std::endl;
    }
    return testFailures;
}
