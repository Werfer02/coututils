#include "coututils.hpp"

namespace coututils {

    void clearScreen(std::ostream& stream) {
        stream << "\033[H\033[J"; // move to top left and clear
    }

    void moveCursorTo(int x, int y, std::ostream& stream) {
        stream << "\033[G"; // move to beginning of line
        for (int i = 0; i < x; ++i) stream << ansi::cursor_right; // move right
        for (int i = 0; i < y; ++i) stream << ansi::cursor_up; // move up
    }

    void CharScreen::setChar(int x, int y, CharScreenPixel c) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            screen[y * width + x] = c;
        }
    }

    void CharScreen::clearScreen(CharScreenPixel defaultchar = CharScreenPixel()) {
        screen = std::vector(width * height, defaultchar);
    }

    void CharScreen::drawScreen(std::ostream& stream) {
        std::string output;
        output.reserve(height * (width * 10)); // speed

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                const auto& px = screen[i * width + j];
                output += px.styles + px.ch;
                if (extrahorizontalspacing) {
                    output += " "; // Extra horizontal spacing
                }
                output += "\033[0m"; // Reset styles
            }
            output += "\n";
        }

        stream << output;
    }

    void CharScreen::drawScreenInPlace(std::ostream& stream) {
        moveCursorTo(0, height, stream); // Move cursor to top left
        drawScreen(stream);
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
        { 1, {{
            "### #   ###   # ### ### ### # # ### ### # # #   ### ### ### ### ### ###  ## ### # # # # # # # # # # ###",
            "### ### #   ### ##  ##  ### ###  #   #  ##  #   ### # # # # ### ### ##  ###  #  # # # # ###  #   #   ##",
            "# # ### ### ### ### #   ### # # ### ##  # # ### # # # # ### #     # # # ##   #  ###  #  ### # #  #  ###",
            }}},
        { 2, {{
            "##### ####  ##### ##### ##### ##### ##### #   # ##### ##### #   # #     #   # #   # ##### ##### ##### ##### ##### ##### #   # #   # #   # #   # #   # ##### #####     # ##### ##### #   # ##### ##### ##### ##### ##### #      # #   # #   #### ##  #  ##   #         # #       #                               #                               ##### #####",
            "#   # #   # #      #  # #     #     #     #   #   #      #  #  #  #     ## ## ##  # #   # #   # #   # #   # #       #   #   # #   # #   #  # #   # #     #  #  ##     #     #     # #   # #     #         # #   # #   # #      # #  ##### # #   ## #  #  #  #        #   #    #####   #                        #   #     #      #    ###    #       # #   #",
            "##### ####  #      #  # ##### ##### #  ## #####   #      #  ###   #     # # # # # # #   # ##### # # # ##### #####   #   #   # #   # # # #   #     #     #   # # #     # ##### ##### ##### ##### #####     # ##### ##### #            # #   ###    #     # #          #   #     # #   ###         ###          #                #             #    ### # # #",
            "#   # #   # #      #  # #     #     #   # #   #   #      #  #  #  #     #   # #  ## #   # #     #  ## #  #      #   #   #   #  # #  # # #  # #    #    #    ##  #     # #         #     #     # #   #     # #   #     #             #####   # #  # ## #  #           #   #            #   #                  #     #     #      #    ###    #         # ###",
            "#   # ####  ##### ##### ##### #     ##### #   # ##### ####  #   # ##### #   # #   # ##### #     ##### #   # #####   #   #####   #   ##### #   #   #   ##### #####     # ##### #####     # ##### #####     # ##### ##### #            # #  ####  #  ##  ## #           # #                 #           #     #            #                        #   #####",
            }}}
    };

    void drawASCIItext(std::ostream& stream, const std::string& text, int fontsize, CharScreenPixel defaultchar) {

        int fontdimension = fontsize * 2 + 1;

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

            if (i < fontdimension - 1) stream << asciiline << "\033[0m" << "\n";
            else stream << asciiline << "\033[0m"; // last line without newline

        }

    }

    void drawprogressbar(std::ostream& stream, int size, float progress, CharScreenPixel fill, CharScreenPixel empty, CharScreenPixel borderleft, CharScreenPixel borderright) {
        int filled = static_cast<int>(size * progress);
        int unfilled = size - filled;

        std::string output;
        output.reserve(size * 10); // speed

        output += borderleft.styles + borderleft.ch + "\033[0m"; // reset styles
        for (int i = 0; i < filled; ++i) {
            output += fill.styles + fill.ch; 
        }
        output += "\033[0m";
        for (int i = 0; i < unfilled; ++i) {
            output += empty.styles + empty.ch;
        }
        output += "\033[0m";
        output += borderright.styles + borderright.ch + "\033[0m";

        stream << output;
    }

}
