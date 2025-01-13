#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define gc getchar();

struct data {
    int id;
    char name[100];
    int price ;
    data *next;
} *h, *c, *t;

int count = 0;

void printMenu();
void enterToContinue();

void pushMid(char name[]);
void pop(char name[]);

void sellCard();
void buyCard();
void changeCard();
void viewCard(data *h);

int main() {
    srand(time(0));
    pushMid("Vulpix");
    pushMid("Diglett");
    pushMid("Zubat");
    pushMid("Nidoran");

    do {
        int input;
        printMenu();
        do {
            printf(">> ");
            scanf("%d", &input); gc
        } while (input < 1 || input > 5);

        // printf("%d\n", count);
        switch (input) {
            case 1 :
                sellCard();
                break;
            case 2 :
                buyCard();
                break;
            case 3 :
                changeCard();
                break;
            case 4 :
                viewCard(h);
                break;
            case 5 :
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}

void printMenu() {
    system("clear");
    // puts("Card Exchange");
    puts("   _____              _   ______          _                            ");
    puts("  / ____|            | | |  ____|        | |                           ");
    puts(" | |     __ _ _ __ __| | | |__  __  _____| |__   __ _ _ __   __ _  ___ ");
    puts(" | |    / _` | '__/ _` | |  __| \\ \\/ / __| '_ \\ / _` | '_ \\ / _` |/ _ \\");
    puts(" | |___| (_| | | | (_| | | |____ >  < (__| | | | (_| | | | | (_| |  __/");
    puts("  \\_____\\__,_|_|  \\__,_| |______/_/\\_\\___|_| |_|\\__,_|_| |_|\\__, |\\___|");
    puts("                                                             __/ |     ");
    puts("                                                            |___/      ");
    puts("1. Sell Card");
    puts("2. Buy Card");
    puts("3. Change Card");
    puts("4. View Card");
    puts("5. Exit");
}

void enterToContinue() {
    printf("Press ENTER to continue..."); gc
}

void pushMid(char name[]) {
    c = (data*)malloc(sizeof(data));

    strcpy(c->name, name);
    c->id = rand() % 1000;
    c->price = 100;
    c->next = NULL;

    if (!h) {
        h = t = c;
    } else if (strcmp(name, h->name) < 0) {
        c->next = h;
        h = c;
    } else if (strcmp(name, t->name) > 0) {
        t->next = c;
        t = c;
    } else {
        data *temp = h;
        while (strcmp(temp->next->name, name) < 0) {
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

void pop(char name[]) {
    if (h == NULL) {
        return;
    }

    if (strcmp(name, h->name) == 0) {
        data *temp = h;
        h = h->next;
        free(temp);
    } else {
        data *temp1 = h;
        data *temp2 = h->next;

        while (strcmp(temp2->name, name) != 0) {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }
}

void viewCard(data *h) {
    if (h == NULL) {
        puts("There is no card");
        enterToContinue();
        return;
    }
    while (h != NULL) {
        printf("ID : %03d\n", h->id);
        printf("Name : %s\n", h->name);
        printf("Price : %d\n", h->price);
        h = h->next;
        puts("========================");
    }
    enterToContinue();
}

void buyCard() {
    viewCard(h);
    if (h == NULL) return;

    char name[100];
    printf("Input card name : ");
    scanf("%[^\n]", name); gc

    pushMid(name);

    puts("Card has been succesfully bought");
    count++;
    enterToContinue();
}

void sellCard() {
    viewCard(h);
    if (h == NULL) return;

    char name[100];
    printf("Input card name : ");
    scanf("%[^\n]", name); gc

    int found = -1;
    data *temp = h;
    while (temp != NULL) {
        if (strcmp(name, temp->name) == 0) {
            found = 1;
            break;
        } else temp = temp->next;
    }

    if (found == 1) {
        pop(name);
        count--;
    } else {
        puts("There is no card");
        enterToContinue();
        return;
    }
    puts("Card has been succesfully sold");
    enterToContinue();
}

void changeCard() {
    viewCard(h);
    if (h == NULL) return;

    char name1[100], name2[100];
    printf("Input card name before : ");
    scanf("%[^\n]", name1); gc

    int found = -1;
    data *temp = h;
    while (temp != NULL) {
        if (strcmp(name1, temp->name) == 0) {
            found = 1;
            break;
        } else temp = temp->next;
    }

    if (found == 1) {
        pop(name1);
    } else {
        puts("There is no card");
        enterToContinue();
        return;
    }

    printf("Input card name after : ");
    scanf("%[^\n]", name2); gc

    pushMid(name2);
    puts("Card has been succesfully changed");
    enterToContinue();
}