#include <iostream>
#include <raylib.h>
#include <HeapTree.hpp>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <variable.hpp>
#include <random>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void HeapTree::init(){
    heap = BinaryHeap(30);
}

int HeapTree::UpdatePressOn(){
    bool Press = 0;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) Press = 1;
    int res = viewapp.UpdatePressOn(Press);
    if (res != -1) return res;

    return -1;
}

void HeapTree::draw(){
    Vector2 Mouse = GetMousePosition();
}

void HeapTree::create(int n){
    Animation.clear();
    for (int i = 0 ; i < n ; i++) {
        int x = rng() % 100;
        heap.Insert(x,0);
    }

    std::vector <Transforms> u(heap.size);
    for (int i = 0 ; i < heap.capacity; i++){
        if (i < heap.size) {
            u[i].u = u[i].v;
            u[i].u.color.a = 0;
        }
        else {
            u[i].u.color.a = u[i].v.color.a = 0;
        }
    }

    Animation.push_back(u);

}