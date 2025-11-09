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

};


template <typename T>
class DequeInterface {

};

