
#ifndef ViewMenu_hpp
#define ViewMenu_hpp
#include <raylib.h>
#include <iostream>
#include <vector>
#include <node.hpp>
#include <variable.hpp>


class Menu {

private:
    std::vector <button_select> Botton;
public:
    void init();
    void draw();
    int UpdatePressOn();
};
 
#endif


