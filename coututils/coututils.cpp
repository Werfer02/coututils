#include "coututils.hpp"

namespace coututils {

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
        for(int i = 0; i < height; ++i) {
            stream << "\033[F";
        }
        drawScreen(stream);
    }

    void drawprogressbar(std::ostream& stream, int size, float progress, CharScreenPixel fill, CharScreenPixel empty, CharScreenPixel borderleft, CharScreenPixel borderright) {
        int filled = static_cast<int>(size * progress);
        int unfilled = size - filled;

        std::string output;
        output.reserve(size * 10); // speed

        output += borderleft.styles + borderleft.ch;
        for (int i = 0; i < filled; ++i) {
            output += fill.styles + fill.ch;
        }
        for (int i = 0; i < unfilled; ++i) {
            output += empty.styles + empty.ch;
        }
        output += borderright.styles + borderright.ch;

        stream << output;
    }

}
