
#ifndef ViewInApp_hpp
#define ViewInApp_hpp
#include <raylib.h>
#include <iostream>
#include <vector>
#include <node.hpp>
#include <variable.hpp>


class ViewInApp {

private:
    std::vector <button_select> Botton;
public:
    void init();
    void draw();
    int UpdatePressOn(bool Press);
};

#endif


