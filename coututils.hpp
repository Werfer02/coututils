#include <string>

namespace ansi {

    inline const std::string reset = "\033[0m";

    // styles
    inline const std::string bold = "\033[1m";
    inline const std::string italic = "\033[3m";
    inline const std::string underline = "\033[4m";
    inline const std::string strikethrough = "\033[9m";

    // foreground colors
    inline const std::string black = "\033[30m";
    inline const std::string red = "\033[31m";
    inline const std::string green = "\033[32m";
    inline const std::string yellow = "\033[33m";
    inline const std::string blue = "\033[34m";
    inline const std::string magenta = "\033[35m";
    inline const std::string cyan = "\033[36m";
    inline const std::string white = "\033[37m";
    inline const std::string default_fg = "\033[39m";

    // bright foreground colors
    inline const std::string bright_black = "\033[90m";
    inline const std::string bright_red = "\033[91m";
    inline const std::string bright_green = "\033[92m";
    inline const std::string bright_yellow = "\033[93m";
    inline const std::string bright_blue = "\033[94m";
    inline const std::string bright_magenta = "\033[95m";
    inline const std::string bright_cyan = "\033[96m";
    inline const std::string bright_white = "\033[97m";

    // background colors
    inline const std::string bg_black = "\033[40m";
    inline const std::string bg_red = "\033[41m";
    inline const std::string bg_green = "\033[42m";
    inline const std::string bg_yellow = "\033[43m";
    inline const std::string bg_blue = "\033[44m";
    inline const std::string bg_magenta = "\033[45m";
    inline const std::string bg_cyan = "\033[46m";
    inline const std::string bg_white = "\033[47m";
    inline const std::string default_bg = "\033[49m";

    // bright background colors
    inline const std::string bg_bright_black = "\033[100m";
    inline const std::string bg_bright_red = "\033[101m";
    inline const std::string bg_bright_green = "\033[102m";
    inline const std::string bg_bright_yellow = "\033[103m";
    inline const std::string bg_bright_blue = "\033[104m";
    inline const std::string bg_bright_magenta = "\033[105m";
    inline const std::string bg_bright_cyan = "\033[106m";
    inline const std::string bg_bright_white = "\033[107m";

    // move cursor
    inline const std::string cursor_up = "\033[A";
    inline const std::string cursor_down = "\033[B";
    inline const std::string cursor_right = "\033[C";
    inline const std::string cursor_left = "\033[D";
    inline const std::string cursor_home = "\033[G";
    inline const std::string cursor_topleft = "\033[H";

    inline const std::string clear = "\033[J"; // note: not 100% sure but i think this clears from current position to as far down and right as the cursor can go

    inline const std::string brightnessmap = " .`^\",:;Il!i~+_-?][}{1)(|\\/*tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    inline std::string rgb(int r, int g, int b) {
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }
    inline std::string rgb_bg(int r, int g, int b) {
        return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

}
