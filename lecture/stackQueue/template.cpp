#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int priorityQueue[MAX_SIZE];
int queueSize = 0;

// Function to insert an element into the priority queue
void enqueue(int value) {
    if (queueSize == MAX_SIZE) {
        printf("Priority Queue overflow. Cannot enqueue %d.\n", value);
        return;
    }

    int i = queueSize - 1;

    // Shift elements to make space for the new element in sorted order
    while (i >= 0 && priorityQueue[i] < value) {
        priorityQueue[i + 1] = priorityQueue[i];
        i--;
    }

    priorityQueue[i + 1] = value;
    queueSize++;

    printf("%d enqueued into the priority queue.\n", value);
}

// Function to dequeue the element with the highest priority
int dequeue() {
    if (queueSize == 0) {
        printf("Priority Queue underflow. Cannot dequeue from an empty priority queue.\n");
        return -1; // Signifies an error condition
    }

    int front = priorityQueue[queueSize - 1];
    queueSize--;

    return front;
}

// Function to display the elements in the priority queue
void display() {
    if (queueSize == 0) {
        printf("Priority Queue is empty.\n");
        return;
    }
	
	int i;
    printf("Elements in the priority queue: ");
    for (i = 0; i < queueSize; ++i) {
        printf("%d ", priorityQueue[i]);
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(15);
    enqueue(25);

    display();

    printf("Dequeued element: %d\n", dequeue());

    display();
	
	printf("Dequeued element: %d\n", dequeue());

	display();
    return 0;
}

