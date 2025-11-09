#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    void push(const T& item) = 0;
    T pop() = 0;
    T peek() const = 0;
    std::size_t getSize() const noexcept = 0;
};


template <typename T>
class QueueInterface {

};


template <typename T>
class DequeInterface {

};

