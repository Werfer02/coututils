#include <iostream>
#include <string>
#include <vector>

namespace coututils{

    struct CharScreenPixel {
        char ch;
        std::string styles;
        CharScreenPixel(char c = '#', std::string col = "\033[0m") : ch(c), styles(col) {}
    }; 

    class CharScreen {

        int width;
        int height;
        std::vector<CharScreenPixel> screen;
        bool extrahorizontalspacing = false;

    public:

        CharScreen(int width, int height, CharScreenPixel defaultchar = CharScreenPixel(), bool extrahorizontalspace = false)
        : extrahorizontalspacing(extrahorizontalspace), width(width), height(height), screen(width * height, defaultchar) {}

        void setChar(int x, int y, CharScreenPixel c);

        void clearScreen(CharScreenPixel defaultchar);

        void drawScreen(std::ostream& stream);

        void drawScreenInPlace(std::ostream& stream);

    };

    void drawprogressbar(std::ostream& stream, int size, float progress, CharScreenPixel fill = '#',
                                                                         CharScreenPixel empty = ' ',
                                                                         CharScreenPixel borderleft = '[',
                                                                         CharScreenPixel borderright = ']');

}
