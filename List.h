#ifndef COURSEWORK1_LIST_H
#define COURSEWORK1_LIST_H

#include <iostream>

class List {
protected:
    struct Node {
        int data;
        Node *next;

        explicit Node(int value) : data(value), next(nullptr) {}
    };

    Node *top;      // Указатель на начало списка
    Node *marker;   // Указатель на текущий элемент
    Node *pred;     // Указатель на элемент перед текущим

public:
    // Конструктор: создаёт пустой список
    List();

    // Конструктор копирования
    List(const List &other);

    // Деструктор
    ~List();

    // Установить маркер на начало списка
    void Reset();

    // Доступ к информационному полю текущего элемента
    int GetCurrent() const;

    // Сдвиг по списку на один шаг
    void Move();

    // Проверка, находится ли маркер на конце списка
    bool EoList() const;

    // Добавить элемент перед текущим
    void AddBefore(int value);

    // Добавить элемент после текущего
    void Add(int value);

    // Удалить текущий элемент
    void Del();

    List addLists(const List &list1, const List &list2) const;

    friend std::ostream &operator<<(std::ostream &os, const List &list);

    List &operator=(const List &other);

    virtual int Length() const;

    void RemoveTrailingZeros();

};


#endif //COURSEWORK1_LIST_H
