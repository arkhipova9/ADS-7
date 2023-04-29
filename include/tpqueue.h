// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
   sruct TPQItem {
     T data;
     TPQItem* next;
     TPQItem* prev;
   };
   TPQItem* head;
   TPQItem* tail;
   TPQueue::TPQItem* createTPQItem(const T&);
 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

typename TPQueue<T>::TPQItem* TPQueue<T>::createTPQItem(const T& data) {
    TPQItem* tqitem = new TPQItem;
    tqitem->data = data;
    tqitem->next = nullptr;
    tqitem->prev = nullptr;
    return tqitem;
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
        head = createTPQItem(a);
        tail = head;
    } else if (tail->data.prior >= a.prior) {
        if (tail->data.ch == a.ch) {
            tail->data = a;
        } else {
            tail->next = createTPQItem(a);
            tail->next->prev = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->prev = createQueueItem(a);
        head = tail->prev;
        head->next = tail;
    } else {
        TPQItem* temp1 = tail;
        while (temp1 != head && temp1->data.prior < a.prior) {
            temp1 = temp1->prev;
        }
        if (temp1->data.prior > a.prior) {
            TPQItem* cell = new TPQItem;
            cell->next = temp1->next;
            cell->prev = temp1;
            cell->data = a;
            temp1->next->prev = cell;
            temp1->next = cell;
        }
        if (temp1 == head && temp1->data.prior < a.prior) {
            head->prev = createTPQItem(a);
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
        TPQItem* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    TPQItem* temp = head;
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
