#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define gc getchar();

struct data {
    int id;
    char name[100];
    int price;
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
void viewCard();

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
                viewCard();
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

    c->id = rand() % 100;
    strcpy(c->name, name);
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
        /*
        Double Linked List tambahin 2 baris ini
        temp->next->prev = c;
        c->prev = temp;
        */
        temp->next = c;
    }
}

void pop(char name[]) {
    if (!h) {
        return;
    } else if (strcmp(h->name, name) == 0) { // Pop Head
        data *temp = h;
        h = h->next;
        temp->next = NULL;
        free(temp);
    } else {
        data *temp1 = h;
        data *temp2 = h->next;

        // Kalo belum ketemu
        while (strcmp(temp2->name, name) != 0) {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        // Kalo udah ketemu
        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }
}

void buyCard() {
    viewCard();
    char name[100];
    do {
        printf("Enter card name : ");
        scanf("%s", name); gc
    } while (strcmp(name, "Rattata") != 0 && strcmp(name, "Squirtle") != 0
            && strcmp(name, "Charmander") != 0 &&
            strcmp(name, "Pikachu") != 0 && strcmp(name, "Nidoran") != 0);

    // Cek kartunya ada ato ga
    int found = -1;
    data *temp = h;
    while (temp != NULL) {
        if (strcmp(name, temp->name) == 0) {
            found = 1;
            break;
        } else {
            temp = temp->next;
        }
    }

    if (found == 1) {
        puts("Card has been bought before");
        enterToContinue();
        return;
    } else {
        pushMid(name);
        count++;
        puts("Card has been bought");
        enterToContinue();
    }
}

void sellCard() {
    if (!h) {
        puts("There is no card");
        return;
    }

    viewCard();

    char name[100];
    printf("Input card name : ");
    scanf("%s", name); gc

    int found = -1;
    data *temp = h;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            found = 1;
            break;
        } else {
            temp = temp->next;
        }
    }

    if (found == -1) {
        puts("Card not found");
        enterToContinue();
        return;
    } else {
        pop(name);
        count--;
        puts("Card has been succesfully sold");
        return;
    }
}

void viewCard() {
    data *temp = h;
    while (temp != NULL) {
        printf("ID : %03d\n", temp->id);
        printf("Name : %s\n", temp->name);
        printf("Price : %d\n", temp->price);
        puts("====================");
        temp = temp->next;
    }
    enterToContinue();
}

void changeCard() {
    viewCard();
    
    char name1[100], name2[100];
    // Kartu pertama (harus udah kita punya)
    printf("Input first card : ");
    scanf("%s", name1); gc

    int found = -1;
    data *temp = h;
    while (temp != NULL) {
        if (strcmp(temp->name, name1) == 0) {
            found = 1;
            break;
        } else {
            temp = temp->next;
        }
    }

    if (found == -1) {
        puts("Card not found");
        enterToContinue();
        return;
    }

    // Kartu kedua (harus yang boleh ditambah)
    do {
        printf("Input second card : ");
        scanf("%s", name2); gc
    } while (strcmp(name2, "Rattata") != 0 &&
            strcmp(name2, "Squirtle") != 0 &&
            strcmp(name2, "Charmander") != 0 &&
            strcmp(name2, "Pikachu") != 0 &&
            strcmp(name2, "Nidoran") != 0);

    pop(name1);
    pushMid(name2);
    puts("Card has been succesfully changed");
    enterToContinue();
}

/*
5 10 NULL
h t

4 5 10 NULL
c   t 
h

4    5 10 20 NULL
h       t c
temp
*/