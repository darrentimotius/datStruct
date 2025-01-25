#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

struct node {
    char name[100];
    int age;
    int status;
    node *next;
} *h, *c, *t;

void printMenu();
void enterToContinue();

void push();
void pop();

void add();
void dequeue();
void reset();
void view();

int main() {
    do {
        printMenu();
        int inp;

        do {
            printf(">> ");
            scanf("%d", &inp); gc
        } while (inp < 1 || inp > 4);

        switch (inp) {
            case 1:
                add();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                reset();
                break;
            case 4:
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}

void push(char name[], int age, int status) {
    c = (node*)malloc(sizeof(node));

    strcpy(c->name, name);
    c->age = age;
    c->status = status;
    c->next = NULL;

    if (!h) {
        h = t = c;
    } else if (status < h->status) {
        c->next = h;
        h = c;
    } else if (status >= t->status) {
        t->next = c;
        t = c;
    } else {
        node *temp = h;
        while (status >= temp->next->status) {
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

void view() {
    node *temp = h;

    if (temp == NULL) {
        printf("There is no patient\n\n");
        return;
    }

    int count = 1;
    while (temp != NULL) {
        printf("%d. Name : %s, Age : %d, Status : %d\n", count++, temp->name, temp->age, temp->status);
        temp = temp->next;
    }
    printf("\n");
}

void printMenu() {
    system("clear");
    puts("Hospital Priority Queue");
    view();
    puts("1. Add Patient");
    puts("2. Dequeue");
    puts("3. Reset Queue");
    puts("4. Exit");
}

void enterToContinue() {
    printf("Press ENTER to continue..."); gc
}

void add() {
    // Input name
    char name[100];
    printf("Input patient's name : ");
    scanf("%[^\n]", name); gc

    // Input age
    int age;
    printf("Input patient's age : ");
    scanf("%d", &age); gc

    // Input status
    char statusTemp[100];
    do {
        printf("Input patient's status [Low / Mid / High] : ");
        scanf("%s", statusTemp); gc
    } while (strcmp(statusTemp, "Low") != 0 && strcmp(statusTemp, "Mid") != 0 && strcmp(statusTemp, "High") != 0);

    int status;
    if (strcmp(statusTemp, "Low") == 0) status = 3;
    else if (strcmp(statusTemp, "Mid") == 0) status = 2;
    else status = 1;

    push(name, age, status);

    puts("Patient has been succesfully added to queue");
    enterToContinue();
}
void dequeue() {
    if (h == NULL) {
        puts("There is no queue");
        enterToContinue();
        return;
    }

    node *temp = h;
    h = h->next;
    free(temp);
}

void reset() {
    if (h == NULL) {
        puts("There is no queue");
        enterToContinue();
        return;
    }

    node *temp = h;
    node *del;
    while (temp != NULL) {
        del = temp;
        temp = temp->next;
        free(del);
    }
    h = t = NULL;
}