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

    Node *top;
    Node *marker;
    Node *pred;

public:
    List();

    List(const List &other);

    ~List();

    void Reset();

    int GetCurrent() const;

    void Move();

    bool EoList() const;

    void AddBefore(int value);

    void Add(int value);

    void Del();

    List addLists(const List &list1, const List &list2) const;

    friend std::ostream &operator<<(std::ostream &os, const List &list);

    List &operator=(const List &other);

    virtual int Length() const;

    void RemoveTrailingZeros();

};


#endif //COURSEWORK1_LIST_H
