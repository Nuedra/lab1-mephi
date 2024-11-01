#ifndef LAB1_SMRTPTR_HPP
#define LAB1_SMRTPTR_HPP

#include <stdexcept>


template <typename T>
class SmrtPtr {
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
    explicit SmrtPtr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    // Копирующий конструктор
    SmrtPtr(const SmrtPtr<T> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);      // Увеличиваем счетчик ссылок
    }

    // Деструктор
    ~SmrtPtr() {
        release();
    }

    // Оператор присваивания
    SmrtPtr<T>& operator=(const SmrtPtr<T> &other) {
        if (this != &other) {  // Проверка на само присваивание
            release();         // Освобождение текущего объекта
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);    // Увеличиваем счетчик ссылок
        }
        return *this;
    }

    const T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error!");
    }

    const T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error!");
    }

    // Получение текущего значения счетчика ссылок
    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }
};


template <typename T>
class SmrtPtr<T[]> {
private:
    T* ptr;                  // Указатель на управляемый объект
    size_t* ref_count;       // Указатель на счетчик ссылок

    void release() const {
        if (--(*ref_count) == 0) {  // Уменьшаем счетчик, удаляем, если он обнуляется
            delete ptr;
            delete[] ref_count;
        }
    }

public:
    // Конструктор по умолчанию
    explicit SmrtPtr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    // Копирующий конструктор
    SmrtPtr(const SmrtPtr<T[]> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);      // Увеличиваем счетчик ссылок
    }

    // Деструктор
    ~SmrtPtr() {
        release();
    }

    // Оператор присваивания
    SmrtPtr<T[]>& operator=(const SmrtPtr<T[]> &other) {
        if (this != &other) {  // Проверка на самоприсваивание
            release();         // Освобождение текущего объекта
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);    // Увеличиваем счетчик ссылок
        }
        return *this;
    }

    const T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error!");
    }

    const T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error!");
    }

    const T& operator[](size_t index) const {
        return ptr[index];
    }

    // Получение текущего значения счетчика ссылок
    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }
};


#endif //LAB1_SMRTPTR_HPP
