#include <stdio.h>
#include <string.h>

#define MAX 1000

struct Node {
    char taskName[35];
    int urgencyScore;
};

Node heap[MAX];
int heap_size = 0;

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

void upHeap(int i) {
    while (i > 0) {
        if (heap[parent(i)].urgencyScore > heap[i].urgencyScore) {
            swap(&heap[parent(i)], &heap[i]);
            i = parent(i);
        } else {
            break;
        }
    }
}

void insert(Node c) {
    if (heap_size == MAX) {
        return;
    }

    heap[heap_size] = c;
    heap_size++;
    upHeap(heap_size - 1);
}

void heapify(int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap_size && heap[left].urgencyScore < heap[smallest].urgencyScore) {
        smallest = left;
    } 
    if (right < heap_size && heap[right].urgencyScore < heap[smallest].urgencyScore) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(smallest);
    }
}

Node deleteHeap() {
    if (heap_size == 0) {
        return heap[0];
    }

    Node root = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    heapify(0);
    return root;
}

int main() {
    int T;
    scanf("%d", &T); getchar();

    for (int i = 0; i < T; i++) {
        char choice[35];
        scanf("%s", choice); getchar();

        if (strcmp(choice, "ADD") == 0) {
            Node c;
            scanf("%s %d", c.taskName, &c.urgencyScore); getchar();
            insert(c);
        } else if (strcmp(choice, "PROCESS") == 0) {
            if (heap_size > 0) {
                Node processed = deleteHeap();
                printf("%s\n", processed.taskName);
            } else {
                puts("No jobs pending.");
            }
        }
    }
    return 0;
}