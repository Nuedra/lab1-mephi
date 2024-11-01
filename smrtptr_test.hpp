#ifndef SMRTPTR_TEST_h
#define SMRTPTR_TEST_h
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>
#include <exception>


int functional_SmrtPtr_tests();
int functional_LinkedList_tests();

template <template <typename> class PtrType>
long measure_allocation_time(long& num_allocations) {
    try {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<PtrType<int>> pointers;
        pointers.reserve(num_allocations);

        for (int i = 0; i < num_allocations; ++i) {
            pointers.push_back(PtrType<int>(new int(i)));
        }

        auto end = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    catch (const std::exception &e) {
        std::cerr << "Failed with exception: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Failed with unknown exception\n";
    }

    return -1;
}

template <template <typename> class PtrType>
long run_load_tests(long& num_allocations) {
    long duration = measure_allocation_time<PtrType>(num_allocations);

    if (duration != -1) {
        std::cout << "Load Test: Time: " << duration << " ms\n";
    }

    return duration;
}

#endif

