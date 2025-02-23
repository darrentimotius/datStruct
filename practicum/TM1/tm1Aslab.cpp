#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

int getHashKey(char* id) {
    int x = 0;
    for (int i = 2; i < 5; i++) {
        x += id[i] - '0';
    }
    return (x - 1) % HASH_SIZE;
}

char toUpper(char x) {
    return 'a' <= x && x <= 'z' ? x - ('a' - 'A') : x;
}

char* generateId(char* roomType) {
    char* id = (char*)malloc(sizeof(char) * 7);
    for (int i = 0; i < 5; i++) {
        id[i] = i < 2 ? toUpper(roomType[i]) : rand() % 10 + '0';
    }
    id[5] = '\0';
    return id;
}

Booking* newBooking(char* name, char* phoneNum, int age, char* roomType, int stayDuration) {
    char* bookingID = generateId(roomType);

    Booking* curr = (Booking*)malloc(sizeof(Booking));
    strcpy(curr->name, name);
    strcpy(curr->phoneNum, phoneNum);
    curr->age = age;
    strcpy(curr->roomType, roomType);
    strcpy(curr->bookingID, bookingID);

    curr->next = NULL;
    
    return curr;
}

void pushTail(Booking* newData) {
    int hash = getHashKey(newData->bookingID);

    if(bookings[hash] == NULL) {
        bookings[hash] = newData;
    } else {
        Booking* curr = bookings[hash];
        while(curr->next) {
            curr = curr->next;
        }
        curr->next = newData;
    }
}

bool validFullName(char* name) {
    int l = strlen(name);
    return 3 <= l && l <= 30;
}

bool validPhoneNum(char* phoneNum) {
    if (phoneNum[0] != '+' || phoneNum[1] != '6' || phoneNum[2] != '2') return false;

    int space = 0;
    int l = strlen(phoneNum);
    for (int i = 3; i < l; i++) {
        if (phoneNum[i] == ' ') space++;
    }
    return space >= 1 && l - (space + 3) == 11;
}

bool validAge(int age) {
    return age >= 18;
}

bool validRoomType(char* roomType) {
    return strcmp(roomType, "Deluxe") == 0 ||
    strcmp(roomType, "Regular") == 0 ||
    strcmp(roomType, "Suite") == 0;
}

bool validStayDuration(int stayDuration) {
    return 1 <= stayDuration && stayDuration <= 30;
}

void createBooking() {
    char name[35];
    char phoneNum[20];
    int age;
    char roomType[10];
    int stayDuration;
    
    do {
        printf("Input name : ");
        scanf("%[^\n]", name); gc
    } while (!validFullName(name));
    
    do {
        printf("Input phone : ");
        scanf("%[^\n]", phoneNum); gc
    } while (!validPhoneNum(phoneNum));

    do {
        printf("Input age : ");
        scanf("%d", &age); gc
    } while (!validAge(age));

    do {
        printf("Input type : ");
        scanf("%[^\n]", roomType); gc
    } while (!validRoomType(roomType));

    do {
        printf("Input duration : ");
        scanf("%d", &stayDuration); gc
    } while (!validStayDuration(stayDuration));

    pushTail(newBooking(name, phoneNum, age, roomType, stayDuration));
}

bool viewBooking() {
    bool found = false;
    for (int i = 0; i < HASH_SIZE; i++) {
        Booking* curr = bookings[i];
        while(curr) {
            printf("ID : %s\n", curr->bookingID);
            curr = curr->next;
            found = true;
        }
    }

    if (!found) puts("Not Found!");
    return found;
}

bool pop(char* bookingID) {
    int hash = getHashKey(bookingID);
    Booking* curr = bookings[hash];

    if (curr == NULL) return false;

    if (strcmp(curr->bookingID, bookingID) == 0) {
        bookings[hash] = curr->next;
        free(curr);
        return true;
    } else {
        while (curr->next) {
            if (strcmp(curr->next->bookingID, bookingID) == 0) {
                Booking* temp = curr->next;
                curr->next = temp->next;
                free(temp);
                return true;
            }
            curr = curr->next;
        }
    }
}

void deleteBooking() {
    if(!viewBooking()) return;

    char bookingID[7];
    printf("Input Booking ID : ");
    scanf("%[^\n]", bookingID); gc

    if (pop(bookingID)) {
        printf("Deleted Booking %s\n", bookingID);
    } else {
        puts("ID Not Found!");
    }
}

int main() {
    srand(time(NULL));
    int inp = -1;
    do {
        puts("1. Insert");
        puts("2. View");
        puts("3. Delete");
        puts("4. Exit");
        printf(">> ");
        scanf("%d", &inp); gc

        switch(inp) {
            case 1 :
                createBooking();
                break;
            case 2 :
                viewBooking();
                break;
            case 3 :
                deleteBooking();
                break;
        }
    } while (inp != 4);

    return 0;
}