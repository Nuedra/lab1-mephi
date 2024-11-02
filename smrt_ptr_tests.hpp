#ifndef SMRTPTR_TEST_h
#define SMRTPTR_TEST_h
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>
#include <exception>

void log_error(const std::string& test_name, const std::string& message);

// Вспомогательная функция для выполнения теста с перехватом исключений
template <typename Func>
int run_test(const std::string& test_name, Func test_func, bool silent = false);

int functional_smrt_ptr_tests();
int functional_linked_list_tests();


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


// Базовый и производный классы для тестов
class C2 {
public:
    virtual ~C2() = default;
    virtual int getValue() const { return 10; }
};

class C1 : public C2 {
public:
    int getValue() const override { return 20; }
};

// Для Графиков

std::vector<std::pair<int, long long>> loadUnqPtrTests();
std::vector<std::pair<int, long long>> loadShrdPtrTests();
std::vector<std::pair<int, long long>> loadStdShrdPtrTests();
std::vector<std::pair<int, long long>> loadStdUnqPtrTests();

#endif

