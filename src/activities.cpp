#include <raylib.h>
#include <variable.hpp>
#include <ViewMenu.hpp>
#include <ViewInApp.hpp>
#include <HeapTree.hpp>
#include <AVLTree.hpp>
#include <iostream>

Menu  menu;
ViewInApp viewapp;
HeapTree heaptree;
AVLTree avltree;

void init(){
    menu.init();
    viewapp.init();
    heaptree.init();
    avltree.init();
}

void Activities() {
    if (pos == MENU) {
        int x = menu.UpdatePressOn();
        if (x == 0) {
           // std::cout << "co";
            pos = HEAPTREE;
            heaptree.init();
            return ;
        }
        if (x == 1) {
            pos = AVLTREE;
            avltree.init();
        }
    }

    if (pos == HEAPTREE) {
        heaptree.Activity();
    }

    if (pos == AVLTREE) {
        avltree.Activity();
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
    else if (pos == AVLTREE) {
        viewapp.draw();
        avltree.draw();
    }
}