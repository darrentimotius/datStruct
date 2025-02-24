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

// Main Menu Functions
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

// Hashing Function
int getHashKey(char* id) {
    int x = 0;
    for (int i = 2; i < 5; i++) {
        x += id[i] - '0';
    }

    return (x - 1) % HASH_SIZE;
}

char* generateID(char* roomType) {
    char* id = (char*)malloc(sizeof(char) * 7);
    sprintf(id, "%c%c%d%d%d", toupper(roomType[0]), toupper(roomType[1]), rand() % 10, rand() % 10, rand() % 10);
    return id;
}

// Chaining Functions
Booking *newBooking(char* name, char* phoneNum, int age, char* roomType, int stayDuration) {
    char* bookingID = generateID(roomType);

    Booking* c = (Booking*)malloc(sizeof(Booking));
    strcpy(c->name, name);
    strcpy(c->phoneNum, phoneNum);
    c->age = age;
    strcpy(c->roomType, roomType);
    c->stayDuration = stayDuration;
    strcpy(c->bookingID, bookingID);
    c->next = NULL;

    return c;
}

void pushTail(Booking *c) {
    int key = getHashKey(c->bookingID);

    if (bookings[key] == NULL) {
        bookings[key] = c;
    } else {
        Booking* temp = bookings[key];

        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = c;
    }
}

bool pop(char* bookingID) {
    int key = getHashKey(bookingID);

    Booking* c = bookings[key];

    if (c == NULL) return false;

    if (strcmp(c->bookingID, bookingID) == 0) {
        Booking* temp = bookings[key];
        bookings[key] = temp->next;
        free(temp);
        return true;
    } else {
        Booking* temp = bookings[key];
        while (strcmp(temp->next->bookingID, bookingID) != 0) {
            temp = temp->next;
        }
        Booking* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        return true;
    }
}

// Validation Functions
bool validName(char* name) {
    int l = strlen(name);
    return l >= 3 && l <= 30;
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
    return strcmp(roomType, "Regular") == 0 || strcmp(roomType, "Deluxe") == 0 || strcmp(roomType, "Suite") == 0;
}

bool validStayDuration(int stayDuration) {
    return stayDuration >= 1 && stayDuration <= 30;
}

// Main Function
void createBooking() {
    system("clear");
    char name[35];
    char phoneNum[20];
    int age;
    char roomType[10];
    int stayDuration;

    do {
        printf("Input Full Name [3..30] : ");
        scanf("%[^\n]", name); gc

        if (!validName(name)) puts("Full name length must be between 3 and 30");
    } while (!validName(name));

    do {
        printf("Input Phone Number : ");
        scanf("%[^\n]", phoneNum); gc

        if (!validPhoneNum(phoneNum)) puts("Phone number must be begin with '+62', contains with at least 1 space and the length must be 11 (Exclude +62 and space)");
    } while (!validPhoneNum(phoneNum));

    do {
        printf("Input Age [Minimum 18] : ");
        scanf("%d", &age); gc

        if (!validAge(age)) puts("Age must be minimum 18");
    } while (!validAge(age));

    do {
        printf("Input Room Type [Regular | Deluxe | Suite] (Case Sensitive) : ");
        scanf("%[^\n]", roomType); gc

        if (!validRoomType(roomType)) puts("Room type must be either Regular or Deluxe or Suite (Case Sensitive)");
    } while (!validRoomType(roomType));

    do {
        printf("Input How Many Night You Will Stay [1..30] : ");
        scanf("%d", &stayDuration); gc

        if (!validStayDuration(stayDuration)) puts("You can't stay less than 1 night or more than 30 nights");
    } while (!validStayDuration(stayDuration));
    
    Booking* c = newBooking(name, phoneNum, age, roomType, stayDuration);
    pushTail(c);

    system("clear");

    printf("Booking ID = %s\n", c->bookingID);
    puts("==================");
    printf("Full Name : %s\n", c->name);
    printf("Phone Number : %s\n", c->phoneNum);
    printf("Room Type : %s\n", c->roomType);
    printf("Night Stay : %d night(s)\n", c->stayDuration);
    puts("");

    enterToContinue();
}

bool viewBooking() {
    system("clear");
    bool found = false;

    for (int i = 0; i < HASH_SIZE; i++) {
        Booking* temp = bookings[i];
        while (temp != NULL) {
            found = true;
            printf("Booking ID = %s\n", temp->bookingID);
            puts("==================");
            printf("Full Name : %s\n", temp->name);
            printf("Phone Number : %s\n", temp->phoneNum);
            printf("Room Type : %s\n", temp->roomType);
            printf("Night Stay : %d night(s)\n", temp->stayDuration);
            puts("");
            puts("=========================");
            puts("");

            temp = temp->next;
        }
    }
    if (!found) puts("There is no booking !");

    enterToContinue();
    return found;
}

void deleteBooking() {
    if(!viewBooking()) return;

    char bookingID[7];
    printf("Input Booking ID (Case Sensitive) : ");
    scanf("%[^\n]", bookingID); gc

    system("clear");
    if(pop(bookingID)) {
        printf("BookingID %s is Successfully Deleted !\n", bookingID);
    } else {
        puts("Failed to Delete, There is No Data !");
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
        } while (inp < 1 || inp > 4);
        
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
            case 4 :
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}