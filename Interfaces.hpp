#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    void virtual push(const T& item) = 0;
    T virtual pop() = 0;
    T virtual peek() const = 0;
    std::size_t virtual getSize() const noexcept = 0;
};


template <typename T>
class QueueInterface {
    void virtual enqueue(const T& item) = 0;
    T virtual dequeue() = 0;
    T virtual peek() const = 0;
    std::size_t virtual getSize() const noexcept = 0;
};


template <typename T>
class DequeInterface {
    void virtual pushFront(const T& item) = 0;
    void virtual pushBack(const T& item) = 0;
    T virtual popFront() = 0;
    T virtual popBack() = 0;
    const T& virtual front() const = 0;
    const T& virtual back() const = 0;
    std::size_t virtual getSize() const noexcept = 0;
};

