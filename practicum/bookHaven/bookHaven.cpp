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

int hashKey(char* id) {
    char idTemp[5] = {id[2], id[3], id[4], '\0'};
    
    // long long int idInt = atoi(idTemp);
    long long int idInt = atoi(&id[2]);
    idInt *= idInt;

    char square[100];
    sprintf(square, "%lld", idInt);

    int l = strlen(square);

    int key = 0;
    if (l % 2 == 1) {
        key = square[l / 2] - '0';
    } else {
        char mid[3] = {square[l / 2 - 1], square[l / 2], '\0'};
        key = atoi(mid);
    }

    return key % TABLE_SIZE;
}

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

void push(Node* c) {
    int key = hashKey(c->borrowingID);
    if (hash[key] == NULL) {
        hash[key] = c;
    } else {
        Node* temp = hash[key];
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = c;
    }
}

void enterToContinue() {
    printf("Press ENTER To Continue..."); gc
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
    
    int flagNum = 0;
    do {
        printf("Enter your library ID (format: LIB-xxxxx): ");
        scanf("%[^\n]", libraryID); gc

        for (int i = 4; i < 9; i++) {
            if (isdigit(libraryID[i]) != 0) flagNum = 1;
            else flagNum = 0;
        }

        if (libraryID[0] != 'L' || libraryID[1] != 'I' || libraryID[2] != 'B' || libraryID[3] != '-' || flagNum == 0 || strlen(libraryID) != 9)
            puts("Input must start with \"LIB-\" followed by exactly 5 digits");
    } while (libraryID[0] != 'L' || libraryID[1] != 'I' || libraryID[2] != 'B' || libraryID[3] != '-' || flagNum == 0 || strlen(libraryID) != 9);

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
    
    enterToContinue();
}

void viewBook() {
    // system("clear");
    system("cls");
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash[i] != NULL) {
            found = 1;
            Node* temp = hash[i];
            printf("Borrowing ID : %s\n", temp->borrowingID);
            printf("Borrower Name : %s\n", temp->name);
            printf("Library ID : %s\n", temp->libraryID);
            printf("Book Title : %s\n", temp->bookTitle);
            printf("Duration : %d\n", temp->duration);
            puts("=============================");
        }
    }
    if (found == 0) puts("No books borrowed yet");

    enterToContinue();
}

void returnBook() {
    // system("clear");
    system("cls");
	
	int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash[i] != NULL) {
            found = 1;
            Node* temp = hash[i];
            printf("Borrowing ID : %s\n", temp->borrowingID);
            printf("Borrower Name : %s\n", temp->name);
            printf("Library ID : %s\n", temp->libraryID);
            printf("Book Title : %s\n", temp->bookTitle);
            printf("Duration : %d\n", temp->duration);
            puts("=============================");
        }
    }
    
    if (found == 0) {
        puts("No books found");
        enterToContinue();
        return;
    }

    puts("");
    char borrowingID[10];
    printf("Enter Borrowing ID to return: ");
    scanf("%[^\n]", borrowingID); gc

    int key = hashKey(borrowingID);
    Node*c = hash[key];

    if (c == NULL) {
        // system("clear");
        system("cls");
        puts("No books found");
        enterToContinue();
        return;
    }

    if (strcmp(c->borrowingID, borrowingID) == 0) {
        hash[key] = NULL;
        free(c);
    } else {
        Node* temp = hash[key];
        while (temp->next != NULL && strcmp(temp->next->borrowingID, borrowingID) != 0) {
            temp = temp->next;
        }
        Node* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
    }

    // system("clear");
    system("cls");
    puts("Book Returned Succesfully!");
    printf("Borrowing ID : %s has been removed\n", borrowingID);
    enterToContinue();
}

void printMenu() {
    // system("clear");
    system("cls");
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
                system("cls");
                puts("Thank you for using our program...");
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}