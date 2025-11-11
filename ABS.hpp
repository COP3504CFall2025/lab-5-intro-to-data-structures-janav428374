 #pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    explicit ABS(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    ABS(const ABS& other) {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = new T[capacity_];

        T* other_array = other.getData();
        for (int i = 0; i < curr_size_; i++) {
            array_[i] = other_array[i];
        }
    }

    ABS& operator=(const ABS& other) {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        T* temp_array = new T[capacity_];
        delete[] array_;
        array_ = temp_array;
        T* other_data = other.getData();
        for (int i = 0; i < curr_size_; i++) {
            array_[i] = other_data[i];
        }
        return *this;
        
    }

    ABS(ABS&& other) noexcept {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = other.getData();
        other.resetData(false);
    }

    ABS& operator=(ABS&& other) noexcept {
        resetData(true);
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = other.getData();
        other.resetData(false);
        return *this;
    }

    ~ABS() noexcept {
        resetData(true);
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ >= capacity_) {
            capacity_ *= 2;
            T* temp_data = new T[capacity_];

            for (int i = 0; i < curr_size_; i++) {
                temp_data[i] = array_[i];
            }
            delete[] array_;
            array_ = temp_data;
        }

        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Stack Empty");
        }
        T element = array_[curr_size_ - 1];
        return element;
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Stack Empty");
        }
        curr_size_ --;
        T element = array_[curr_size_];
        return element;
    }

    void resetData(bool delete_data) {
        if (delete_data) {
            delete[] array_;
        }
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }
private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
