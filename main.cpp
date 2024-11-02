#include <iostream>
#include <sstream>
#include <memory>

#include "smrt_ptr.hpp"
#include "smrt_ptr_tests.hpp"

int main() {

    long size_test = 1000000;
    std::cout << functional_smrt_ptr_tests() << std::endl;
    std::cout << functional_linked_list_tests() << std::endl;
    std::cout << measure_allocation_time<smrt_ptr>(size_test) << std::endl;
//    std::cout << measure_allocation_time<std::unique_ptr>(size_test) << std::endl;
    std::cout << measure_allocation_time<std::shared_ptr>(size_test) << std::endl;

}