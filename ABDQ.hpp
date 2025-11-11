#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 1;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }

    ABDQ(const ABDQ& other) {
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        front_ = other.getFront();
        back_ = other.getBack();
        
        T* temp_data = new T[capacity_];
        //delet data if not constructor
        data_ = temp_data;
        T* other_data = other.data();

        for (unsigned int i = 0; i < size_; i++) {
            data_[i] = other_data[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        front_ = other.getFront();
        back_ = other.getBack();
        //delete data_ if not constructor
        data_ = other.data();

        other.reset(false);
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {return *this;}
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        front_ = other.getFront();
        back_ = other.getBack();
        
        T* temp_data = new T[capacity_];
        delete[] data_;
        data_ = temp_data;
        T* other_data = other.data();

        for (unsigned int i = 0; i < size_; i++) {
            data_[i] = other_data[i];
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {return *this;}
        capacity_ = other.getCapacity();
        size_ = other.getSize();
        front_ = other.getFront();
        back_ = other.getBack();
        delete[] data_;
        data_ = other.data();

        other.reset(false);
        return *this;
    }
    ~ABDQ() {
        delete[] data_;
    };

    // Insertion
    void pushFront(const T& item) override {
        if (size_ >= capacity_) {
            ensureCapacity();
        } 

        if (size_ != 0) {
            front_ = mod(static_cast<int>(front_ - 1), capacity_); 
        }
        
        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override {
        if (size_ >= capacity_) {
            ensureCapacity();
        } 
        
        //back_ = mod(back_ + 1, capacity_);
        if (size_ != 0) {
            back_ = mod(back_ + 1, capacity_);
        }
        data_[back_] = item; 
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Queue");
        }
        T returnValue = data_[front_];

        if (front_ != back_) {
            front_ = mod(front_ + 1, capacity_);
            size_--;
        } else {
            size_ = 0;
            front_ = 0;
            back_ = 0;
        }
        ShrinkIfNeeded();
        return returnValue;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Queue");
        }
        T returnValue = data_[back_];

        if (front_ != back_) {
            back_ = mod(back_ - 1, capacity_);
            size_--;
        } else {
            size_ = 0;
            front_ = 0;
            back_ = 0;
        }
        
        ShrinkIfNeeded();
        return returnValue;
    }

    // Access
    const T& front() const override {
        return data_[front_];
    }
    const T& back() const override {
        return data_[back_];
    }

    T* data() const {
        return data_;
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    std::size_t getCapacity() const noexcept {
        return capacity_;
    }

    std::size_t getFront() const noexcept{
        return front_;
    }

    std::size_t getBack() const noexcept{
        return back_;
    }

    void reset(bool deleteData) {
        if (deleteData && data_ != nullptr) {
            delete[] data_;
        }
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    int mod(int num, int mod) {
        int result = num % mod;
        if (result < 0) {result += mod;}
        return result;
    }

    void ensureCapacity() {
        capacity_ *= SCALE_FACTOR;
        T* temp_data = new T[capacity_];
            
        int index = 0;
        for (unsigned int i = front_; i < front_ + size_; i++) {
            temp_data[index] = data_[mod(i, capacity_ / SCALE_FACTOR)];
            index++;
        } 
        
        
        delete[] data_;
        data_ = temp_data;
        front_ = 0;
        back_ = size_ - 1;
    }

    void ShrinkIfNeeded() {
        if (size_ < capacity_ / SCALE_FACTOR) {
            capacity_ /= SCALE_FACTOR;
            T* temp_data = new T[capacity_];
            
            int index = 0;
            if (front_ != back_) {
                for (unsigned int i = front_; i < front_ + size_; i++) {
                    temp_data[index] = data_[mod(i, capacity_ / SCALE_FACTOR)];
                }
            } else {
                //std::cout << "here" << std::endl;
                temp_data[0] = data_[front_];
            }

            delete[] data_;
            data_ = temp_data;
            front_ =  0;
            if (size_ == 0) {
                back_ = 0;
            } else {
                back_ = size_ - 1;
            }
            
        } 
    }

    void unused_indices(T val) {
        size_t first_index = front_;
        size_t last_index = back_;
        if (first_index <= last_index) {
            for (int i = 0; i < first_index; i++) {
                data_[i] = val;
            }
            for (int i = last_index + 1; i < capacity_; i++) {
                data_[i] = val;
            }
        } else {
            for (int i = last_index + 1; i < first_index; i++) {
                data_[i] = val;
            }
        } 
        
        if (size_ == 0) {
            for (int i = 0; i < capacity_; i++) {
                data_[i] = val;
            }
        }
    }

    void printArray() {
        for (int i = 0; i < capacity_; i++) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }

    void PrintE(T i) {
        std::cout << "Front: " << front_ << std::endl;
        std::cout << "Back: " << back_ << std::endl;
        unused_indices(i);
        printArray();

    }



};
