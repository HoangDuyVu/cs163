#include <iostream>
#include <raylib.h>
#include <HeapTree.hpp>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <variable.hpp>
#include <random>

void HeapTree::init(){
    heap = BinaryHeap(30);
    select.init();
    deltaTime = 1.0f;
}

int HeapTree::UpdatePressOn(){
    bool Press = 0;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Press = 1;
    int res = viewapp.UpdatePressOn(Press);
    if (res != -1) return res;

    res = select.checkPressOn(Press);

    if (res != -1) return res;
    return -1;
}

Vector2 NewPos2D(Vector2 A,Vector2 B,float g) {
    return {A.x + (B.x - A.x)*g,A.y + (B.y - A.y)*g};
}

float NewPos1D(float x, float y, float g) {
    return x + (y - x)*g;
}

void DrawAnimation(std::vector<Transforms> f,double g){
    for (Transforms v : f) {
        Vector2 NewPostion = NewPos2D(v.u.Postion,v.v.Postion,g);
        int NewA = (int) std::min((float)254.0,NewPos1D(v.u.Af,255,g));
        NewA = std::max(NewA,0);

        DrawVertex(NewPostion,v.u.radius,v.u.val,v.u.color,v.u.Af);
        DrawVertex(NewPostion,v.u.radius,v.u.val,v.v.color,NewA);
    }
}

void DrawAnimationEdge(std::vector<TransformsEdge> f,double g){
    for (TransformsEdge v : f) {
        Vector2 NewPostionX = NewPos2D(v.u.PostionX,v.v.PostionX,g);
        Vector2 NewPostionY = NewPos2D(v.u.PostionY,v.v.PostionY,g);
        Vector2 NewPostionVal = NewPos2D(v.u.PostionVal,v.v.PostionVal,g);
        int NewA = (int) std::min((float)254.0,NewPos1D(v.u.Af,v.v.Af,g));
        NewA = std::max(NewA,0);

        NewPostionVal.y += 34;
        DrawEdge(NewPostionX,NewPostionY,v.v.val,0,NewA);
        DrawVertex(NewPostionVal,17,v.v.val,4,NewA);
    }
}


void HeapTree::draw(){
    Vector2 Mouse = GetMousePosition();
    select.draw();
   // DrawVertex(Vector2 {500,300},25,10,1,255);

    if (Animation.size() > 0) {

        double NowTime = GetTime();
        TotalTime += NowTime - LastTime;
       // std::cout << NowTime - LastTime << "\n";
        LastTime = NowTime;
        if (TotalTime > deltaTime) {
            if (pos_ani + 1 < Animation.size()) {
                pos_ani++;
                TotalTime = 0;
            } else TotalTime = deltaTime;
        }

        double G = std::min((double)1.0,(double)TotalTime/deltaTime);
 
        DrawAnimationEdge(AnimationEdge[pos_ani],G);
        DrawAnimation(Animation[pos_ani],G);
    } 

   // std:: cout << deltaTime << " " << TotalTime << " " << LastTime << " " << pos_ani << "\n"; 

    //std::cout << Animation.size() << "\n";
}

void HeapTree::Activity(){
    int g = UpdatePressOn();
    if (g == 101 || g == 102) {
        pos = MENU;
        return ;
    } 

    if (g == 0) {
        if (select.KIND == 0) {
            select.KIND ^= 1;
            select.Textr = select.Open;
        }
        else {
            select.KIND ^= 1;
            select.Textr = select.Close;
        }
    }

    if (g == 200) {
        int n = 0;
        for (int i = 0 ; _create.a[i] != '\0' ; i++)
            n = n * 10 + _create.a[i] - '0';
        create(n);
    }
    else if (g == 201) {
        int n = 0;
        std::cout << "co\n";
        for (int i = 0 ; _insert.a[i] != '\0' ; i++)
            n = n * 10 + _insert.a[i] - '0';
        insert(n);
    }

    if (g >= 1 && g <= 5) {
        SelectPress(g - 1);
    }

    if (g != -1) std::cout << g << "\n";
}

void HeapTree::SelectPress(int pos) {
    select.sel[pos].press ^= 1;
    if (select.sel[pos].press)
    for (int i = 0 ; i < 5 ; i++)
        if (i != pos) select.sel[i].press = 0;
}

void HeapTree::create(int n){
    heap = BinaryHeap(30);
    Animation.clear();
    AnimationEdge.clear();
    std::cout << n << " " << heap.size << "\n";
    for (int i = 0 ; i < n ; i++) {
        int x = rng() % 100;
        heap.Insert(x,0,Animation,AnimationEdge);
    }

    // heap.DFS(0,heap.arr[0],60,1380,140,80);
    // int cnt = 0;

    // for (int i = 0 ; i < heap.size; i++){

    //     if (i == 0) {
    //         int v = i;
    //         Edge x = Edge(heap.arr[i].Postion,heap.arr[v].Postion,heap.arr[v].Postion,0,v,255);
    //         g[cnt].u = g[cnt].v = x;
    //         g[cnt].u.Af = 0;     
    //         cnt++;
    //     }

    //     if (i*2 + 1 < heap.size) {
    //         int v = i*2 + 1;
    //         Edge x = Edge(heap.arr[i].Postion,heap.arr[v].Postion,heap.arr[v].Postion,0,v,255);
    //         g[cnt].u = g[cnt].v = x;
    //         g[cnt].u.Af = 0;
    //         cnt++;
    //     }

    //     if (i*2 + 2 < heap.size) {
    //         int v = i*2 + 2;
    //         Edge x = Edge(heap.arr[i].Postion,heap.arr[v].Postion,heap.arr[v].Postion,0,v,255);
    //         g[cnt].u = g[cnt].v = x;
    //         g[cnt].u.Af = 0;     
    //         cnt++;
    //     }

    //     u[i].v = heap.arr[i];
    //     if (i < heap.size) {
    //         u[i].u = u[i].v;
    //         u[i].u.Af = 0;
    //        // std::cout << u[i].v.Postion.x << " " << u[i].v.Postion.y << "\n";
    //     }
    //     else {
    //         u[i].u.Af = u[i].v.Af = 0;
    //     }
    // }

    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;
    Unre.push_back(Animation);
    UnreEdge.push_back(AnimationEdge);
}

void HeapTree::insert(int val) {
    pos_ani = 0;
    LastTime = GetTime();
    TotalTime = 0;
    Animation.clear();
    AnimationEdge.clear();

    heap.Insert(val,1,Animation,AnimationEdge);
   // std::cout << Animation[0].size() << " " << AnimationEdge[0].size() << "\n";
    Unre.push_back(Animation);
    UnreEdge.push_back(AnimationEdge);
}