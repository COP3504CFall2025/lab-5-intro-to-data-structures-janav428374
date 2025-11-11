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

public:
    // Constructors + Big 5
    ABQ() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    explicit ABQ(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    ABQ(const ABQ& other) {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = new T[capacity_];

        T* other_data = other.getData();

        for (int i = 0; i < curr_size_; i++) {
            array_[i] = other_data[i];
        }
    }

    ABQ& operator=(const ABQ& other) {
        if (this == *other) {return *this;}

        T* temp_data = new T[other.getMaxCapacity()];
        delete[] array_;

        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = temp_data;
        T* other_data = other.getData();
        for (int i = 0; i < curr_size_; i++) {
            array_[i] = other_data[i];
        }
    }
    
    ABQ(ABQ&& other) noexcept {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = other.getData();
        other.resetData(false);
    }

    ABQ& operator=(ABQ&& other) noexcept {
        resetData(true);
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = other.getData();
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

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ >= capacity_) {
            capacity_ *= scale_factor_;
            T* temp_data = new T[capacity_];

            for (unsigned int i = 0; i < curr_size_; i++) {
                temp_data[i] = array_[i];
            }
            delete[] array_;
            array_ = temp_data;
        }

        // for (int i = curr_size_; i > 0; i--) {
        //     array_[i] = array_[i - 1];
        // }
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Queue Empty");
        }

        return array_[0];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Queue Empty");
        }

        T front_element = array_[0];
        curr_size_ --;

        if (curr_size_ < capacity_ / scale_factor_) {
            capacity_ /= scale_factor_;
            T* temp_data = new T[capacity_];

            for (unsigned int i = 0; i < curr_size_; i++) {
                temp_data[i] = array_[i + 1];
            }
            delete[] array_;
            array_ = temp_data;
        } else {
            for (unsigned int i = 0; i < curr_size_; i++) {
                array_[i] = array_[i + 1];
            }
        }
        
        return front_element;
    }


    void PrintForward() {
        for (int i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << " ";
        }
        std::cout << std::endl;
    }

    void PrintReverse() {
        for (int i = curr_size_ - 1; i >= 0; i--) {
            std::cout << array_[i] << " ";
        }
        std::cout << std::endl;
    }    

    void resetData(bool delete_data) {
        if (delete_data) {
            delete[] array_;
        }
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

};
