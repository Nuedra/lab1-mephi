#include <iostream>
#include <sstream>

#include "smrtptr.hpp"
#include "smrtptr_test.hpp"

int main() {
    long size_test = 10000000;
    std::cout << functional_SmrtPtr_tests();
    std::cout << functional_LinkedList_tests();
    std::cout << run_load_tests<SmrtPtr>(size_test);

}