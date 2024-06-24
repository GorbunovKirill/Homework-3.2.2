#include <iostream>
#include <stdexcept>

class smart_array {
private:
    int* data;
    int size;
    int capacity;

    void copy_from(const smart_array& other) {
        data = new int[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

public:

    explicit smart_array(int n) : size(0), capacity(n) {
        if (capacity <= 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
        data = new int[capacity];
    }


    ~smart_array() {
        delete[] data;
    }

    smart_array(const smart_array& other) {
        copy_from(other);
    }


    smart_array& operator=(const smart_array& other) {
        if (this != &other) {
            delete[] data;
            copy_from(other);
        }
        return *this;
    }


    smart_array(smart_array&& other) noexcept : data(nullptr), size(0), capacity(0) {
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }


    smart_array& operator=(smart_array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }


    void add_element(int value) {
        if (size >= capacity) {
            capacity *= 2;
            int* new_data = new int[capacity];
            for (int i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        data[size] = value;
        size++;
    }

    int get_element(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array; 

        std::cout << arr.get_element(1) << std::endl; 
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
