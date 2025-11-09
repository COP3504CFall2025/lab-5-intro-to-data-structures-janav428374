#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>
#include <utility>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {}

    //Copy Constructor
    LLS(const LLS<T>& other) {
        list = other.getLinkedList();
    }

    //Move Constructor
    LLS(const LLS<T>&& other) noexcept{
        list = other.getLinkedList();
    }

    //Copy Assignment
    LLS& operator=(const LLS<T>& rhs) {
        list = rhs.getLinkedList();
        return *this;
    }

    //Move Assignment
    LLS& operator=(const LLS<T>&& rhs) noexcept{
        list = (rhs.getLinkedList());
        return *this;
    }

    LinkedList<T> getLinkedList() {
        return list;
    }
    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Stack Empty");
        }
        T head_value = (list.getHead())->data;
        list.removeHead();
        return head_value;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Stack Empty");
        }
        T head_value = (list.getHead())->data;
        return head_value;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void PrintForward() {
        list.printForward();
    }

    void PrintReverse() {
        list.printNodeF();
    }
};