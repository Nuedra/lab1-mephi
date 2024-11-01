#include <iostream>
#include "smrtptr.hpp"


int main() {
    // Создаем SmrtPtr для int
    SmrtPtr<int> ptr1(new int(42));
    std::cout << "Initial use count (ptr1): " << ptr1.use_count() << std::endl;
    std::cout << "Value pointed by ptr1: " << *ptr1 << std::endl;

    // Копируем указатель
    {
        SmrtPtr<int> ptr2 = ptr1;  // Новый указатель указывает на тот же int
        std::cout << "Use count after copying to ptr2: " << ptr1.use_count() << std::endl;
        std::cout << "Value pointed by ptr2: " << *ptr2 << std::endl;
    }  // ptr2 выходит из области видимости

    std::cout << "Use count after ptr2 is destroyed: " << ptr1.use_count() << std::endl;


    return 0;
}



#pragma clang diagnostic pop