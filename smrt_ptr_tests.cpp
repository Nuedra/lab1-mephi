#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <exception>
#include "smrt_ptr.hpp"
#include "smrt_ptr_tests.hpp"
#include "linked_list.hpp"
#include <cassert>


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

    failed_tests += run_test("Test 1: Constructor and Dereference", []() {
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

    failed_tests += run_test("Test 2: Copy Constructor", []() {
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

    failed_tests += run_test("Test 3: Assignment Operator", []() {
        smrt_ptr<int> p1(new int(30));
        smrt_ptr<int> p2;
        p2 = p1;

        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 30);
    });

    failed_tests += run_test("Test 4: Self-assignment Handling", []() {
        smrt_ptr<int> p1(new int(40));
        p1 = p1;

        assert(p1.use_count() == 1);
        assert(*p1 == 40);
    });

    failed_tests += run_test("Test 5: Arrow Operator", []() {
        struct TestStruct {
            int val;
            TestStruct(int v) : val(v) {}
        };

        smrt_ptr<TestStruct> p1(new TestStruct(50));
        assert(p1->val == 50);
    });

    failed_tests += run_test("Test 6: Array Access for smrt_ptr<T[]>", []() {
        smrt_ptr<int[]> p1(new int[3]{1, 2, 3});

        assert(p1[0] == 1);
        assert(p1[1] == 2);
        assert(p1[2] == 3);
    });

    failed_tests += run_test("Test 7: Null Dereference Exception", []() {
        smrt_ptr<int> p1(nullptr);
        *p1;  // Ожидается, что бросит исключение

        assert(false);  // Этот assert не должен быть достигнут
    }, true);


    failed_tests += run_test("Test 8: Null Array Access Exception", []() {
        smrt_ptr<int[]> p1(nullptr);
        p1[0];  // Ожидается, что бросит исключение
        assert(false);  // Этот assert не должен быть достигнут

    }, true);

    // Тест 9: Подтипизация и присваивание подтипов
    failed_tests += run_test("Test 9: Subtyping Assignment", []() {
        smrt_ptr<C1> derivedPtr(new C1());
        smrt_ptr<C2> basePtr = derivedPtr;

        assert(basePtr->getValue() == 20);
        assert(derivedPtr.use_count() == 2);
    });

    // Тест 10: Проверка счётчика ссылок при подтипизации
    failed_tests += run_test("Test 10: Reference Counting with Subtyping", []() {
        smrt_ptr<C1> derivedPtr1(new C1());
        smrt_ptr<C2> basePtr1 = derivedPtr1;

        assert(basePtr1.use_count() == 2);

        smrt_ptr<C2> basePtr2 = basePtr1;
        assert(basePtr1.use_count() == 3);
    });

    failed_tests += run_test("Test 11: Subtyping Assignment for []", []() {
        smrt_ptr<C1[]> derivedPtr(new C1[3]);
        smrt_ptr<C2[]> basePtr = derivedPtr;


        assert(basePtr[0].getValue() == 20);
        assert(derivedPtr.use_count() == 2);
    });

    return failed_tests;
}

int functional_linked_list_tests() {
    int failed_tests = 0;

    failed_tests += run_test("Test 1: Default Constructor and Size", [](){
        linked_list<int> list;

        assert(list.size() == 0);
        assert(list.null());
    });

    failed_tests += run_test("Test 2: Push Front and Get Front", [](){
        linked_list<int> list;
        list.push_front(10);

        assert(list.size() == 1);
        assert(list.get_front() == 10);
    });

    failed_tests += run_test("Test 3: Multiple Push Fronts and Size Check", [](){
        linked_list<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);

        assert(list.size() == 3);
        assert(list.get_front() == 30);
    });

    failed_tests += run_test("Test 4: Pop Front and Size Check", [](){
        linked_list<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);

        list.pop_front();
        assert(list.size() == 2);
        assert(list.get_front() == 20);

        list.pop_front();
        assert(list.size() == 1);
        assert(list.get_front() == 10);

        list.pop_front();
        assert(list.size() == 0);
        assert(list.null());
    });


    failed_tests += run_test("Test 5: Clear and Null Check", [](){
        linked_list<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);
        list.clear();

        assert(list.size() == 0);
        assert(list.null());
    });

    failed_tests += run_test("Test 6: Mixed Operations", [](){
        linked_list<int> list;
        list.push_front(10);
        assert(list.get_front() == 10);

        list.push_front(20);
        assert(list.get_front() == 20);

        list.pop_front();
        assert(list.get_front() == 10);

        list.clear();
        assert(list.null());
        assert(list.size() == 0);
    });

    return failed_tests;
}










