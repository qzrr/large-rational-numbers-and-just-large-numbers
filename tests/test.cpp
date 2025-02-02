#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
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

// Тестируем конструкторы BigNumber и getDigit()
void testBigNumberConstructors() {
    std::stringstream ss;
    
    // Конструктор с int
    BigNumber bn0(0);
    CHECK_EQ(bn0.Length(), 1);
    ss.str("");
    ss << bn0;
    CHECK_EQ(ss.str(), "0");

    BigNumber bn1(12345);
    ss.str("");
    ss << bn1;
    CHECK_EQ(ss.str(), "12345");

    // Проверка getDigit: BigNumber хранит цифры в обратном порядке
    // Для 12345 цифры внутри: 5,4,3,2,1 – поэтому getDigit(0)==5, getDigit(4)==1.
    CHECK_EQ(bn1.getDigit(0), 5);
    CHECK_EQ(bn1.getDigit(4), 1);
    try {
        bn1.getDigit(5);
        std::cerr << "[FAILED] " << "bn1.getDigit(5) - ожидается исключение" << std::endl;
        ++testFailures;
    } catch (std::out_of_range &) {
        std::cout << "[PASSED] " << "bn1.getDigit(5) вызвало исключение" << std::endl;
    }

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
}

// Тест арифметических операций BigNumber
void testBigNumberArithmetic() {
    std::stringstream ss;
    
    // Сложение
    BigNumber a(123);
    BigNumber b(456);
    BigNumber sum = a + b; // 123 + 456 = 579
    ss.str("");
    ss << sum;
    CHECK_EQ(ss.str(), "579");

    // Сложение с переносом
    BigNumber c(999);
    BigNumber d(1);
    BigNumber sum2 = c + d; // 999 + 1 = 1000
    ss.str("");
    ss << sum2;
    CHECK_EQ(ss.str(), "1000");

    // Вычитание (без отрицательного результата)
    BigNumber e(456);
    BigNumber f(123);
    BigNumber diff = e - f; // 456 - 123 = 333
    ss.str("");
    ss << diff;
    CHECK_EQ(ss.str(), "333");

    // Вычитание, требующее займа
    BigNumber g(1000);
    BigNumber h(1);
    BigNumber diff2 = g - h; // 1000 - 1 = 999
    ss.str("");
    ss << diff2;
    CHECK_EQ(ss.str(), "999");

    // Проверка исключения при отрицательном результате
    try {
        BigNumber i(123);
        BigNumber j(456);
        BigNumber r = i - j;
        (void)r;
        std::cerr << "[FAILED] " << "Ожидалось исключение при вычитании 123 - 456" << std::endl;
        ++testFailures;
    } catch (std::runtime_error &) {
        std::cout << "[PASSED] " << "Исключение при вычитании 123 - 456" << std::endl;
    }

    // Умножение
    BigNumber k(12);
    BigNumber l(34);
    BigNumber prod = k * l; // 12 * 34 = 408
    ss.str("");
    ss << prod;
    CHECK_EQ(ss.str(), "408");
}

// Тест сравнения BigNumber
void testBigNumberComparison() {
    BigNumber a(12345);
    BigNumber b(12345);
    BigNumber c(54321);
    CHECK(a == b);
    CHECK(!(a != b));
    CHECK(a < c);
    CHECK(c > b);
    CHECK(a <= b);
    CHECK(c >= a);
}

// Тестируем конструкторы BigRacNumber
void testBigRacNumberConstructors() {
    std::stringstream ss;
    
    // Конструктор с целым числом
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
}

// Тест арифметики BigRacNumber
void testBigRacNumberArithmetic() {
    std::stringstream ss;
    
    BigRacNumber br1("1/2");
    BigRacNumber br2("1/3");

    // Сложение: 1/2 + 1/3 = (1*3 + 1*2)/6 = 5/6
    BigRacNumber sum = br1 + br2;
    ss.str("");
    ss << sum;
    CHECK_EQ(ss.str(), "5 / 6");

    // Вычитание: 1/2 - 1/3 = (1*3 - 1*2)/6 = 1/6
    BigRacNumber diff = br1 - br2;
    ss.str("");
    ss << diff;
    CHECK_EQ(ss.str(), "1 / 6");

    // Проверка исключения при отрицательном результате вычитания
    try {
        BigRacNumber br5("1/3");
        BigRacNumber br6("1/2");
        BigRacNumber r = br5 - br6;
        (void)r;
        std::cerr << "[FAILED] " << "Ожидалось исключение при вычитании 1/3 - 1/2" << std::endl;
        ++testFailures;
    } catch (std::runtime_error &) {
        std::cout << "[PASSED] " << "Исключение при вычитании 1/3 - 1/2" << std::endl;
    }

    // Умножение: 1/2 * 1/3 = 1/6
    BigRacNumber prod = br1 * br2;
    ss.str("");
    ss << prod;
    CHECK_EQ(ss.str(), "1 / 6");
}

// Тест методов inverse и оператора получения цифры (||) для BigRacNumber
void testBigRacNumberInverseAndIndex() {
    std::stringstream ss;
    
    BigRacNumber br("3/5");
    BigRacNumber inv = br.inverse();
    ss.str("");
    ss << inv;
    CHECK_EQ(ss.str(), "5 / 3");

    // Оператор || возвращает цифру из числителя (в BigNumber, числитель 3 хранится как "3")
    int d = br || 0;
    CHECK_EQ(d, 3);

    // Проверяем выход за пределы (исключение)
    try {
        int d2 = br || 1;
        (void)d2;
        std::cerr << "[FAILED] " << "Ожидалось исключение при доступе по несуществующему индексу" << std::endl;
        ++testFailures;
    } catch (std::out_of_range &) {
        std::cout << "[PASSED] " << "Исключение при доступе по несуществующему индексу" << std::endl;
    }
}

// Тест операций над List
void testListOperations() {
    std::stringstream ss;
    
    // Создаем список и добавляем элементы
    List list;
    list.Add(1);
    list.Add(2);
    list.Add(3);
    CHECK_EQ(list.Length(), 3);

    // Тест Reset, GetCurrent, Move
    list.Reset();
    int a = list.GetCurrent();
    CHECK_EQ(a, 1);
    list.Move();
    int b = list.GetCurrent();
    CHECK_EQ(b, 2);
    list.Move();
    int c = list.GetCurrent();
    CHECK_EQ(c, 3);

    // Удаляем элемент (удаляем средний элемент)
    list.Reset();
    list.Move(); // теперь marker на втором элементе
    list.Del();
    CHECK_EQ(list.Length(), 2);
    list.Reset();
    CHECK_EQ(list.GetCurrent(), 1);
    list.Move();
    CHECK_EQ(list.GetCurrent(), 3);

    // Тест RemoveTrailingZeros:
    // Формируем список: 1 -> 0 -> 0 -> 2 -> 0, где последний 0 – лишний.
    List list2;
    list2.Add(1);
    list2.Add(0);
    list2.Add(0);
    list2.Add(2);
    list2.Add(0);
    list2.RemoveTrailingZeros();
    // После удаления лишних нулей список должен содержать до последнего ненулевого элемента.
    // То есть список должен быть: 1 -> 0 -> 0 -> 2
    ss.str("");
    ss << list2;
    std::string expected = "1 -> 0 -> 0 -> 2";
    CHECK_EQ(ss.str(), expected);
}

int main() {
    std::cout << "Запуск тестов...\n";

    testBigNumberConstructors();
    testBigNumberArithmetic();
    testBigNumberComparison();
    testBigRacNumberConstructors();
    testBigRacNumberArithmetic();
    testBigRacNumberInverseAndIndex();
    testListOperations();

    if (testFailures == 0) {
        std::cout << "\nВсе тесты пройдены успешно.\n";
    } else {
        std::cerr << "\nВсего ошибок: " << testFailures << std::endl;
    }
    return testFailures;
}
