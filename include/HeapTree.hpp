
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
    std::vector <std::vector<Transforms> > Animation;
    std::vector <std::vector <std::vector<Transforms> > > Unre; 
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

        void Insert(int x,bool Ani) {
            if (size == capacity) {
            std::cout << "Binary Heap Overflwon" << std::endl;
            return;
            }
            arr[size].val = x; 
            int k = size;
            size++;

            while (k != 0 && arr[parent(k)].val > arr[k].val) {
            swap( & arr[parent(k)].val, & arr[k].val);
            k = parent(k);
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
    };
    
    BinaryHeap heap;

public:
    void create(int n);
    void init();
    void draw();
    int UpdatePressOn();
};

#endif 