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
        list = std::move(other.getLinkedList());
    }

    //Copy Assignment
    LLS& operator=(const LLS<T>& rhs) {
        list = rhs.getLinkedList();
        return *this;
    }

    //Move Assignment
    LLS& operator=(const LLS<T>&& rhs) noexcept{
        list = std::move(rhs.getLinkedList());
        return *this;
    }

    LinkedList<T>& getLinkedList() const {
        return list;
    }
    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        T head_value = *(list.getHead());
        list.removeHead();
        return head_value;
    }

    // Access
    T peek() const override {
        T head_value = *(list.getHead());
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