#include <iostream>
#include "smrtptr.hpp"


int main() {
    // Создаем SmrtPtr для int
    const SmrtPtr<int> ptr1(new int (0));

    const int m = *ptr1;
    std::cout << m;
}

