#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define gc getchar();

struct Node {
    char address[100];
    char id[10];
    int type;
    char typeArr[10];
    Node *next;
}*h, *c, *t;

void printMenu() {
    system("clear");
    puts("Copi Xpress");
    puts("1. Insert new package");
    puts("2. Send a package");
    puts("3. View all package");
    puts("4. Exit");
}

void enterToContinue() {
    printf("Press ENTER To Continue..."); gc
}

void push(char* address, char* id, int type, char* typeArr) {
    c = (Node*)malloc(sizeof(Node));

    strcpy(c->address, address);
    strcpy(c->id, id);
    c->type = type;
    strcpy(c->typeArr, typeArr);
    c->next = NULL;

    if (h == NULL) {
        h = t = c;
    } else if (type > h->type) {
        c->next = h;
        h = c;
    } else if (t->type >= type) {
        t->next = c;
        t = c;
    } else {
        Node *temp = h;
        while (temp != NULL & temp->next->type >= type) {
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

char randomChar() {
    int decision = rand() % 2;
    if (decision == 0) {
        return rand() % 26 + 'A';
    } else {
        return rand() % 10 + '0';
    }
}

char* generateID() {
    char* id = (char*)malloc(sizeof(char) * 10);
    id[0] = 'C', id[1] = 'P', id[2] = 'X', id[3] = randomChar(), id[4] = randomChar(), id[5] = randomChar();

    return id;
}

bool validAddress(char* address) {
    if (address[0] != 'J' || address[1] != 'l' || address[2] != '.') return false;
    return strlen(address) >= 5 && strlen(address) <= 20;
}

bool validType(char* type) {
    return strcmp(type, "Economy") == 0 || strcmp(type, "Standard") == 0 || strcmp(type, "Instant") == 0;
}

void insertPackage() {
    char address[100];
    char id[10];
    char typeArr[12];
    int type;

    do {
        printf("Address (must start with \"Jl.\", 5-20 characters [inclusive]): ");
        scanf("%[^\n]", address); gc
    } while (!validAddress(address));

    do {
        printf("Package Type (Economy/Standard/Instant [case sensitive]): ");
        scanf("%[^\n]", typeArr); gc
    } while (!validType(typeArr));

    if (strcmp(typeArr, "Economy") == 0) type = 0;
    else if (strcmp(typeArr, "Standard") == 0) type = 1;
    else if (strcmp(typeArr, "Instant") == 0) type = 2;

    push(address, generateID(), type, typeArr);
    puts("Package inserted");
    enterToContinue();
}

void sendPackage() {
    if (h == NULL) {
        puts("No data");
        return;
    }

    Node* temp = h;
    printf("%s (%s) successfully sent to %s\n", temp->id, temp->typeArr, temp->address);
    h = h->next;
    free(temp);

    enterToContinue();
}

void viewPackage() {
    if (h == NULL) {
        puts("No data");
        enterToContinue();
    }

    Node* temp = h;
    while (temp != NULL) {
        printf("%s - %s - %s\n", temp->id, temp->typeArr, temp->address);
        temp = temp->next;
    }
    enterToContinue();
}

void exit() {
    while (h != NULL) {
        Node* temp = h;
        printf("%s (%s) successfully sent to %s\n", temp->id, temp->typeArr, temp->address);
        h = h->next;
        free(temp);
    }
    enterToContinue();
}

int main() {
    srand(time(NULL));
    do {
        int inp = -1;
        printMenu();

        do {
            printf(">> ");
            scanf("%d", &inp); gc
        } while (inp < 0 || inp > 4);

        switch (inp) {
            case 1 :
                insertPackage();
                break;
            case 2 :
                sendPackage();
                break;
            case 3 :
                viewPackage();
                break;1
                
            case 4 :
                exit();
                return 0;
        }
    } while (1);
    return 0;
}