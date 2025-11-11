#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>
mess
template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {}

    //Copy Constructor
    LLQ(const LLQ<T>& other) {
        list = other.getList();
    }

    //Move Constructor
    LLQ(LLQ<T>&& other) noexcept {
        list = std::move(other.getList());
    }

    //Copy Operator
    LLQ<T>& operator=(const LLQ<T>& other) {
        list = other.getList();
        return *this;
    }

    //Move Operator
    LLQ<T>& operator=(LLQ<T>&& other) noexcept {
        list = std::move(other.getList());
        return *this;
    }

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Queue Empty");
        }
        T head_value = (list.getHead())->data;
        list.removeHead();
        return head_value;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Stack Queue");
        }
        T head_value = (list.getHead())->data;
        return head_value;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    //Printers
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