#include "coututils.hpp"

#ifdef _WIN32
    #include <windows.h>
#endif

namespace coututils {

    namespace ansi {

        std::string rgb(int r, int g, int b) {
            return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
        }
        std::string rgb_bg(int r, int g, int b) {
            return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
        }

    }

    #ifdef _WIN32
        void initWindowsConsole() {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD mode;
            GetConsoleMode(hConsole, &mode);
            SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING); // add this flag to the console mode
        }
    #else
        void initWindowsConsole() return;
    #endif

    void clearScreen(std::ostream& stream) {
        stream << "\033[H\033[J"; // move to top left and clear
    }

    void moveCursorTo(int x, int y, std::ostream& stream) {
        stream << ansi::cursor_home; // move to start of line
        if (x > 0) stream << "\033[" << x << "C";       // right 
        else if (x < 0) stream << "\033[" << -x << "D"; // left
        if (y > 0) stream << "\033[" << y << "A";       // up
        else if (y < 0) stream << "\033[" << -y << "B"; // down
    }

    void CharScreen::setChar(int x, int y, CharScreenPixel c) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            screen[y * width + x] = c;
        }
    }

    void CharScreen::clearScreen(CharScreenPixel defaultchar = CharScreenPixel()) {
        screen = std::vector(width * height, defaultchar);
    }

    void CharScreen::setScreen(std::vector<CharScreenPixel> pixels){
        screen = std::move(pixels);
    }

    void CharScreen::drawScreen(std::ostream& stream) {
        std::string output;
        output.reserve(height * (width * 10)); // speed

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                const auto& px = screen[i * width + j];
                output += px.styles + px.ch;
                if (extrahorizontalspacing) output += " "; 
                output += ansi::reset; // reset styles
            }
            output += "\n";
        }

        stream << output;
    }

    void CharScreen::drawScreenInPlace(std::ostream& stream) {
        moveCursorTo(0, height, stream); // move cursor to top left
        drawScreen(stream);
    }

    void CharScreen::drawScreenAt(std::ostream& stream, int x, int y) {
        moveCursorTo(x, y, stream); // go to correct x,y
        std::string output;
        output.reserve(height * (width * 10)); // speed
        for (int row = 0; row < height; ++row) {
            if (row > 0) output += ansi::cursor_down + "\033[" + std::to_string(width) + "D"; // move down one row and back to start

            for (int col = 0; col < width; ++col) {
                const auto& pixel = screen[row * width + col];
                output += pixel.styles + pixel.ch;
                output += ansi::reset; // reset styles

                if (extrahorizontalspacing) output += " "; 
            }
        }

        stream << output;
    }

    std::vector<CharScreenPixel> imageToCharScreenPixels(const unsigned char* data, int width, int height, int channels) {
        if (!data) {
            std::cerr << "Error: image data is null!\n";
            return;
        }
        std::vector<CharScreenPixel> pixels(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * channels;

                int r = data[index];
                int g = data[index + 1];
                int b = data[index + 2];

                float brightness = (r + g + b) / (3.0f * 255.0f);
                pixels[y * width + x] = CharScreenPixel(brightnessToChar(brightness), ansi::rgb(r, g, b));
            }
        }

        return pixels;
    }

    CharScreen CharScreen::loadImage(const unsigned char* data, int width, int height, int channels) {
        
        std::vector<CharScreenPixel> pixels = imageToCharScreenPixels(data, width, height, channels);

        CharScreen screen(width, height);
        screen.setScreen(std::move(pixels));
        return screen;

    }

    void CharScreen::loadImageToScreen(const unsigned char* data, int imgwidth, int imgheight, int channels,
        std::function<std::vector<unsigned char> (const unsigned char*, int, int, int, int, int)> scalefunc) {

        std::vector<unsigned char> scaledData = scalefunc(data, imgwidth, imgheight, channels, width, height);
        std::vector<CharScreenPixel> pixels = imageToCharScreenPixels(scaledData.data(), width, height, channels);

        setScreen(std::move(pixels));

    }

    int ASCIIfont::charToASCIIIndex(char c) {
        if(c >= 'A' && c <= 'Z') {
            return c - 'A';
        }
        else if(c >= 'a' && c <= 'z') {
            return c - 'a';
        }
        else if(c >= '0' && c <= '9') {
            return c - '0' + 26; // 26 letters
        }
        else if(c >= '!' && c <= '/') {
            return c - '!' + 36; // 26 letters + 10 digits
        }
        else if(c >= ':' && c <= '@') {
            return c - ':' + 51; // 26 letters + 10 digits + 15 special
        }
        else return ' ';
    }

    std::unordered_map<int, ASCIIfont> ASCIIfont::fonts = {
        {1, {{
        "##### ####  ##### ##### ##### ##### ##### #   # ##### ##### #   # #     #   # #   # ##### ##### ##### ##### ##### ##### #   # #   # #   # #   # #   # ##### #####     # ##### ##### #   # ##### ##### ##### ##### ##### #      # #   # #   #### ##  #  ##   #         # #       #                               #                               ##### #####",
        "#   # #   # #      #  # #     #     #     #   #   #      #  #  #  #     ## ## ##  # #   # #   # #   # #   # #       #   #   # #   # #   #  # #   # #     #  #  ##     #     #     # #   # #     #         # #   # #   # #      # #  ##### # #   ## #  #  #  #        #   #    #####   #                        #   #     #      #    ###    #       # #   #",
        "##### ####  #      #  # ##### ##### #  ## #####   #      #  ###   #     # # # # # # #   # ##### # # # ##### #####   #   #   # #   # # # #   #     #     #   # # #     # ##### ##### ##### ##### #####     # ##### ##### #            # #   ###    #     # #          #   #     # #   ###         ###          #                #             #    ### # # #",
        "#   # #   # #      #  # #     #     #   # #   #   #      #  #  #  #     #   # #  ## #   # #     #  ## #  #      #   #   #   #  # #  # # #  # #    #    #    ##  #     # #         #     #     # #   #     # #   #     #             #####   # #  # ## #  #           #   #            #   #                  #     #     #      #    ###    #         # ###",
        "#   # ####  ##### ##### ##### #     ##### #   # ##### ####  #   # ##### #   # #   # ##### #     ##### #   # #####   #   #####   #   ##### #   #   #   ##### #####     # ##### #####     # ##### #####     # ##### ##### #            # #  ####  #  ##  ## #           # #                 #           #     #            #                        #   #####",
        }}}
    };

    char brightnessToChar(float brightness) {
        std::string chars = " .`^\",:;Il!i~+_-?][}{1)(|\\/*tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
        return chars[int(brightness * (chars.size() - 1))];
    }


    void drawASCIItext(std::ostream& stream, const std::string& text, int fontsize, CharScreenPixel defaultchar) {

        int fontdimension = fontsize * 4 + 1;

        for (int i = 0; i < fontdimension; i++){

            std::string asciiline;
            for (const char c : text) {
                if(c == ' ') {
                    asciiline += std::string(fontdimension + 1, ' ');
                    continue;
                }
                std::string asciicharline = ASCIIfont::fonts.at(fontsize).characters[i].substr((ASCIIfont::charToASCIIIndex(c)) * (fontdimension + 1), fontdimension + 1);
                if (defaultchar.ch != '#' || !defaultchar.styles.empty()) {
                    std::string styledline;
                    for (char ch : asciicharline) {
                        if (ch == '#') {
                            styledline += defaultchar.styles;  // insert styles before
                            styledline += defaultchar.ch;
                        } else {
                            styledline += ch; // keep unchanged
                        }
                    }
                    asciicharline = styledline;
                }
                asciiline += asciicharline;

            }

            if (i < fontdimension - 1) stream << asciiline << ansi::reset << "\n";
            else stream << asciiline << ansi::reset; // last line without newline

        }

    }

    void drawprogressbar(std::ostream& stream, int size, float progress, CharScreenPixel fill, CharScreenPixel empty, CharScreenPixel borderleft, CharScreenPixel borderright) {
        int filled = static_cast<int>(size * progress);
        int unfilled = size - filled;

        std::string output;
        output.reserve(size * 10); // speed

        output += borderleft.styles + borderleft.ch + ansi::reset; // reset styles
        for (int i = 0; i < filled; ++i) {
            output += fill.styles + fill.ch; 
        }
        output += ansi::reset;
        for (int i = 0; i < unfilled; ++i) {
            output += empty.styles + empty.ch;
        }
        output += ansi::reset;
        output += borderright.styles + borderright.ch + ansi::reset;

        stream << output;
    }

    std::vector<unsigned char> nearestNeighbourScale(const unsigned char* data, int srcW, int srcH, int channels, int dstW, int dstH) {
        std::vector<unsigned char> out(dstW * dstH * channels);
        for (int y = 0; y < dstH; ++y) {
            for (int x = 0; x < dstW; ++x) {
                int srcX = x * srcW / dstW; // calculate nearest
                int srcY = y * srcH / dstH;
                for (int c = 0; c < channels; ++c) {
                    out[(y * dstW + x) * channels + c] = data[(srcY * srcW + srcX) * channels + c];
                }
            }
        }
        return out;
    }

}
