#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class CircularBuffer 
{
private:
    std::vector<T> elements; // Buffer to hold elements
    size_t capacity; // Maximum capacity of the buffer
    size_t head; // Index of the head (oldest element)
    size_t tail; // Index of the tail (next available slot)
    size_t size; // Current number of elements in the buffer

public:
    // Constructor to initialize the circular buffer with a given capacity
    CircularBuffer(size_t capacity) : elements(capacity), capacity(capacity), head(0), tail(0), size(0) {}

    // Check if the buffer is empty
    const bool isEmpty()
    {
        return size == 0;
    }

    // Check if the buffer is full
    const bool isFull() 
    {
        return size == capacity;
    }

    // Get the maximum capacity of the buffer
    const size_t getCapacity()
    {
        return capacity;
    }

    // Get the current number of elements in the buffer
    const size_t getSize()
    {
        return size;
    }

    // Clear the buffer
    void clear() 
    {
        head = tail = size = 0;
    }

    // Add an element to the buffer
    void push(const T& element)
    {
        if (isFull()) 
        {
            // Buffer is full, overwrite the oldest element
            tail = (tail + 1) % capacity;
        }
        else 
        {
            size++;
        }
        elements[head] = element;
        head = (head + 1) % capacity;
    }

    // Remove and return the oldest element from the buffer
    T pop() 
    {
        if (isEmpty()) 
        {
            throw std::out_of_range("Buffer is empty");
        }
        T element = elements[tail];
        tail = (tail + 1) % capacity;
        size--;
        return element;
    }
};
