# coututils

WIP TUI utility library in C++ (ab)using ANSI escape codes

## features
- customizable progress bars
- customizable ASCII art text rendering
- customizable CharScreen for 2D graphics

## example

```cpp
coututils::drawprogressbar(std::cout, 20, 0.5f);                      // [##########          ]

coututils::drawprogressbar(std::cout, 20, 0.5f, '&', '-', '(', ')');  // (&&&&&&&&&&----------)

coututils::drawASCIItext(std::cout, "Hello, World!", 2);  //  #   # ##### #     #     #####             #   # ##### ##### #     ##### #     
                                                          //  #   # #     #     #     #   #             #   # #   # #   # #      #  # #
                                                          //  ##### ##### #     #     #   #             # # # #   # ##### #      #  # #
                                                          //  #   # #     #     #     #   # #           # # # #   # #  #  #      #  #
                                                          //  #   # ##### ##### ##### ##### #           ##### ##### #   # ##### ##### #

coututils::CharScreen screen(10, 5, '%', true);
screen.drawScreen(std::cout);  //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%%%%%%%

screen.setChar(4, 3, 'A');
screen.drawScreen(std::cout);  //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%A%%%%%
                               //  %%%%%%%%%%

screen.clearScreen();
screen.drawScreen(std::cout);  //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%%%%%%%
                               //  %%%%%%%%%%
etc.

```
see demo.cpp for more
