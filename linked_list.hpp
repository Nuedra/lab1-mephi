#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "smrtptr.hpp"
#include <iostream>

template<typename T>
struct Node {
    T data;
    SmrtPtr<Node<T>> next;

    explicit Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    SmrtPtr<Node<T>> head;
    size_t length;

public:
    LinkedList() : head(nullptr), length(0) {}

    void push_front(const T& value) {
        SmrtPtr<Node<T>> newNode(new Node<T>(value));
        newNode->next = std::move(head);
        head = std::move(newNode);
        ++length;
    }

    bool null() const {
        return head.null();
    }

    void pop_front() {
        if (!head.null()) {
            SmrtPtr<Node<T>> oldHead = std::move(head);
            head = std::move(oldHead->next);
            --length;
        }
    }

    const T& get_front() const {
        if (!head.null()) {
            return head->data;
        }
        throw std::out_of_range("List is empty");
    }

    size_t size() const {
        return length;
    }

    void clear() {
        while (!head.null()) {
            pop_front();
        }
    }

    ~LinkedList(){
        clear();
    }

};

#endif //LINKED_LIST_HPP
