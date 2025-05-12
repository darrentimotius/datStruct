#include <stdio.h>

#define MAX 100

struct minHeap {
    int size;
    int arr[MAX];
};

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

void insert(minHeap* heap, int value) {
    if (heap->size >= MAX) {
        puts("Full");
        return;
    }

    int i = heap->size;
    heap->arr[i] = value;
    heap->size++;

    while (i != 0 && heap->arr[parent(i)] > heap->arr[i]) {
        swap(&heap->arr[parent(i)], &heap->arr[i]);
        i = parent(i);
    }
}

void downHeap(minHeap* heap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap->size && heap->arr[left] < heap->arr[i]) {
        smallest = left;
    }

    if (right < heap->size && heap->arr[right] < heap->arr[i]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        downHeap(heap, smallest);
    }
}

int extract(minHeap* heap) {
    if (heap->size <= 0) {
        puts("Empty");
        return -1;
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    downHeap(heap, 0);
    return root;
}

void printHeap(minHeap* heap) {
    int j = 0;
    while (j < heap->size) {
        printf("%d ", heap->arr[j]);
        j++;
    }
    puts("");
}

int main() {
    minHeap heap;
    heap.size = 0;

    insert(&heap, 10);
    insert(&heap, 5);
    insert(&heap, 20);
    insert(&heap, 3);

    extract(&heap);
    printHeap(&heap);
}