#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

namespace coututils{

    struct CharScreenPixel {
        char ch;
        std::string styles;
        CharScreenPixel(char c = '#', std::string col = "") : ch(c), styles(col) {}
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

    class ASCIIfont {
        public:
        std::vector<std::string> characters;
        static std::unordered_map<int, ASCIIfont> fonts;
        ASCIIfont(std::vector<std::string> chars) : characters(std::move(chars)) {}
        static int charToASCIIIndex(char c);
    };

    void drawASCIItext(std::ostream& stream, const std::string& text, int fontsize, CharScreenPixel defaultchar = '#');

    void drawprogressbar(std::ostream& stream, int size, float progress, CharScreenPixel fill = '#',
                                                                         CharScreenPixel empty = ' ',
                                                                         CharScreenPixel borderleft = '[',
                                                                         CharScreenPixel borderright = ']');
    

}
