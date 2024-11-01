#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <exception>
#include "smrtptr.hpp"
#include "smrtptr_tests.hpp"
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

int functional_SmrtPtr_tests() {
    int failed_tests = 0;

    // Test 1: Default Constructor and Dereference
    failed_tests += run_test("Test 1: Default Constructor and Dereference", []() {
        SmrtPtr<int> p1(new int(10));
        assert(*p1 == 10);
        assert(p1.use_count() == 1);

        SmrtPtr<std::string> p2(new std::string("Hello"));
        assert(*p2 == "Hello");
        assert(p2.use_count() == 1);

        SmrtPtr<std::vector<int>> p3(new std::vector<int>{1, 2, 3});
        assert((*p3)[0] == 1);
        assert((*p3)[1] == 2);
        assert((*p3)[2] == 3);
        assert(p3.use_count() == 1);
    });

    // Test 2: Copy Constructor
    failed_tests += run_test("Test 2: Copy Constructor", []() {
        SmrtPtr<int> p1(new int(20));
        SmrtPtr<int> p2(p1);
        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 20);

        SmrtPtr<std::string> p3(new std::string("World"));
        SmrtPtr<std::string> p4(p3);
        assert(p3.use_count() == 2);
        assert(p4.use_count() == 2);
        assert(*p4 == "World");

        SmrtPtr<std::vector<int>> p5(new std::vector<int>{4, 5, 6});
        SmrtPtr<std::vector<int>> p6(p5);
        assert(p5.use_count() == 2);
        assert(p6.use_count() == 2);
        assert((*p6)[0] == 4);
        assert((*p6)[1] == 5);
        assert((*p6)[2] == 6);
    });

    // Test 3: Assignment Operator
    failed_tests += run_test("Test 3: Assignment Operator", []() {
        SmrtPtr<int> p1(new int(30));
        SmrtPtr<int> p2;
        p2 = p1;
        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 30);
    });

    // Test 4: Self-assignment Handling
    failed_tests += run_test("Test 4: Self-assignment Handling", []() {
        SmrtPtr<int> p1(new int(40));
        p1 = p1;
        assert(p1.use_count() == 1);
        assert(*p1 == 40);
    });

    // Test 5: Arrow Operator
    failed_tests += run_test("Test 5: Arrow Operator", []() {
        struct TestStruct {
            int val;
            TestStruct(int v) : val(v) {}
        };
        SmrtPtr<TestStruct> p1(new TestStruct(50));
        assert(p1->val == 50);
    });

    // Test 6: Array Access for SmrtPtr<T[]>
    failed_tests += run_test("Test 6: Array Access for SmrtPtr<T[]>", []() {
        SmrtPtr<int[]> p1(new int[3]{1, 2, 3});
        assert(p1[0] == 1);
        assert(p1[1] == 2);
        assert(p1[2] == 3);
    });

    // Test 7: Null Dereference Exception
    failed_tests += run_test("Test 7: Null Dereference Exception", []() {
        SmrtPtr<int> p1(nullptr);
        *p1;  // Ожидается, что бросит исключение
        assert(false);  // Этот assert не должен быть достигнут
    }, true);

    // Test 8: Null Array Access Exception
    failed_tests += run_test("Test 8: Null Array Access Exception", []() {
        SmrtPtr<int[]> p1(nullptr);
        p1[0];  // Ожидается, что бросит исключение
        assert(false);  // Этот assert не должен быть достигнут
    }, true);

    return failed_tests;
}

int functional_LinkedList_tests() {
    int failed_tests = 0;

    // Test 1: Default Constructor and Size
    failed_tests += run_test("Test 1: Default Constructor and Size", [](){
        LinkedList<int> list;
        assert(list.size() == 0);
        assert(list.null());
    });

    // Test 2: Push Front and Get Front
    failed_tests += run_test("Test 2: Push Front and Get Front", [](){
        LinkedList<int> list;
        list.push_front(10);
        assert(list.size() == 1);
        assert(list.get_front() == 10);
    });

    // Test 3: Multiple Push Fronts and Size Check
    failed_tests += run_test("Test 3: Multiple Push Fronts and Size Check", [](){
        LinkedList<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);
        assert(list.size() == 3);
        assert(list.get_front() == 30);
    });

    // Test 4: Pop Front and Size Check
    failed_tests += run_test("Test 4: Pop Front and Size Check", [](){
        LinkedList<int> list;
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

    // Test 5: Clear and Null Check
    failed_tests += run_test("Test 5: Clear and Null Check", [](){
        LinkedList<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);
        list.clear();
        assert(list.size() == 0);
        assert(list.null());
    });

    // Test 6: Mixed Operations
    failed_tests += run_test("Test 6: Mixed Operations", [](){
        LinkedList<int> list;
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









