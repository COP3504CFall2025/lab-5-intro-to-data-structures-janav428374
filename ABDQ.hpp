#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

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
            T* temp_data = new T[capacity_];
            
            int index = 0;
            for (unsigned int i = front_; i < front_ + size_; i++) {
                temp_data[index] = data_[mod(i, capacity_ / SCALE_FACTOR)];
            }
            delete[] data_;
            data_ = temp_data;

            front_ = 0;
            back_ = size_ - 1;
        } 

        back_ = mod(back_ + 1, capacity_);
        data_[back_] = item; 
        size_++;
    }

    void pushBack(const T& item) override {
        if (size_ >= capacity_) {
            ensureCapacity();
            T* temp_data = new T[capacity_];
            
            int index = 1;
            for (unsigned int i = front_; i < front_ + size_; i++) {
                temp_data[index] = data_[mod(i, capacity_ / SCALE_FACTOR)];
            }
            delete[] data_;
            data_ = temp_data;
            front_ = 1;
            back_ = size_;
        } 
        
        front_ = mod(static_cast<int>(front_ - 1), capacity_); 
        data_[front_] = item;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Queue");
        }
        T returnValue = data_[front_];
        front_ = mod(front_ + 1, capacity_);
        ShrinkIfNeeded();
        return returnValue;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Queue");
        }
        T returnValue = data_[back_];
        back_ = mod(back_ - 1, capacity_);
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
    }

    void ShrinkIfNeeded() {
        if (size_ < capacity_ / SCALE_FACTOR) {
            capacity_ /= SCALE_FACTOR;
            T* temp_data = new T[capacity_];
            
            int index = 0;
            for (unsigned int i = front_; i < front_ + size_; i++) {
                temp_data[index] = data_[mod(i, capacity_ / SCALE_FACTOR)];
            }
            delete[] data_;
            data_ = temp_data;
            front_ =  0;
            back_ = size_ - 1;
        } 
    }

};
