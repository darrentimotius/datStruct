#include <stdio.h>

#define MAX 100

struct Heap {
    int code[MAX];
    int fuel[MAX];
    int size;
};

int swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int parent(int i) {
    return(i - 1) / 2;
}

int leftChild(int i) {
    return i * 2 + 1;
}

int rightChild(int i) {
    return i * 2 + 2;
}

void insert(Heap* heap ,int code, int fuel) {
    if (heap->size >= MAX) {
        puts("Full");
        return;
    }

    int i = heap->size;
    heap->code[i] = code;
    heap->fuel[i] = fuel;
    heap->size++;

    while (i != 0 && heap->fuel[parent(i)] > heap->fuel[i]) {
        swap(&heap->fuel[parent(i)], &heap->fuel[i]);
        swap(&heap->code[parent(i)], &heap->code[i]);
        i = parent(i);
    }
}

void print(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("Code : %d\n", heap->code[i]);
        printf("Status : %s\n", heap->fuel[i] < 50 ? "Urgent" : "Normal");
        printf("Fuel : %d\n\n", heap->fuel[i]);
    }
}

int main() {
    Heap heap;
    heap.size = 0;

    insert(&heap, 1212, 55);
    insert(&heap, 1414, 12);
    insert(&heap, 4322, 33);
    insert(&heap, 3392, 23);
    insert(&heap, 7728, 54);
    insert(&heap, 9928, 60);

    print(&heap);
}