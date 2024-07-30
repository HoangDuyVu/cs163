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
            return ;
        }
    }

    if (pos == HEAPTREE) {
        int x = heaptree.UpdatePressOn();
        if (x != -1) {
            pos = MENU;
            return ;
        }
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