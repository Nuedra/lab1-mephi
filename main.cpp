#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <memory>
#include "graphic.hpp"
#include "smrt_ptr.hpp"
#include "smrt_ptr_tests.hpp"

void print_main_menu() {
    std::cout << "\n=== ������� ���� ===\n";
    std::cout << "1. �������� �㭪樮����� ���� smrt_ptr\n";
    std::cout << "2. �������� ����㧮�� ��� (���������� �����)\n";
    std::cout << "3. �뢮� ��䨪��\n";
    std::cout << "4. ��室\n";
    std::cout << "�롥�� ���� (1-4):  ";
}

void print_load_test_menu() {
    std::cout << "\n=== ���� ���⮢ �ந�����⥫쭮�� ===\n";
    std::cout << "1. ����஢��� smrt_ptr\n";
    std::cout << "2. ����஢��� unique_ptr\n";
    std::cout << "3. ����஢��� shared_ptr\n";
    std::cout << "4. ����஢��� ��\n";
    std::cout << "5. �������� � ������� ����\n";
    std::cout << "�롥�� ���� (1-5): ";
}

int get_user_input(int max_option) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > max_option) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "�����४�� ����. ��������, ������ �᫮ �� 1 �� " << max_option << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

void run_load_tests() {
    int load_choice;
    long size_test;

    do {
        print_load_test_menu();
        load_choice = get_user_input(5);

        if (load_choice == 5) break;

        std::cout << "������ ࠧ��� ��� �� 10^12: ";
        std::cin >> size_test;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (load_choice) {
            case 1:
                std::cout << "�६� �뤥����� smrt_ptr: " << measure_allocation_time<smrt_ptr>(size_test) << " ms\n";
                break;
            case 2:
                std::cout << "�६� �뤥����� unique_ptr: " << measure_allocation_time<std::unique_ptr>(size_test) << " ms\n";
                break;
            case 3:
                std::cout << "�६� �뤥����� shared_ptr: " << measure_allocation_time<std::shared_ptr>(size_test) << " ms\n";
                break;
            case 4:
                std::cout << "�६� �뤥����� smrt_ptr: " << measure_allocation_time<smrt_ptr>(size_test) << " ms\n";
                std::cout << "�६� �뤥����� unique_ptr: " << measure_allocation_time<std::unique_ptr>(size_test) << " ms\n";
                std::cout << "�६� �뤥����� shared_ptr: " << measure_allocation_time<std::shared_ptr>(size_test) << " ms\n";
                break;
        }
        std::cout << "\n������ Enter ��� �த�������...";
        std::cin.get();
    } while (load_choice != 5);
}

int main() {
    int main_choice;
    int test_result;

    do {
        print_main_menu();
        main_choice = get_user_input(5);

        switch (main_choice) {
            case 1:
                test_result = functional_smrt_ptr_tests();
                if (test_result == 0)
                    std::cout << "�� �㭪樮����� ���� ��� smrt_ptr �ᯥ譮 �����襭�.\n";
                else
                    std::cout << "�� �� ���� �ன����. �����㦥�� �訡��.\n";
                break;

            case 2:
                run_load_tests();
                break;

            case 3:
                create_graphic(10000, 100000, 10000);
                break;

        }

        if (main_choice != 4) {
            std::cout << "\n������ Enter ��� ������ � ������� ����...";
            std::cin.get();
        }

    } while (main_choice != 4);

    std::cout << "�ணࠬ�� �����襭�.\n";
    return 0;
}
