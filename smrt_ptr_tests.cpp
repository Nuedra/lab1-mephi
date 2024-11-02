#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <exception>
#include "smrt_ptr.hpp"
#include "smrt_ptr_tests.hpp"
#include <cassert>
#include <memory>
#include <utility>


void log_error(const std::string& test_name, const std::string& message) {
    std::cerr << "Test failed: " << test_name << std::endl;
}

template <typename Func>
int run_test(const std::string& test_name, Func test_func, const bool silent) {
    int local_failed_tests = 0;

    try {
        test_func();
    }
    catch (const std::exception& e) {
        if (!silent) {
            log_error(test_name, e.what());
            ++local_failed_tests;
        }
    }
    catch (...) {
        if (!silent) {
            log_error(test_name, "Unknown exception");
            ++local_failed_tests;
        }
    }

    return local_failed_tests;
}

int functional_smrt_ptr_tests() {
    int failed_tests = 0;

    failed_tests += run_test("Test 1", []() {
        smrt_ptr<int> p1(new int(10));
        assert(*p1 == 10);
        assert(p1.use_count() == 1);

        smrt_ptr<std::string> p2(new std::string("Hello"));
        assert(*p2 == "Hello");
        assert(p2.use_count() == 1);

        smrt_ptr<std::vector<int>> p3(new std::vector<int>{1, 2, 3});
        assert((*p3)[0] == 1);
        assert((*p3)[1] == 2);
        assert((*p3)[2] == 3);
        assert(p3.use_count() == 1);
    });

    failed_tests += run_test("Test 2", []() {
        smrt_ptr<int> p1(new int(20));
        smrt_ptr<int> p2(p1);
        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 20);

        smrt_ptr<std::string> p3(new std::string("World"));
        smrt_ptr<std::string> p4(p3);
        assert(p3.use_count() == 2);
        assert(p4.use_count() == 2);
        assert(*p4 == "World");

        smrt_ptr<std::vector<int>> p5(new std::vector<int>{4, 5, 6});
        smrt_ptr<std::vector<int>> p6(p5);
        assert(p5.use_count() == 2);
        assert(p6.use_count() == 2);
        assert((*p6)[0] == 4);
        assert((*p6)[1] == 5);
        assert((*p6)[2] == 6);
    });

    failed_tests += run_test("Test 3", []() {
        smrt_ptr<int> p1(new int(30));
        smrt_ptr<int> p2;
        p2 = p1;

        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 30);
    });

    failed_tests += run_test("Test 4", []() {
        smrt_ptr<int> p1(new int(40));
        p1 = p1;

        assert(p1.use_count() == 1);
        assert(*p1 == 40);
    });

    failed_tests += run_test("Test 5", []() {
        struct TestStruct {
            int val;
            TestStruct(int v) : val(v) {}
        };

        smrt_ptr<TestStruct> p1(new TestStruct(50));
        assert(p1->val == 50);
    });

    failed_tests += run_test("Test 6", []() {
        smrt_ptr<int[]> p1(new int[3]{1, 2, 3});

        assert(p1[0] == 1);
        assert(p1[1] == 2);
        assert(p1[2] == 3);
    });

    failed_tests += run_test("Test 7", []() {
        smrt_ptr<int> p1(nullptr);
        *p1;  // Ожидается, что бросит исключение

        assert(false);  // Этот assert не должен быть достигнут
    }, true);


    failed_tests += run_test("Test 8", []() {
        smrt_ptr<int[]> p1(nullptr);
        p1[0];  // Ожидается, что бросит исключение
        assert(false);  // Этот assert не должен быть достигнут

    }, true);


    failed_tests += run_test("Test 9", []() {
        smrt_ptr<C1> derivedPtr(new C1());
        smrt_ptr<C2> basePtr = derivedPtr;

        assert(basePtr->getValue() == 20);
        assert(derivedPtr.use_count() == 2);
    });


    failed_tests += run_test("Test 10", []() {
        smrt_ptr<C1> derivedPtr1(new C1());
        smrt_ptr<C2> basePtr1 = derivedPtr1;

        assert(basePtr1.use_count() == 2);

        smrt_ptr<C2> basePtr2 = basePtr1;
        assert(basePtr1.use_count() == 3);
    });

    failed_tests += run_test("Test 11", []() {
        smrt_ptr<C1[]> derivedPtr(new C1[3]);
        smrt_ptr<C2[]> basePtr = derivedPtr;


        assert(basePtr[0].getValue() == 20);
        assert(derivedPtr.use_count() == 2);
    });

    return failed_tests;
}

// Заполнения векторов для отрисовки графиков
// Функция для генерации размеров тестов
std::vector<int> generate_test_sizes(int start_size, int end_size, int step_size) {
    std::vector<int> test_sizes;
    for (int size = start_size; size <= end_size; size += step_size) {
        test_sizes.push_back(size);
    }
    return test_sizes;
}

// Функция заполнения для smrt_ptr
std::vector<std::pair<long, long>> load_smrt_ptr_tests(int start_size, int end_size, int step_size) {
    std::vector<std::pair<long, long>> results;
    std::vector<int> test_sizes = generate_test_sizes(start_size, end_size, step_size);

    for (int test_size : test_sizes) {
        auto start = std::chrono::high_resolution_clock::now();

            std::vector<smrt_ptr<int>> pointers;
            pointers.reserve(test_size);
            for (int i = 0; i < test_size; ++i) {
                pointers.push_back(smrt_ptr<int>(new int(i)));
            }

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
        results.emplace_back(test_size, duration);
    }

    return results;
}

// Функция заполнения для unique_ptr
std::vector<std::pair<long, long>> load_unique_ptr_tests(int start_size, int end_size, int step_size) {
    std::vector<std::pair<long, long>> results;
    std::vector<int> test_sizes = generate_test_sizes(start_size, end_size, step_size);

    for (int test_size : test_sizes) {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::unique_ptr<int>> pointers;
        pointers.reserve(test_size);
        for (int i = 0; i < test_size; ++i) {
            pointers.push_back(std::unique_ptr<int>(new int(i)));
        }

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
        results.emplace_back(test_size, duration);
    }

    return results;
}

// Функция заполнения для shared_ptr
std::vector<std::pair<long, long>> load_shrd_ptr_tests(int start_size, int end_size, int step_size) {
    std::vector<std::pair<long, long>> results;
    std::vector<int> test_sizes = generate_test_sizes(start_size, end_size, step_size);

    for (int test_size : test_sizes) {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::shared_ptr<int>> pointers;
        pointers.reserve(test_size);
        for (int i = 0; i < test_size; ++i) {
            pointers.push_back(std::shared_ptr<int>(new int(i)));
        }

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
        results.emplace_back(test_size, duration);
    }

    return results;
}








