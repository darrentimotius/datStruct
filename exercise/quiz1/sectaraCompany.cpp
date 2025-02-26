#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 10

struct Node {
    int id;
    int priority;
    char severity[100];
    Node* next;
}*hash[SIZE], *h, *t;

Node* createNode(int id, bool impact, bool likelihood) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;

    if (impact && likelihood) {
        strcpy(newNode->severity, "Critical");
        newNode->priority = 0;
    } else if (impact && !likelihood) {
        strcpy(newNode->severity, "High");
        newNode->priority = 1;
    } else if (!impact && likelihood) {
        strcpy(newNode->severity, "Medium");
        newNode->priority = 2;
    } else {
        strcpy(newNode->severity, "Low");
        newNode->priority = 3;
    }
    newNode->next = NULL;

    return newNode;
}

void push(int id, bool impact, bool likelihood) {
    Node* c = createNode(id, impact, likelihood);

    if (h == NULL) {
        h = t = c;
    } else if (c->priority > t->priority) {
        t->next = c;
        t = c;
    } else if (c->priority < h->priority) {
        c->next = h;
        h = c;
    } else {
        Node* temp = h;
        while (temp != NULL && temp->next->priority <= c->priority) {
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

void printData() {
    Node* temp = h;
    puts("Vulnerability Queue");
    while (temp != NULL) {
        printf("ID: %d - %s\n", temp->id, temp->severity);
        temp = temp->next;
    }
}

int getHashKey(int id) {
    return id % SIZE;
}

void pushHash(Node* data) {
    int key = getHashKey(data->id);

    if (hash[key] == NULL) {
        hash[key] = data;
    } else {
        Node* temp = hash[key];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = data;
    }
}

void dequeue() {
    Node* temp = h;
    h = h->next;

    temp->next = NULL;
    pushHash(temp);
}

void printHashData() {
    puts("Stored Processed Vulnerabilities:");
    for (int i = 0; i < SIZE; i++) {
        Node* temp = hash[i];
        while (temp != NULL) {
            printf("Index %d -> ID: %d\n", i, temp->id);
            temp = temp->next;
        }
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        int id, temp1, temp2;
        bool impact, likelihood;
        scanf("%d,%d,%d", &id, &temp1, &temp2);

        impact = temp1, likelihood = temp2;

        push(id, impact, likelihood);
    }

    printData();

    dequeue();
    dequeue();

    puts("");
    printData();
    
    puts("");
    puts("Processing vulnerabilities...");

    puts("");
    printHashData();

    return 0;
}