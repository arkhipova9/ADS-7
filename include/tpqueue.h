// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
  struct QItem {
    T data;
    QItem* next;
    QItem* prev;
  };
  QItem* head;
  QItem* tail;
  TPQueue::QItem* createQItem(const T&);
 public:
    TPQueue():head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

typename TPQueue<T>::QItem* TPQueue<T>::createQItem(const T& data) {
    QItem* item = new QItem;
    item->data = data;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
void TPQueue<T>::push(const T& a) {
    if (head == nullptr) {
        head = createQItem(a);
        tail = head;
    } else if (tail->data.prior >= a.prior) {
        if (tail->data.ch == a.ch) {
            tail->data = a;
        } else {
            tail->next = createQItem(a);
            tail->next->prev = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->prev = createQItem(a);
        head = tail->prev;
        head->next = tail;
    } else {
        QItem* temp1 = tail;
        while (temp1 != head && temp1->data.prior < a.prior) {
            temp1 = temp1->prev;
        }
        if (temp1->data.prior > a.prior) {
            QItem* cell = new QItem;
            cell->next = temp1->next;
            cell->prev = temp1;
            cell->data = a;
            temp1->next->prev = cell;
            temp1->next = cell;
        }
        if (temp1 == head && temp1->data.prior < a.prior) {
            head->prev = createQItem(a);
            head = head->prev;
            head->next = temp1;
        }
    }
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("EMPTY!");
    } else {
        QItem* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    QItem* temp = head;
    while (temp) {
        std::cout << temp->data.ch << temp->data.prior << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}
struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
