#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

struct data {
    int id;
    char name[100];
    data *next;
    data *prev;
} *h, *c, *t, *now;

int count = 0;
int modeNum = 2;

char musik[50][100] {
    "Heidi Montag - Superficial",
    "ROSE & Bruno Mars - APT.",
    "Lady Gaga & Bruno Mars - Die With A Smile",
    "Teddy Swims & GIVĒON - Are You Even Real",
    "Morgan Wallen - Smile",
    "Pastor Mike Jr. - Amen",
    "Heidi Montag - I'll Do It",
    "Shaboozey - A Bar Song (Tipsy)",
    "Teddy Swims - Lose Control",
    "Morgan Wallen - Love Somebody",
    "Lola Young - Messy",
    "Dean Lewis - With You",
    "Billie Eilish - BIRDS OF A FEATHER",
    "Teddy Swims - The Door",
    "Disturbed - The Sound of Silence (CYRIL Remix)",
    "Jelly Roll - I Am Not Okay",
    "Gracie Abrams - Thats So True",
    "Heidi Montag - Go Harder",
    "Bad Bunny - DtMF",
    "Chappell Roan - Pink Pony Club"
};

void printMenu();
void enterToContinue();

void push(char name[]);

void view(data *temp);
void addSong();
void mode();
void previous();
void next();

int main() {
    do {
        int input;
        printMenu();
        do {
            printf(">> ");
            scanf("%d", &input); gc
        } while (input < 1 || input > 6);

        switch (input) {
            case 1:
                addSong();
                break;
            case 2:
                mode();
                break;
            case 3:
                previous();
                break;
            case 4:
                next();
                break;
            case 5:
                view(h);
                break;
            case 6:
                enterToContinue();
                return 0;
        }
    } while (1);
}

void printMenu() {
    system("clear");
    puts("SpoDiddy");
    if (now != NULL) printf("Now Playing : %s\n", now->name);
    if (modeNum == 1) printf("Mode : Loop\n\n");
    else printf("Mode : Play Once\n\n");
    puts("1. Add Song");
    puts("2. Mode");
    puts("3. Previous Song");
    puts("4. Next Song");
    puts("5. View List");
    puts("6. Exit");
}

void enterToContinue() {
    printf("Press ENTER To Continue..."); gc
}

void push(char name[]) {
    c = (data*)malloc(sizeof(data));

    strcpy(c->name, name);
    c->id = count + 1;
    c->next = NULL;
    c->prev = NULL;

    if (!h) {
        h = t = c;
    } else {
        t->next = c;
        c->prev = t;
        t = c;
    }
}

void view(data *temp) {
    if (temp == NULL) {
        puts("There is no song");
        enterToContinue();
        return;
    }

    // t->next = NULL;
    // h->prev = NULL;
    

    while (temp != NULL) {
        printf("%d. %s\n", temp->id, temp->name);
        temp = temp->next;
    }

    // if (modeNum == 1) {
    //     t->next = h;
    //     h->prev = t;
    // }
    enterToContinue();
}

void addSong() {
    for (int i = 0; i < 20; i++) {
        printf("%d. %s\n", i + 1, musik[i]);
    }
    printf("\n");

    if (modeNum == 1) {
        t->next = NULL;
        h->prev = NULL;
    }

    int input;
    do {
        printf("Input number you want to add : ");
        scanf("%d", &input); gc
    } while (input < 1 || input > 20);

    input--;
    push(musik[input]);
    puts("Song has been succesfully added");
    count++; 
    if (h == t) now = h;

    if (modeNum == 1) {
        t->next = h;
        h->prev = t;
    }
    enterToContinue();
}

void mode() {
    if (h == NULL) {
        puts("There is no song");
        enterToContinue();
        return;
    }

    puts("1. Loop");
    puts("2. Play Once");

    do {
        printf(">> ");
        scanf("%d", &modeNum); gc
    } while (modeNum < 0 || modeNum > 2);

    if (modeNum == 1) {
        t->next = h;
        h->prev = t;
    }
    puts("Mode has been changed");
    enterToContinue();
}

void previous() {
    if (h == NULL) {
        puts("There is no song");
        enterToContinue();
        return;
    }

    if (now == h && modeNum == 2) {
        return;
    }

    now = now->prev;
}

void next() {
    if (h == NULL) {
        puts("There is no song");
        enterToContinue();
        return;
    }
    
    if (now == t && modeNum == 2) {
        return;
    }

    now = now->next; 
}