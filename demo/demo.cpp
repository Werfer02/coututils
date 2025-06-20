#include <iostream>
#include <thread>
#include <chrono>

#include "coututils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {

    coututils::initWindowsConsole();

    coututils::clearScreen(std::cout);
    for (int i = 0; i <= 20; ++i) {
        coututils::drawprogressbar(std::cout, 20, static_cast<float>(i) / 20);
        std::cout << "\r"; 
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "\n";
    std::cin.get();
    for (int i = 0; i <= 20; ++i) {
        coututils::drawprogressbar(std::cout, 20, static_cast<float>(i) / 20, {'&', coututils::ansi::bright_green}, '-', '(', ')');
        std::cout << "\r";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "\n";
    std::cin.get();

    coututils::CharScreen screen(10, 10, {'#', coututils::ansi::red}, true);

    screen.drawScreen(std::cout);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            screen.setChar(j, i, {static_cast<char>('A' + (i + j) % 26), coututils::ansi::blue + coututils::ansi::bold + coututils::ansi::bg_bright_green});
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

    coututils::drawASCIItext(std::cout, "Hello, World!", 1);
    std::cout << "\n";
    coututils::drawASCIItext(std::cout, "Hello, World!", 1, {'@', coututils::ansi::blue + coututils::ansi::bold + coututils::ansi::bg_bright_green});
    std::cout << "\n";
    coututils::drawASCIItext(std::cout, "Hello, World!", 1, {'&', coututils::ansi::bright_red + coututils::ansi::bg_bright_yellow});
    std::cout << "\n";

    coututils::moveCursorTo(5, 3, std::cout);
    std::cout << "Cursor moved to (5, 3)!";
    coututils::moveCursorTo(0, -3, std::cout);
    std::cout << "Moved back!\n";

    int width1, height1, channels1;
    unsigned char* data1 = stbi_load("../demo/apple_50x50.bmp", &width1, &height1, &channels1, 0);

    int width2, height2, channels2;
    unsigned char* data2 = stbi_load("../demo/orange_50x50.bmp", &width2, &height2, &channels2, 0);

    int width3, height3, channels3;
    unsigned char* data3 = stbi_load("../demo/banana_50x50.bmp", &width3, &height3, &channels3, 0);

    coututils::CharScreen imageScreen = coututils::CharScreen::loadImage(data1, width1, height1, channels1);
    imageScreen.drawScreen(std::cout);
    std::cout << "\n";

    coututils::CharScreen imageScreen2(30, 15);
    imageScreen2.loadImageToScreen(data1, width1, height1, channels1, coututils::nearestNeighbourScale);
    coututils::CharScreen imageScreen3(30, 15);
    imageScreen3.loadImageToScreen(data2, width2, height2, channels2, coututils::nearestNeighbourScale);
    coututils::CharScreen imageScreen4(30, 15);
    imageScreen4.loadImageToScreen(data3, width3, height3, channels3, coututils::nearestNeighbourScale);

    imageScreen2.drawScreen(std::cout);
    imageScreen3.drawScreenAt(std::cout, 45, 14);
    imageScreen4.drawScreenAt(std::cout, 90, 14);
    std::cout << "\n";

    stbi_image_free(data1);
    stbi_image_free(data2);
    stbi_image_free(data3);

}