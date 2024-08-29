#include <raylib.h>
#include <variable.hpp>
#include <ViewMenu.hpp>
#include <ViewInApp.hpp>
#include <HeapTree.hpp>
#include <AVLTree.hpp>
#include <TTFTree.hpp>
#include <Trie.hpp>
#include <Hashtable.hpp>
#include <Graph.hpp>
#include <iostream>

Menu  menu;
ViewInApp viewapp;
HeapTree heaptree;
AVLTree avltree;
Hashtable hashtable;
TTFTree ttftree;
Trie trie;
Graph graph;


void init(){
    menu.init();
    viewapp.init();
    heaptree.init();
    avltree.init();
    hashtable.init();
    ttftree.init();
    trie.init();
    graph.init();
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

        if (x == 3) {
            pos = HASHTABLE;
            hashtable.init();
        }

        if (x == 4) {
            pos = TRIE;
            trie.init();
        }

        if (x == 2) {
            pos = TTFTREE;
            ttftree.init();
        }

        if (x == 5) {
            pos = GRAPH;
            graph.init();
        }
    }

    if (pos == HEAPTREE) {
        heaptree.Activity();
    }

    if (pos == AVLTREE) {
        avltree.Activity();
    }
    
    if (pos == HASHTABLE) {
        hashtable.Activity();
    }

    if (pos == TTFTREE) {
        ttftree.Activity();
    }

    if (pos == TRIE) {
        trie.Activity();
    }

    if (pos == GRAPH) {
        graph.Activity();
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
    else if (pos == HASHTABLE) {
        viewapp.draw();
        hashtable.draw();
    }
    else if (pos == TTFTREE) {
        viewapp.draw();
        ttftree.draw();
    }
    else if (pos == TRIE) {
        viewapp.draw();
        trie.draw();
    }
    else if (pos == GRAPH) {
        viewapp.draw();
        graph.draw();
    }
}