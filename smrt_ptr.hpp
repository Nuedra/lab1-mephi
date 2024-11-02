#ifndef LAB1_SMRT_PTR_HPP
#define LAB1_SMRT_PTR_HPP

#include <stdexcept>

template <typename T>
class smrt_ptr {
private:
    T* ptr;                  // Указатель на управляемый объект
    size_t* ref_count;       // Указатель на счетчик ссылок

    void release() const{
        if (--(*ref_count) == 0) {  // Уменьшаем счетчик, удаляем, если он обнуляется
            delete ptr;
            delete ref_count;
        }
    }

public:
    // Конструктор по умолчанию
    explicit smrt_ptr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    // Копирующий конструктор
    smrt_ptr(const smrt_ptr<T> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    // Деструктор
    ~smrt_ptr() {
        release();
    }

    // Оператор присваивания для идентичных типов
    smrt_ptr<T>& operator=(const smrt_ptr<T> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error: null pointer dereference");
    }

    T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error: null pointer access");
    }


    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }

    bool null() const {
        return ptr == nullptr;
    }


};


template <typename T>
class smrt_ptr<T[]> {
private:
    T* ptr;
    size_t* ref_count;

    void release() const {
        if (--(*ref_count) == 0) {
            delete[] ptr;
            delete[] ref_count;
        }
    }

public:
    // Конструктор по умолчанию
    explicit smrt_ptr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    // Копирующий конструктор
    smrt_ptr(const smrt_ptr<T[]> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }


    ~smrt_ptr() {
        release();
    }

    // Оператор присваивания
    smrt_ptr<T[]>& operator=(const smrt_ptr<T[]> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error: null pointer dereference!");
    }

    T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error: null pointer access");
    }

    T& operator[](size_t index) const {
        if (ptr != nullptr) return ptr[index];
        throw std::logic_error("Error");
    }


    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }
};

#endif //LAB1_SMRT_PTR_HPP
