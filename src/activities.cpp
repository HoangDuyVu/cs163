#include <raylib.h>
#include <variable.hpp>
#include <ViewMenu.hpp>
#include <ViewInApp.hpp>
#include <HeapTree.hpp>
#include <iostream>

Menu  menu;
ViewInApp viewapp;
HeapTree heaptree;
void init(){
    menu.init();
    viewapp.init();
    heaptree.init();
}

void Activities() {
    if (pos == MENU) {
        int x = menu.UpdatePressOn();
        if (x == 0) {
           // std::cout << "co";
            pos = HEAPTREE;
            heaptree.init();
            _create.init({184,496});
            _insert.init({184,536});
            return ;
        }
    }

    if (pos == HEAPTREE) {
        heaptree.Activity();
    }
}

void draw() {
    if (pos == MENU){
        draw_bg();
        menu.draw();
    }
    else if (pos == HEAPTREE) {
        viewapp.draw();
        heaptree.draw();
    }
}