#include "List.h"
#include <iostream>

using namespace std;

// Конструктор: создаёт пустой список
List::List() : top(nullptr), marker(nullptr), pred(nullptr) {}

// Конструктор копирования
List::List(const List &other) : top(nullptr), marker(nullptr), pred(nullptr) {
    Node *current = other.top;
    Node *tail = nullptr; // Указатель на последний добавленный узел

    while (current) {
        Node *newNode = new Node(current->data); // Создаём новый узел
        if (!top) {
            top = newNode; // Если список пуст, новый узел становится головой
        } else {
            tail->next = newNode; // Присоединяем новый узел к концу списка
        }
        tail = newNode; // Обновляем указатель на последний узел
        current = current->next;
    }
}

// Деструктор
List::~List() {
    while (top) {
        Node *temp = top;
        top = top->next;
        delete temp;
    }
}

// Установить маркер на начало списка
void List::Reset() {
    marker = top;
    pred = nullptr;
}

// Доступ к информационному полю текущего элемента
int List::GetCurrent() const {
    if (!marker) throw runtime_error("Marker is null");
    return marker->data;
}

// Сдвиг по списку на один шаг
void List::Move() {
    if (!marker) throw runtime_error("Marker is null");
    pred = marker;
    marker = marker->next;
}

// Проверка, находится ли маркер на конце списка
bool List::EoList() const {
    return marker == nullptr;
}

// Добавить элемент перед текущим
void List::AddBefore(int value) {
    Node *newNode = new Node(value);
    if (!pred) { // Если добавляем перед первым элементом
        newNode->next = top;
        top = newNode;
    } else {
        newNode->next = pred->next;
        pred->next = newNode;
    }
    marker = newNode; // Перемещаем маркер на новый элемент
}

// Добавить элемент после текущего
void List::Add(int value) {
    Node *newNode = new Node(value);
    if (!top) { // Если список пуст
        top = marker = newNode;
    } else {
        Node *current = top;
        while (current->next) { // Находим последний узел
            current = current->next;
        }
        current->next = newNode; // Добавляем новый узел в конец
    }
}

// Удалить текущий элемент
void List::Del() {
    if (!marker) throw runtime_error("Marker is null");

    if (!pred) { // Если удаляем первый элемент
        Node *temp = top;
        top = marker->next;
        marker = top; // Перемещаем маркер на новый первый элемент
        delete temp;
    } else {
        Node *temp = marker;
        pred->next = marker->next;
        marker = marker->next; // Перемещаем маркер на следующий элемент
        delete temp;
    }
}

// Метод для сложения двух списков
List List::addLists(const List &list1, const List &list2) const {
    List result;
    Node *a = list1.top;
    Node *b = list2.top;
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

    return result;
}

std::ostream &operator<<(std::ostream &os, const List &list) {
    List::Node *current = list.top; // Начинаем с головы списка
    while (current) {
        os << current->data; // Выводим значение текущего узла
        if (current->next) {
            os << " -> "; // Разделитель между элементами
        }
        current = current->next;
    }
    return os;
}

// Оператор присваивания
List &List::operator=(const List &other) {
    if (this == &other) return *this; // Защита от самоприсваивания

    // Освобождаем текущие ресурсы
    while (top) {
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    // Создаём глубокую копию
    Node *current = other.top;
    Node *tail = nullptr;

    while (current) {
        Node *newNode = new Node(current->data);
        if (!top) {
            top = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        current = current->next;
    }

    marker = nullptr; // Сбрасываем маркер
    pred = nullptr;   // Сбрасываем предыдущий элемент
    return *this;
}

// Метод для получения длины списка
int List::Length() const {
    int count = 0;
    Node* current = top;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}
// Метод для удаления лишних нулей в конце списка
void List::RemoveTrailingZeros() {
    if (!top) return; // Если список пуст, ничего не делаем

    Node* current = top;
    Node* lastNonZero = nullptr;

    // Находим последний ненулевой элемент
    while (current) {
        if (current->data != 0) {
            lastNonZero = current;
        }
        current = current->next;
    }

    // Если все элементы нули, оставляем один ноль
    if (!lastNonZero) {
        while (top->next) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
        return;
    }

    // Удаляем все элементы после последнего ненулевого
    current = lastNonZero->next;
    lastNonZero->next = nullptr;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}