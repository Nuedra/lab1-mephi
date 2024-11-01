#include <iostream>
#include "smrtptr.hpp"


int main() {
    // Создаем SmrtPtr для int
    SmrtPtr<int> ptr1(nullptr);
    int* ptr2 = nullptr;
    int zalupa = *ptr1.operator*();

}



#pragma clang diagnostic pop