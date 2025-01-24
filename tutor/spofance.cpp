#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

int count = 0;
int modeNum = 2;

struct data {
    int id;
    char name[100];
    data *prev;
    data *next;
} *h, *c, *t, *now;

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

void view();
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
                view();
                break;
            case 6:
                enterToContinue();
                return 0;
        }
    } while (1);
}

void printMenu() {
    system("clear");
    puts("Fance's Music");
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

    c->id = count + 1;
    strcpy(c->name, name);
    c->next = NULL;
    c->prev = NULL;

    if (!h) {
        h = t = c;
    } else {
        // Push Tail
        t->next = c; // kiri ke kanan
        c->prev = t; // kanan ke kiri
        t = c;
    }
}

void view() {
    t->next = NULL; // Kiri ke kanan
    h->prev = NULL; // Kanan ke kiri

    data *temp = h;
    while (temp != NULL) { // Berhenti ketika ketemu NULL
        printf("%d. %s\n", temp->id, temp->name);
        temp = temp->next;
    }

    // Mode LOOP
    if (modeNum == 1) {
        t->next = h; // Kiri ke kanan
        h->prev = t; // Kanan ke kiri
    }
    enterToContinue();
}
void addSong() {
    // Nampilin list lagu
    for (int i = 0; i < 20; i++) {
        printf("%d. %s\n", i + 1, musik[i]);
    }

    // Validasi untuk mode LOOP (Putusin hubungan head sama tail)
    if (modeNum == 1) {
        t->next = NULL; // kiri ke kanan
        h->prev = NULL; // kanan ke kiri
    }

    int input = -1;
    do {
        printf("Input number you want to add : ");
        scanf("%d", &input); gc
    } while (input < 1 || input > 20);

    push(musik[input-1]);
    count++;

    if (h == t) {
        now = h;
    }

    // Validasi untuk mode LOOP (head terhubung sama tail)
    if (modeNum == 1) {
        t->next = h; // kiri ke kanan
        h->prev = t; // kanan ke kiri
    }

    puts("Song has been succefully added");
    enterToContinue();
}
void mode() {
    if (h == NULL) {
        puts("There is no song added");
        enterToContinue();
        return;
    }

    puts("1. Loop");
    puts("2. Play Once");

    printf(">> ");
    scanf("%d", &modeNum); gc

    // LOOP
    if (modeNum == 1) {
        t->next = h; // kiri ke kanan
        h->prev = t; // kanan ke kiri
    }

    puts("Mode has been changed");
    enterToContinue();
}
void previous() {
    // Play Once
    if (now->prev == NULL && modeNum == 1) {
        return;
    }
    // Loop
    now = now->prev;
}
void next() {
    // Play Once
    if (now->next == NULL && modeNum == 1) {
        return;
    }

    // Loop
    now = now->next;
}