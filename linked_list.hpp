#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "smrt_ptr.hpp"


template<typename T>
struct Node {
    T data;
    smrt_ptr<Node<T>> next;

    explicit Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class linked_list {
private:
    smrt_ptr<Node<T>> head;
    size_t length;

public:
    linked_list() : head(nullptr), length(0) {}

    void push_front(const T& value) {
        smrt_ptr<Node<T>> newNode(new Node<T>(value));
        newNode->next = head;
        head = std::move(newNode);
        ++length;
    }

    [[nodiscard]] bool null() const {
        return head.null();
    }

    void pop_front() {
        if (!head.null()) {
            smrt_ptr<Node<T>> oldHead = std::move(head);
            head = std::move(oldHead->next);
            --length;
        }
    }

    const T& get_front() const {
        if (!head.null()) {
            return head->data;
        }
        throw std::out_of_range("Empty");
    }

    [[nodiscard]] size_t size() const {
        return length;
    }

    void clear() {
        while (!head.null()) {
            pop_front();
        }
    }

    ~linked_list(){
        clear();
    }

};

#endif //LINKED_LIST_HPP
