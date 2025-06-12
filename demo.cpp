#include <iostream>
#include <thread>
#include <chrono>

#include "coututils/coututils.hpp"


int main() {

    std::cout << "Hello, World!\n" << std::endl;
    for (int i = 0; i <= 20; ++i) {
        coututils::drawprogressbar(std::cout, 20, static_cast<float>(i) / 20);
        std::cout << "\r"; 
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "\n";
    std::cin.get();
    for (int i = 0; i <= 20; ++i) {
        coututils::drawprogressbar(std::cout, 20, static_cast<float>(i) / 20, '&', '-', '(', ')');
        std::cout << "\r";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "\n";
    std::cin.get();

    coututils::CharScreen screen(10, 10, {'#', "\033[32m"}, true);

    screen.drawScreen(std::cout);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            screen.setChar(j, i, {'A' + (i + j) % 26, "\033[34m\033[1m\033[102m"});
            screen.drawScreenInPlace(std::cout);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    for (int sum = 0; sum <= 10 + 10 - 2; ++sum) {
        for (int y = 0; y < 10; ++y) {
            int x = sum - y;
            if (x >= 0 && x < 10) {
                // Change the character/color at (x,y)
                screen.setChar(x, y, {'*', "\033[91m\033[103m"}); 
            }
        }
        screen.drawScreenInPlace(std::cout);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    coututils::drawASCIItext(std::cout, "Hello, World!", 2);
    std::cout << "\n";
    coututils::drawASCIItext(std::cout, "Hello, World!", 2, {'@', "\033[34m\033[1m\033[102m"});
    std::cout << "\n";
    coututils::drawASCIItext(std::cout, "Hello, World!", 2, {'&', "\033[91m\033[103m"});

}