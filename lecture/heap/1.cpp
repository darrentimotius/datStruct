#include <stdio.h>
#include <string.h>

#define MAX 100

struct Heap {
    char name[MAX][100];
    int labaBersih[MAX];
    int size;
};

void swapInt(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapString(char a[], char b[]) {
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return i * 2 + 1;
}

int rightChild(int i) {
    return i * 2 + 2;
}

void insert(Heap* heap, char name[], int labaKotor, int HPP) {
    if (heap->size >= MAX) {
        puts("Full");
        return;
    }

    int i = heap->size;
    strcpy(heap->name[i], name);
    heap->labaBersih[i] = labaKotor - HPP;
    heap->size++;

    while (i != 0 && heap->labaBersih[parent(i)] < heap->labaBersih[i]) {
        swapString(heap->name[parent(i)], heap->name[i]);
        swapInt(&heap->labaBersih[parent(i)], &heap->labaBersih[i]);
        i = parent(i);
    }
}

// void downHeap(Heap* heap, int i) {
//     int highest = i;
//     int left = leftChild(i);
//     int right = rightChild(i);

//     if (left < heap->size && heap->labaBersih[left] > heap->labaBersih[i]) {
//         highest = left;
//     }

//     if (right < heap->size && heap->labaBersih[right] > heap->labaBersih[i]) {
//         highest = right;
//     }

//     if (highest != i) {
//         swapString(heap->name[i], heap->name[highest]);
//         swapInt(&heap->labaBersih[i], &heap->labaBersih[highest]);
//         downHeap(heap, highest);
//     }
// }

// int extract(Heap* heap) {
//     if (heap->size <= 0) {
//         puts("Empty");
//         return -1;
//     }

//     int root = heap->labaBersih[0];
//     heap->labaBersih[0] = heap->labaBersih[heap->size - 1];
//     swapString(heap->name[0], heap->name[heap->size - 1]);
//     heap->size--;

//     downHeap(heap, 0);
//     return root;
// }

void printHeap(Heap* heap) {
    int j = 0;
    printf("Daftar UMKM : ");
    while (j < heap->size) {
        printf("%s", heap->name[j]);
        if (j != heap->size - 1) printf(", ");
        j++;
    }
    puts("");
    printf("Prioritas : %s\n", heap->name[0]);
}

int main() {
    Heap heap;
    heap.size = 0;

    insert(&heap, "Cilokal", 1000, 250);
    insert(&heap, "Eserut", 500, 100) ;
    insert(&heap, "SotoMadura", 700, 300);
    insert(&heap, "BebekBarokah", 750, 50);
    insert(&heap, "PijaHat",1800, 1100);
    insert(&heap, "Kaepce", 800, 30);
    insert(&heap, "SoBakso", 300, 50);
    insert(&heap, "AyamMoza", 2000, 200);
    insert(&heap, "CirengHot", 1200, 400);

    printHeap(&heap);
    return 0;
}