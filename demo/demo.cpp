#include <iostream>
#include <thread>
#include <chrono>

#include "coututils.hpp"

#ifdef _WIN32
    #include <windows.h> 
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {

    #ifdef _WIN32 // support for ansi codes in windows console
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING); // add this flag to the console mode
    #endif

    coututils::clearScreen(std::cout);
    for (int i = 0; i <= 20; ++i) {
        coututils::drawprogressbar(std::cout, 20, static_cast<float>(i) / 20);
        std::cout << "\r"; 
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "\n";
    std::cin.get();
    for (int i = 0; i <= 20; ++i) {
        coututils::drawprogressbar(std::cout, 20, static_cast<float>(i) / 20, {'&', "\033[92m"}, '-', '(', ')');
        std::cout << "\r";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "\n";
    std::cin.get();

    coututils::CharScreen screen(10, 10, {'#', "\033[32m"}, true);

    screen.drawScreen(std::cout);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            screen.setChar(j, i, {'A' + char((i + j) % 26), "\033[34m\033[1m\033[102m"});
            screen.drawScreenInPlace(std::cout);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    for (int sum = 0; sum <= 10 + 10 - 2; ++sum) {
        for (int y = 0; y < 10; ++y) {
            int x = sum - y;
            if (x >= 0 && x < 10) {
                screen.setChar(x, y, {'*', "\033[" + std::to_string((sum % 8) + 90) + "m"}); 
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

    coututils::moveCursorTo(5, 2, std::cout);
    std::cout << "Cursor moved to (5, 2)!\n\n\n";
    std::cout << "Moved back!\n";

    int width, height, channels;
    unsigned char* data = stbi_load("../demo/apple_50x50.bmp", &width, &height, &channels, 0);
    coututils::CharScreen imageScreen = coututils::CharScreen::loadImage(data, width, height, channels);
    imageScreen.drawScreen(std::cout);

    coututils::CharScreen imageScreen2(30, 15);
    imageScreen2.loadImageToScreen(data, width, height, channels, coututils::nearestNeighbourScale);
    imageScreen2.drawScreen(std::cout);
    stbi_image_free(data);

}