#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct Data {
    char name[50];
    int age;
    int status;
};

Data* priorityQueue[MAX_SIZE];
int queueSize = 0;

void enqueue(char name[], int age, char status[]) {
    if (queueSize == MAX_SIZE) {
        printf("Priority Queue overflow. Cannot enqueue %s.\n", name);
        return;
    }

	Data* newData = (Data*)malloc(sizeof(Data));
    if (newData == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newData->name, name);
    newData->age = age;
    int statusNum = -1;
    if (strcmp(status, "Low") == 0) {
        newData->status = 3;
        statusNum = 3;
    } else if (strcmp(status, "Mid") == 0) {
        newData->status = 2;
        statusNum = 2;
    }else if (strcmp(status, "High") == 0) {
        newData->status = 1;
        statusNum = 1;
    }

    int i = queueSize - 1;

    while (i >= 0 && priorityQueue[i]->status > statusNum) {
        priorityQueue[i + 1] = priorityQueue[i];
        i--;
    }

    priorityQueue[i + 1] = newData;
    queueSize++;

    printf("%s enqueued into the priority queue.\n", name);
}

Data* dequeue() {
    if (queueSize == 0) {
        printf("Priority Queue underflow. Cannot dequeue from an empty priority queue.\n");
        return NULL;
    }

    Data* front = priorityQueue[0];
    for (int i = 0; i < queueSize - 1; i++) {
        priorityQueue[i] = priorityQueue[i + 1];
    }
    queueSize--;

    return front;
}

void display() {
    if (queueSize == 0) {
        printf("Priority Queue is empty.\n");
        return;
    }

    printf("Elements in the priority queue:\n");
    for (int i = 0; i < queueSize; ++i) {
        printf("Name: %s, Age: %d, Priority: %d\n", priorityQueue[i]->name, priorityQueue[i]->age, priorityQueue[i]->status);
    }
}

int main() {
    enqueue("Rizki", 33, "Low");
    enqueue("Richard", 26, "Low");
    enqueue("Andi", 16, "High");
    enqueue("Nur", 74, "Mid");
    enqueue("Coki", 66, "Low");
    
    printf("\n");

    display();
    
    printf("\n");
	
 	Data* patient = dequeue();
    if (patient != NULL) {
        printf("Dequeued element: Name: %s, Age: %d, Priority: %d\n", patient->name, patient->age, patient->status);
        free(patient);
    }

    display();
    printf("\n");

    patient = dequeue();
    if (patient != NULL) {
        printf("Dequeued element: Name: %s, Age: %d, Priority: %d\n", patient->name, patient->age, patient->status);
        free(patient);
    }

    display();
    printf("\n");

    for (int i = 0; i < queueSize; i++) {
        free(priorityQueue[i]);
    }

    return 0;
}