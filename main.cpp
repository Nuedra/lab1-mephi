#include <iostream>
#include <sstream>

#include "smrtptr.hpp"
#include "smrtptr_tests.hpp"

int main() {
    long size_test = 1000000;
    std::cout << functional_SmrtPtr_tests() << std::endl;
    std::cout << functional_LinkedList_tests() << std::endl;;
    std::cout << run_load_tests<SmrtPtr>(size_test) << std::endl;
    std::cout << run_load_tests<std::unique_ptr>(size_test) << std::endl;
    std::cout << run_load_tests<std::shared_ptr>(size_test) << std::endl;

}