#include "List.h"
#include <iostream>

using namespace std;

List::List() : top(nullptr), marker(nullptr), pred(nullptr) {}

List::List(const List &other) : top(nullptr), marker(nullptr), pred(nullptr) {
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
}

List::~List() {
    while (top) {
        Node *temp = top;
        top = top->next;
        delete temp;
    }
}

void List::Reset() {
    marker = top;
    pred = nullptr;
}

int List::GetCurrent() const {
    if (!marker) {
        cout << "Marker is null\n";
        return -1;
    }
    return marker->data;
}

void List::Move() {
    if (!marker) {
        cout << "Marker is null\n";
        return;
    }
    pred = marker;
    marker = marker->next;
}

bool List::EoList() const {
    return marker == nullptr;
}

void List::AddBefore(int value) {
    Node *newNode = new Node(value);
    if (!pred) {
        newNode->next = top;
        top = newNode;
    } else {
        newNode->next = pred->next;
        pred->next = newNode;
    }
    marker = newNode;
}

void List::Add(int value) {
    Node *newNode = new Node(value);
    if (!top) {
        top = marker = newNode;
    } else {
        Node *current = top;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void List::Del() {
    if (!marker) {
        cout << "Marker is null\n";
        return;
    }
    if (!pred) {
        Node *temp = top;
        top = marker->next;
        marker = top;
        delete temp;
    } else {
        Node *temp = marker;
        pred->next = marker->next;
        marker = marker->next;
        delete temp;
    }
}

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
    List::Node *current = list.top;
    while (current) {
        os << current->data;
        if (current->next) {
            os << " -> ";
        }
        current = current->next;
    }
    return os;
}

List &List::operator=(const List &other) {
    if (this == &other) return *this;

    while (top) {
        Node *temp = top;
        top = top->next;
        delete temp;
    }

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

    marker = nullptr;
    pred = nullptr;
    return *this;
}

int List::Length() const {
    int count = 0;
    Node *current = top;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}

void List::RemoveTrailingZeros() {
    if (!top) return;

    Node *current = top;
    Node *lastNonZero = nullptr;

    while (current) {
        if (current->data != 0) {
            lastNonZero = current;
        }
        current = current->next;
    }

    if (!lastNonZero) {
        while (top->next) {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
        return;
    }

    current = lastNonZero->next;
    lastNonZero->next = nullptr;
    while (current) {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
}