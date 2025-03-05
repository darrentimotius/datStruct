#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define TABLE_SIZE 100
#define gc getchar();

struct Node {
    char name[50];
    char libraryID[50];
    char borrowingID[50];
    char bookTitle[55];
    int duration;
    Node* next;
}*hash[TABLE_SIZE];

char* createID(char* bookTitle) {
    char* id = (char*)malloc(sizeof(char) * 7);
    sprintf(id, "%c%c%d%d%d", toupper(bookTitle[0]), toupper(bookTitle[1]), rand() % 10, rand() % 10, rand() % 10);

    return id;
}

Node* createNode(char* name, char* libraryID, char* bookTitle, int duration) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->name, name);
    strcpy(newNode->libraryID, libraryID);
    strcpy(newNode->bookTitle, bookTitle);
    strcpy(newNode->borrowingID, createID(bookTitle));
    newNode->duration = duration;
    newNode->next = NULL;

    return newNode;
}

int generateKey(char* id) {
    // HA440

    // 1. Ubah jadi angka
    char tempID[5] = {id[2], id[3], id[4], '\0'};
    // long long int numID = atoi(tempID);

    long long int numID = atoi(&id[2]);

    // 2. Kuadratin
    numID *= numID;

    // 3. Ubah jadi string
    char stringID[100];
    sprintf(stringID, "%lld", numID);

    // 4. Cari tengahnya
    int l = strlen(stringID);
    int key = 0;
    if (l % 2 == 0) {
        char mid[3] = {stringID[l / 2 - 1], stringID[l / 2], '\0'};
        key = atoi(mid);
    } else {
        key = stringID[l / 2] - '0';
    }

    return key % TABLE_SIZE;
}

void push(Node* c) {
    int key = generateKey(c->borrowingID);
    if (hash[key] == NULL) {
        hash[key] = c;
    } else {
        Node* temp = hash[key];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = c;
    }
}

void borrowBook() {
    // system("clear");
    system("cls");
    char name[50];
    char libraryID[50];
    char bookTitle[50];
    int duration;

    do {
        printf("Enter your full name: ");
        scanf("%[^\n]", name); gc
        
        if (strlen(name) < 3 || strlen(name) > 30) puts("Input must be between 3 and 30 characters");
    } while (strlen(name) < 3 || strlen(name) > 30);
    
    int flagNum = 1;
    do {
        flagNum = 1;
        // LIB-12345
        printf("Enter your library ID (format: LIB-xxxxx): ");
        scanf("%[^\n]", libraryID); gc

        // LIB-1abcd
        for (int i = 4; i < 9; i++) {
            if (!isdigit(libraryID[i])) {
                flagNum = 0;
                break;
            }
        }
    } while (flagNum == 0 || libraryID[0] != 'L' || libraryID[1] != 'I' || libraryID[2] != 'B' || libraryID[3] != '-' || strlen(libraryID) != 9);

    do {
        printf("Enter the book title: ");
        scanf("%[^\n]", bookTitle); gc

        if (strlen(bookTitle) < 3 || strlen(bookTitle) > 30) puts("Book Title must be between 3 and 30 characters");
    } while (strlen(bookTitle) < 3 || strlen(bookTitle) > 30);

    do {
        printf("Enter borrowing duration (1-30 days): ");
        scanf("%d", &duration); gc

        if (duration < 1 || duration > 30) puts("Borrowing duration must be between 1 and 30 days");
    } while (duration < 1 || duration > 30);

    Node* newBooking = createNode(name, libraryID, bookTitle, duration);
    push(newBooking);

    // system("clear");
    system("cls");
    puts("Book Borrowed Successfully!");
    printf("Borrowing ID : %s\n", newBooking->borrowingID);
    printf("Borrower Name : %s\n", newBooking->name);
    printf("Library ID : %s\n", newBooking->libraryID);
    printf("Book Title : %s\n", newBooking->bookTitle);
    printf("Duration : %d\n", newBooking->duration);
}

void viewBook() {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash[i] != NULL) {
            Node* temp = hash[i];
            printf("Borrowing ID : %s\n", temp->borrowingID);
            printf("Borrower Name : %s\n", temp->name);
            printf("Library ID : %s\n", temp->libraryID);
            printf("Book Title : %s\n", temp->bookTitle);
            printf("Duration : %d\n", temp->duration);
            puts("======================");
            found = 1;
        }
    }

    if (found == 0) puts("No books borrowed yet");
}

void returnBook() {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash[i] != NULL) {
            Node* temp = hash[i];
            printf("Borrowing ID : %s\n", temp->borrowingID);
            printf("Borrower Name : %s\n", temp->name);
            printf("Library ID : %s\n", temp->libraryID);
            printf("Book Title : %s\n", temp->bookTitle);
            printf("Duration : %d\n", temp->duration);
            puts("======================");
            found = 1;
        }
    }

    if (found == 0) {
        puts("No books borrowed yet");
        return;
    }

    char borrowingID[100];
    printf("Enter borrowing ID to return: ");
    scanf("%[^\n]", borrowingID); gc

    int key = generateKey(borrowingID);
    int flag = 0;
    Node* temp = hash[key];
    if(temp == NULL) {
        puts("No books found");
        return;
    } else if (strcmp(borrowingID, temp->borrowingID) == 0) {
        hash[key] = temp->next;
        free(temp);
        flag = 1;
    } else {
        while (temp->next != NULL && strcmp(temp->next->borrowingID, borrowingID) != 0) {
            temp = temp->next;
        }
        Node* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        flag = 1;
    }

    if (flag == 0) {
        puts("No books found");
        return;
    }

    puts("Book returned succesfully");
    printf("Borrowing ID : %s has been removed\n", borrowingID);
}

void printMenu() {
    // system("clear");
    // system("cls");
    puts("  _                 _    _    _                       ");
    puts(" | |               | |  | |  | |                      ");
    puts(" | |__   ___   ___ | | _| |__| | __ ___   _____ _ __  ");
    puts(" | '_ \\ / _ \\ / _ \\| |/ /  __  |/ _` \\ \\ / / _ \\ '_ \\ ");
    puts(" | |_) | (_) | (_) |   <| |  | | (_| |\\ V /  __/ | | |");
    puts(" |_.__/ \\___/ \\___/|_|\\_\\_|  |_|\\__,_| \\_/ \\___|_| |_|");
    puts("");
    puts("1. Borrow a Book");
    puts("2. View Borrowed Books");
    puts("3. Return a Book");
    puts("4. Exit");
}

int main() {
    srand(time(0));
    do {
        int inp = -1;
        printMenu();
        do {
            printf("Enter yout choice: ");
            scanf("%d", &inp); gc
        } while (inp < 1 || inp > 4);

        switch (inp) {
            case 1:
                borrowBook();
                break;
            case 2:
                viewBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                // system("clear");
                // system("cls");
                puts("Thank you for using our program...");
                // enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}