#include <sstream>
#include <string>
#include <vector>
#include "smrtptr.hpp"
#include "smrtptr_test.h"
#include "linked_list.hpp"
#include <cassert>

int functional_SmrtPtr_tests() {
    // Test 1: Default Constructor and Dereference
    {
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

    }

    // Test 2: Copy Constructor
    {
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
    }

    // Test 3: Assignment Operator
    {
        SmrtPtr<int> p1(new int(30));
        SmrtPtr<int> p2;
        p2 = p1;
        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
        assert(*p2 == 30);

        SmrtPtr<std::string> p3(new std::string("Assignment"));
        SmrtPtr<std::string> p4;
        p4 = p3;
        assert(p3.use_count() == 2);
        assert(p4.use_count() == 2);
        assert(*p4 == "Assignment");

        SmrtPtr<std::vector<int>> p5(new std::vector<int>{7, 8, 9});
        SmrtPtr<std::vector<int>> p6;
        p6 = p5;
        assert(p5.use_count() == 2);
        assert(p6.use_count() == 2);
        assert((*p6)[0] == 7);
        assert((*p6)[1] == 8);
        assert((*p6)[2] == 9);
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

        SmrtPtr<std::string[]> p2(new std::string[2]{"Hello", "Array"});
        assert(p2[0] == "Hello");
        assert(p2[1] == "Array");
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

int functional_LinkedList_tests() {
    // Test 1: Default Constructor and Size
    {
        LinkedList<int> list;
        assert(list.size() == 0);  // List should be empty initially
        assert(list.null());        // Head should be null
    }

    // Test 2: Push Front and Get Front
    {
        LinkedList<int> list;
        list.push_front(10);          // Add one element
        assert(list.size() == 1);     // Size should now be 1
        assert(list.get_front() == 10); // Front element should be 10
    }

    // Test 3: Multiple Push Fronts and Size Check
    {
        LinkedList<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);
        assert(list.size() == 3);     // Size should reflect three elements
        assert(list.get_front() == 30); // Front should be the last pushed value (30)
    }

    // Test 4: Pop Front and Size Check
    {
        LinkedList<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);

        list.pop_front();             // Remove the first element (30)
        assert(list.size() == 2);     // Size should be 2
        assert(list.get_front() == 20); // Front should now be 20

        list.pop_front();             // Remove the new front (20)
        assert(list.size() == 1);     // Size should be 1
        assert(list.get_front() == 10); // Front should now be 10

        list.pop_front();             // Remove the last element (10)
        assert(list.size() == 0);     // List should now be empty
        assert(list.null());          // Head should be null
    }

    // Test 5: Clear and Null Check
    {
        LinkedList<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);
        list.clear();                 // Clear all elements
        assert(list.size() == 0);     // Size should be 0 after clear
        assert(list.null());          // Head should be null
    }

    // Test 6: Mixed Operations
    {
        LinkedList<int> list;
        list.push_front(10);          // Add one element
        assert(list.get_front() == 10);

        list.push_front(20);          // Add another element
        assert(list.get_front() == 20);

        list.pop_front();             // Remove the front element
        assert(list.get_front() == 10);

        list.clear();                 // Clear the list
        assert(list.null());          // Head should be null after clear
        assert(list.size() == 0);     // Size should be 0 after clear
    }

    return 0;
}


