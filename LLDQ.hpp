#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {}

        //Copy Constructor
    LLDQ(const LLDQ<T>& other) {
        list = other.getList();
    }

    //Move Constructor
    LLDQ(LLDQ<T>&& other) noexcept {
        list = std::move(other.getList());
    }

    //Copy Operator
    LLDQ<T>& operator=(const LLDQ<T>& other) {
        list = other.getList();
        return *this;
    }

    //Move Operator
    LLDQ<T>& operator=(LLDQ<T>&& other) noexcept {
        list = std::move(other.getList());
        return *this;
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Empty Double Queue");
        }
        T head_value = (list.getHead())->data;
        list.removeHead();
        return head_value;
    }

    T popBack() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Empty Double Queue");
        }
        T tail_value = (list.getTail())->data;
        list.removeTail();
        return tail_value;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Stack Double Queue");
        }
        return (list.getHead())->data;
    }
    const T& back() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Stack Double Queue");
        }
        return (list.getTail())->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void PrintForward() {
        list.printForward();
    }

    void PrintReverse() {
        list.printNodeF();
    }

private:
    LinkedList<T> getList() const{
        return list;
    }

    LinkedList<T>& getList() {
        return list;
    }

};






