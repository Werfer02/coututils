# coututils

Ignore this please I need to remake this completely

WIP TUI utility library in C++ (ab)using ANSI escape codes

## how to build 
```console
git clone https://github.com/Werfer02/coututils
cd coututils
cmake .
make
```
this builds the library and demo (coututilsdemo) into root directory

## features
- customizable progress bars
- customizable ASCII art text rendering
- customizable CharScreen for 2D graphics and displaying images

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
