#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <memory>
#include "graphic.hpp"
#include "smrt_ptr.hpp"
#include "smrt_ptr_tests.hpp"

void print_main_menu() {
    std::cout << "\n=== Главное Меню ===\n";
    std::cout << "1. Запустить функциональные тесты smrt_ptr\n";
    std::cout << "2. Запустить нагрузочный тест (Заполнение вектора)\n";
    std::cout << "3. Вывод графиков\n";
    std::cout << "4. Выход\n";
    std::cout << "Выберите опцию (1-4):  ";
}

void print_load_test_menu() {
    std::cout << "\n=== Меню Тестов Производительности ===\n";
    std::cout << "1. Тестировать smrt_ptr\n";
    std::cout << "2. Тестировать unique_ptr\n";
    std::cout << "3. Тестировать shared_ptr\n";
    std::cout << "4. Тестировать все\n";
    std::cout << "5. Вернуться в главное меню\n";
    std::cout << "Выберите опцию (1-5): ";
}

int get_user_input(int max_option) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > max_option) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Пожалуйста, введите число от 1 до " << max_option << ": ";
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

        std::cout << "Введите размер теста до 10^12: ";
        std::cin >> size_test;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (load_choice) {
            case 1:
                std::cout << "Время выделения smrt_ptr: " << measure_allocation_time<smrt_ptr>(size_test) << " ms\n";
                break;
            case 2:
                std::cout << "Время выделения unique_ptr: " << measure_allocation_time<std::unique_ptr>(size_test) << " ms\n";
                break;
            case 3:
                std::cout << "Время выделения shared_ptr: " << measure_allocation_time<std::shared_ptr>(size_test) << " ms\n";
                break;
            case 4:
                std::cout << "Время выделения smrt_ptr: " << measure_allocation_time<smrt_ptr>(size_test) << " ms\n";
                std::cout << "Время выделения unique_ptr: " << measure_allocation_time<std::unique_ptr>(size_test) << " ms\n";
                std::cout << "Время выделения shared_ptr: " << measure_allocation_time<std::shared_ptr>(size_test) << " ms\n";
                break;
        }
        std::cout << "\nНажмите Enter для продолжения...";
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
                    std::cout << "Все функциональные тесты для smrt_ptr успешно завершены.\n";
                else
                    std::cout << "Не все тесты пройдены. Обнаружены ошибки.\n";
                break;

            case 2:
                run_load_tests();
                break;

            case 3:
                create_graphic(10000, 100000, 10000);
                break;

        }

        if (main_choice != 4) {
            std::cout << "\nНажмите Enter для возврата в главное меню...";
            std::cin.get();
        }

    } while (main_choice != 4);

    std::cout << "Программа завершена.\n";
    return 0;
}
