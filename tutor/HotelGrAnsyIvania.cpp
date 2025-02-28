#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define HASH_SIZE 100
#define gc getchar();

struct Booking {
    char name[35];
    char phoneNum[20];
    int age;
    char roomType[10];
    int stayDuration;
    char bookingID[7];
    Booking* next;
}*bookings[HASH_SIZE];

Booking* createBooking(char* name, char* phoneNum, int age, char* roomType, int stayDuration) {
    Booking* newBooking = (Booking*)malloc(sizeof(Booking));
    strcpy(newBooking->name, name);
    strcpy(newBooking->phoneNum, phoneNum);
    newBooking->age = age;
    strcpy(newBooking->roomType, roomType);
    newBooking->stayDuration = stayDuration;
    strcpy(newBooking->bookingID, generateID(roomType));

    newBooking->next = NULL;

    return newBooking;
}

void pushHash(Booking* c) {
    int key = getHashKeyMidSquare(c->bookingID);
    if (bookings[key] == NULL) {
        bookings[key] = c;
    } else {
        Booking* temp = bookings[key];
        while (temp != NULL && temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = c;
    }
}

void pop(char* id) {
    int key = getHashKeyMidSquare(id);

    Booking* c = bookings[key];
    if (bookings[key] == NULL) {
        puts("Not found!");
        return;
    } else if (strcmp(c->bookingID, id) == 0) {
        bookings[key] = NULL;
        free(c);
        return;
    }
    else {
        Booking* temp = bookings[key];
        while (temp != NULL && strcmp(temp->next->bookingID, id) != 0) {
            temp = temp->next;
        }
        Booking* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        return;
    }

    puts("Data not found");
}

void view() {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (bookings[i] == NULL) continue;

        Booking* temp = bookings[i];
        while (temp != NULL) {
            printf("Name ; %s\n", temp->name);
            temp = temp->next;
        }
    }
}

void printMenu();
void enterToContinue();
char* generateID(char* roomType);
int getHashKeyMidSquare(char* id);

int main() {
    srand(time(0));
    char id[100];
    strcpy(id, "56787345");
    int hash = getHashKeyMidSquare(id);
    printf("%d\n", hash);
    // do {
    //     int inp = -1;
    //     printMenu();
        
    //     do {
    //         printf(">> ");
    //         scanf("%d", &inp);
    //     } while (inp < 1 || inp > 4);
    // } while (1);
    return 0;
}

void printMenu() {
    system("clear");
    puts("+--------------------+");
    puts("| Hotel GrAnsylvania |");
    puts("+--------------------+");
    puts("1. Booking Hotel");
    puts("2. View Bookings");
    puts("3. Delete Bookings");
    puts("4. Exit");
}

void enterToContinue() {
    printf("Press ENTER To Continue..."); gc
}

char* generateID(char* roomType) {
    char* id = (char*)malloc(sizeof(7));
    sprintf(id, "%c%c%d%d%d", toupper(roomType[0]), toupper(roomType[1]), rand() % 10, rand() % 10, rand() % 10);
    return id;
}
 
// Mid Square
int getHashKeyMidSquare(char* id) {
    /*
    1. Jumlahin semuanya di sum
    2. Kuadratin
    3. Ambil tengahnya
    4. Kalo ganjil banyak digitnya, lansung aja ambil tengahnya
    5. Kalo genap, ambil tengahnya sama sbeelah kanannya
    1234 = 23
    12345 = 3
    */
    int sumID = 1;
    for (int i = 2; i < 5; i++) {
        sumID *= id[i] - '0';
    }

    sumID *= sumID; // Kuadratin
    // sumID = 568
    char string[100000];
    sprintf(string, "%d", sumID); // Convert ke string

    int l = strlen(string);
    int key = 0; // Isinya si tengah
    if (l % 2 == 1) {
        key = string[l / 2] - '0';
    } else {
        // 56787345
        char mid[3] = {string[l / 2 - 1], string[l / 2], '\0'};
        key = atoi(mid);
    }

    return key % HASH_SIZE;
}

