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
    explicit smrt_ptr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    smrt_ptr(const smrt_ptr<T> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    // Шаблонный конструктор копирования для совместимых типов
    template <typename U>
    smrt_ptr(const smrt_ptr<U>& other) : ptr(static_cast<T*>(other.ptr)), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    // Деструктор
    ~smrt_ptr() {
        release();
    }

    smrt_ptr<T>& operator=(const smrt_ptr<T> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }

        return *this;
    }

    // Шаблонный оператор присваивания для совместимых типов
    template <typename U>
    smrt_ptr<T>& operator=(const smrt_ptr<U>& other) {
        if (this != static_cast<const smrt_ptr<T>*>(&other)) {
            release();
            ptr = static_cast<T*>(other.ptr);
            ref_count = other.ref_count;
            ++(*ref_count);
        }

        return *this;
    }

    const T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error: null pointer dereference");
    }

    const T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error: null pointer access");
    }


    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }

    [[nodiscard]] bool null() const {
        return ptr == nullptr;
    }


    template <typename U>
    friend class smrt_ptr;
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
    explicit smrt_ptr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    smrt_ptr(const smrt_ptr<T[]> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    template <typename U>
    smrt_ptr(const smrt_ptr<U[]>& other) : ptr(dynamic_cast<T*>(other.ptr)), ref_count(other.ref_count) {
        if (!ptr) {
            throw std::bad_cast();
        }

        ++(*ref_count);
    }

    ~smrt_ptr() {
        release();
    }

    smrt_ptr<T[]>& operator=(const smrt_ptr<T[]> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }

        return *this;
    }

    // Шаблонный оператор присваивания для подтипов
    template <typename U>
    smrt_ptr<T[]>& operator=(const smrt_ptr<U[]>& other) {
        T* temp_ptr = dynamic_cast<T*>(other.ptr);  // Проверка приведения типа

        if (!temp_ptr) {
            throw std::bad_cast();
        }

        release();
        ptr = temp_ptr;
        ref_count = other.ref_count;
        ++(*ref_count);

        return *this;
    }

    const T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error: null pointer dereference!");
    }

    const T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error: null pointer access");
    }

    const T& operator[](size_t index) const {
        if (ptr != nullptr) return ptr[index];
        throw std::logic_error("Error: null pointer dereference");
    }


    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }

    template <typename U>
    friend class smrt_ptr;
};

#endif //LAB1_SMRT_PTR_HPP
