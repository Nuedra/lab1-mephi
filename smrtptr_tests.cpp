#include <sstream>
#include <string>
#include "smrtptr.hpp"
#include "smrtptr_test.h"
#include <cassert>

int functional_SmrtPtr_tests() {
    // Test 1: Default Constructor and Dereference
    {
        SmrtPtr<int> p1(new int(10));
        assert(*p1 == 10);
        assert(p1.use_count() == 1);
    }

    // Test 2: Copy Constructor
    {
        SmrtPtr<int> p1(new int(20));
        SmrtPtr<int> p2(p1);
        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 20);
    }

    // Test 3: Assignment Operator
    {
        SmrtPtr<int> p1(new int(30));
        SmrtPtr<int> p2;
        p2 = p1;
        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 30);
    }

    // Test 4: Self-assignment Handling
    {
        SmrtPtr<int> p1(new int(40));
        p1 = p1;  // Self-assignment
        assert(p1.use_count() == 1);
        assert(*p1 == 40);
    }

    // Test 5: Arrow Operator
    {
        struct TestStruct {
            int val;
            TestStruct(int v) : val(v) {}
        };

        SmrtPtr<TestStruct> p1(new TestStruct(50));
        assert(p1->val == 50);
    }

    // Test 6: Array Access for SmrtPtr<T[]>
    {
        SmrtPtr<int[]> p1(new int[3]{1, 2, 3});
        assert(p1[0] == 1);
        assert(p1[1] == 2);
        assert(p1[2] == 3);
    }

    // Test 7: Null Dereference Exception
    {
        SmrtPtr<int> p1(nullptr);
        try {
            *p1;  // Should throw
            assert(false);  // Should not reach here
        } catch (const std::logic_error &) {
            // Ожидается исключения
        }
    }

    // Test 8: Null Array Access Exception
    {
        SmrtPtr<int[]> p1(nullptr);
        try {
            p1[0];  // Should throw
            assert(false);  // Should not reach here
        } catch (const std::logic_error &) {
            // Ожидается исключения
        }
    }

    return 0;
}

