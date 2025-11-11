#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{
public: //remove this later
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
    size_t first_index;
    size_t last_index;

public:
    // Constructors + Big 5
    ABQ() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];

        first_index = 0;
        last_index = 0;
    }
    explicit ABQ(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];

        first_index = 0;
        last_index = 0;
    }
    ABQ(const ABQ& other) {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        first_index = other.getFirstIndex();
        last_index = other.getLastIndex();
        array_ = new T[capacity_];

        T* other_array = other.getData();
        for (int i = 0; i < curr_size_; i++) {
            array_[i] = other_array[i];
        }
    }
    ABQ& operator=(const ABQ& other) {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        first_index = other.getFirstIndex();
        last_index = other.getLastIndex();
        T* temp_array = new T[capacity_];
        delete[] array_;
        array_ = temp_array;
        T* other_data = other.getData();
        for (int i = 0; i < curr_size_; i++) {
            array_[i] = other_data[i];
        }
        return *this;
    }
    ABQ(ABQ&& other) noexcept {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = other.getData();
        first_index = other.getFirstIndex();
        last_index = other.getLastIndex();
        other.resetData(false);
    }
    ABQ& operator=(ABQ&& other) noexcept {
        resetData(true);
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = other.getData();
        first_index = other.getFirstIndex();
        last_index = other.getLastIndex();
        other.resetData(false);
        return *this;
    }
    ~ABQ() noexcept {
        resetData(true);
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }
    [[nodiscard]] getFirstIndex() const noexcept {
        return first_index;
    }
    [[nodiscard]] getLastIndex() const noexcept {
        return last_index;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (first_index == 0 && last_index < capacity_ - 1) {
            if (curr_size_ == 0) {
                array_[last_index] = data;
            } else {
                array_[last_index + 1] = data;
                last_index++;
            }
            curr_size_++;
            return;
        } else if (first_index != 0 && curr_size_ < capacity_) {
            last_index = (last_index + 1) % capacity_;
            array_[last_index] = data; //wraps back up if the indices overflow
            curr_size_ ++;
            return;
        } else if (curr_size_ >= capacity_) {
            capacity_ *= scale_factor_;
            T* temp_data = new T[capacity_];

            for (unsigned int i = first_index; i < curr_size_ + first_index; i++) { //Copies data in order in the new array
                temp_data[i - first_index] = array_[i % curr_size_];
            }

            array_ = temp_data;

            first_index = 0;
            last_index = curr_size_ - 1;
            array_[last_index + 1] = data;
            last_index++;
            curr_size_++;
        }
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Queue Empty");
        }
        T element = array_[first_index];
        return element;
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Queue Empty");
        }
        T element = array_[first_index];
        first_index = (first_index + 1) % capacity_;
        //std::cout << first_index << std::endl;
        curr_size_ --;

        if (curr_size_ < capacity_ / scale_factor_) {
            capacity_ /= scale_factor_;
            T* temp_data = new T[capacity_];

            for (unsigned int i = first_index; i < curr_size_ + first_index; i++) { //Copies data in order in the new array
                temp_data[i - first_index] = array_[i % (curr_size_ + first_index)];
            }

            array_ = temp_data;
            first_index = 0;
            last_index = curr_size_ - 1;
        }
        return element;
    }

    void resetData(bool delete_data) {
        if (delete_data) {
            delete[] array_;
        }
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
        first_index = 0;
        last_index = 0;
    }

    void PrintForward() {
        if (curr_size_ == 0) {return;}
        for (int i = first_index; i < first_index + curr_size_; i++) {
            std::cout << array_[i % (curr_size_)] << " ";
        }
        std::cout << std::endl;
    }

    void PrintReverse() {

        if (first_index <= last_index && curr_size_ != 0) {
            for (int i = last_index; i >= last_index; i++) {
                std::cout << array_[i] << " ";
            }
        } else {
            for (int i = last_index; i >= 0; i--) {
                std::cout << array_[i] << " ";
            }
            for (int i = curr_size_ - 1; i >= first_index; i--) {
                std::cout << array_[i] << " ";
            }
        }

        std::cout << std::endl;
    }

    void printArray() {
        for (int i = 0; i < capacity_; i++) {
            std::cout << array_[i] << " ";
        }
        std::cout << std::endl;
    }

    void unused_indices(T val) {
        if (first_index <= last_index) {
            for (int i = 0; i < first_index; i++) {
                array_[i] = val;
            }
            for (int i = last_index + 1; i < capacity_; i++) {
                array_[i] = val;
            }
        } else {
            for (int i = last_index + 1; i < first_index; i++) {
                array_[i] = val;
            }
        } 
        
        if (curr_size_ == 0) {
            for (int i = 0; i < capacity_; i++) {
                array_[i] = val;
            }
        }
    }

};
