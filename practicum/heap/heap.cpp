//root = 0
//left = 2n+1
//right = 2n+2
//parent = (n-1)/2

#include <stdio.h>
#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int heapSize = 0;

int left(int n){
    return n*2 + 1;
}

int right(int n){
    return n*2 + 2;
}

int parent(int n){
    return (n-1)/2;
}

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void insertHeap(int val){
    if (heapSize == MAX_HEAP_SIZE){
        puts("Heap is full");
        return;
    }

    int n = heapSize++;
    /* int n = heapsize;
    heapsize++
    */

    heap[n] = val;
    while(n != 0 && heap[parent(n)] > heap[n]){
        swap(&heap[parent(n)], &heap[n]);
        n = parent(n);
    }
}

int popHeap(){
    if (heapSize == 0){
        puts("Heap is empty");
        return -1;
    }

    int toPop = heap[0];
    heap[0] = heap[--heapSize];

    int n = 0;
    while (left[n] < heapSize) {
        int t = left(n);
        if (right(n) < heapSize && heap[right(n)] < heap[left(n)]) {
            t = right(n);
        }

        if (heap[n] > heap[t]) {
            swap(&heap[n], &heap[t]);
            n = t;
        } else {
            break;
        }
    }
}

void printHeapAsArray(){
    for(int i = 0; i < heapSize; i++){
        printf("%d -> ", heap[i]);
    }
    printf("\n");
}

int main(){
    insertHeap(9);
    printHeapAsArray();

    insertHeap(19);
    printHeapAsArray();

    insertHeap(36);
    printHeapAsArray();

    insertHeap(8);
    printHeapAsArray();

    insertHeap(10);
    printHeapAsArray();

    insertHeap(12);
    printHeapAsArray();

    insertHeap(5);
    printHeapAsArray();

    return 0;
}