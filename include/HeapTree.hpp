
#ifndef HeapTree_hpp
#define HeapTree_hpp
#include <raylib.h>
#include <variable.hpp>
#include <ViewInApp.hpp>
#include <activities.hpp>
#include <iostream>
#include <vector>


class HeapTree {

private:


    struct Select
    {
        std::vector <choose> sel;
        Texture2D Close;
        Texture2D Open;
        Texture2D Textr;
        Vector2 Postion,Size;
        int KIND;
        bool col;
        void init(){
            KIND = 0;
            Postion = {0,498};
            Close = LoadTexture("res/textures/select/Open.png");
            Open  = LoadTexture("res/textures/select/close.png");
            Textr = Close;
            Size = {(float)Close.width,(float)Close.height};
            sel.resize(5);
            sel[0] = choose(Create, Vector2 {27,496},Vector2 {150,40},"Create",ConstColor1,ConstColor2,0);
            sel[1] = choose(Insert, Vector2 {27,536},Vector2 {150,40},"Insert",ConstColor1,ConstColor2,0);
            sel[2] = choose(Create, Vector2 {27,576},Vector2 {150,40},"Create",ConstColor1,ConstColor2,0);
            sel[3] = choose(Create, Vector2 {27,616},Vector2 {150,40},"Create",ConstColor1,ConstColor2,0);
            sel[4] = choose(Create, Vector2 {27,656},Vector2 {150,40},"Create",ConstColor1,ConstColor2,0);
        }

        bool CheckMouse(Vector2 A,int k){
            return Postion.x <= A.x - k && Postion.x + Size.x >= A.x + k 
                && Postion.y <= A.y - k && Postion.y + Size.y >= A.y + k;    
        }

        Texture2D getTexture(){
            if (KIND) return Close;
            return Open;
        }

        void draw(){
            Vector2 x = GetMousePosition();
            float g = 1;
            if (CheckMouse(x,1)) g = 0.6f;
            DrawTextureV(getTexture(),Postion,Fade(WHITE,g));

            if (KIND == 1) {
                for (choose v : sel) {
                    v.Draw();
                    if (v.press) v.DrawPress();
                }
            }
        }

        int checkPressOn(bool Press){
            if (Press && CheckMouse(GetMousePosition(),1)) return 0;
            int d = 1;

            if (KIND == 1) for (choose v : sel) {
                if (Press && v.CheckMouse(GetMousePosition(),1)) return d;
                d++;
            }


            if (KIND == 1) {
                for (choose &v : sel){
                    if (v.press) {
                        v.SolvePress();
                        if (v.kind == Create && _create.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            return 200;
                        } 

                        if (v.kind == Insert && _insert.Item[2].CheckPress(GetMousePosition(),1,IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                            v.press = 0;
                            KIND = 0;
                            return 201;
                        }
                    }
                }
            }
            return -1;
        }

    };

    std::vector <std::vector<Transforms> > Animation;
    std::vector <std::vector <std::vector<Transforms> > > Unre; 
    std::vector <std::vector<TransformsEdge> > AnimationEdge;
    std::vector <std::vector <std::vector<TransformsEdge> > > UnreEdge; 
    class BinaryHeap { 
    public:
        int capacity;
        int size;
        std::vector<Vertex> arr;



        BinaryHeap(int cap = 0) {
            capacity = cap; 
            size = 0;
            arr.resize(capacity);
        }

        int parent(int i) {
            return (i - 1) / 2;
        }

        int left(int i) {
            return 2 * i + 1;
        }

        int right(int i) {
            return 2 * i + 2;
        }

        void dfs(int id,int par,int l,int r,int h, int delta, std::vector<Transforms> &g,std::vector <TransformsEdge> &f){
            Vertex &u = arr[id];
            u.Postion = {(float)((l + r) / 2.0),(float)h};
            g[id].u = g[id].v = u;
            f[id].u = f[id].v = Edge(arr[par].Postion,u.Postion,u.Postion,0,id,255);

            if (left(id) < size) dfs(left(id),id,l,(l + r)/2,h + delta,delta,g,f);
            if (right(id) < size) dfs(right(id),id,(l + r)/2,r,h + delta,delta,g,f);
        }

        void Insert(int x,bool Ani,std::vector <std::vector<Transforms> > &AnimationI,std::vector <std::vector<TransformsEdge> > &AnimationEdgeI) {
            if (size == capacity) {
            std::cout << "Binary Heap Overflwon" << std::endl;
            return;
            }

          //  std::cout << "ggg\n";

            std::vector <Transforms> Anima; 
            std::vector <TransformsEdge> AnimaE;
            Anima.resize(size + 1);
            AnimaE.resize(size + 1);
            arr[size].val = x;
            arr[size].color = 0;
            arr[size].radius = 17;
            arr[size].Af = 255; 
            int k = size;
            size++;
          //  cout << Anima.size()
         //   return ;
            dfs(0,0,60,1380,140,80,Anima,AnimaE);

            Anima[k].u = Anima[k].v;
            Anima[k].u.Af = 0;
            AnimaE[k].u.Af = 0;
            Anima[k].v.color = 2;
            AnimationI.push_back(Anima);
            AnimationEdgeI.push_back(AnimaE);

            while (k != 0 && arr[parent(k)].val > arr[k].val) {
                Anima[parent(k)].v.color = 1;
                Anima[k].u.color = 2;
                Anima[k].u.Af = 255;
                AnimaE[k].u.Af = 255;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
                swap( & arr[parent(k)].val, & arr[k].val);

                std::swap(Anima[k].v.Postion,Anima[parent(k)].v.Postion);
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
                k = parent(k);
                
                dfs(0,0,60,1380,140,80,Anima,AnimaE);
                Anima[k].v.color = 2;
                AnimationI.push_back(Anima);
                AnimationEdgeI.push_back(AnimaE);
            }
        }

        void Heapify(int ind) {
            int ri = right(ind); 
            int li = left(ind);
            int smallest = ind;
            if (li < size && arr[li].val < arr[smallest].val)
            smallest = li;
            if (ri < size && arr[ri].val < arr[smallest].val)
            smallest = ri;
            if (smallest != ind) {
            swap( & arr[ind].val, & arr[smallest].val);
            Heapify(smallest);
            }
        }
        int getMin() {
            return arr[0].val;
        }
        int ExtractMin() {
            if (size <= 0)
            return INT_MAX;
            if (size == 1) {
            size--;
            return arr[0].val;
            }
            int mini = arr[0].val;
            arr[0] = arr[size - 1]; /*Copy last Node value to root Node value*/
            size--;
            Heapify(0); /*Call heapify on root node*/
            return mini;
        }
        void Decreasekey(int i, int val) {
            arr[i].val = val; /*Updating the new_val*/
            while (i != 0 && arr[parent(i)].val > arr[i].val) /*Fixing the Min heap*/ {
            swap( & arr[parent(i)].val, & arr[i].val);
            i = parent(i);
            }
        }
        void Delete(int i) {
            Decreasekey(i, INT_MIN);
            ExtractMin();
        }
        void swap(int * x, int * y) {
            int temp = * x;
            * x = * y;
            * y = temp;
        }
        void print() {
            for (int i = 0; i < size; i++)
            std::cout << arr[i].val << " ";
            std::cout << std::endl;
        }

        void DFS(int id,Vertex &u, int l, int r,int h ,int delta) {
            u.Postion = {(float)((l + r) / 2.0),(float)h};
            u.color = 0;
            u.kind_mouse = 0;
            u.radius = 17;
            u.Af = 255;

            if (left(id) < size) DFS(left(id),arr[left(id)],l,(l + r)/2,h + delta,delta);
            if (right(id) < size) DFS(right(id),arr[right(id)],(l + r)/2,r,h + delta,delta);
        }
    };
    
    BinaryHeap heap;
    Select select;
    double deltaTime;
    double LastTime,NewTime,TotalTime;
    int pos_ani;


public:
    void create(int n);
    void insert(int val);
    void init();
    void draw();
    int UpdatePressOn();
    void Activity();
    void SelectPress(int pos);
};

#endif 