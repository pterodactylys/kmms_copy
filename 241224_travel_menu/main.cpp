#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_functions.hpp"
#include "menu_item.hpp"

int main() {
    std::setlocale(LC_ALL, "");

    const ATl::MenuItem* current = &ATl::MAIN;
    do {
        current = current->func(current);
        std::cout << sizeof(current) << std::endl;
    } while (true);

    return 0;
}