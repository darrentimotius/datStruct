#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();

struct data {
    int id = 0;
    char title[100];
    int quantity;
};

data* dat = (data*)malloc(sizeof(data));

int bookCount = 0;

void printMenu();
void enterToCont();

void add();
void borrow();
void del();
void view();

int main() {
    do {
        int inp = -1;
        printMenu();

        do {
            printf(">> ");
            scanf("%d", &inp); gc
        } while (inp < 0 || inp > 5);

        switch (inp) {
            case 1 :
                add();
                break;
            case 2 :
                borrow();
                break;
            case 3 :
                del();
                break;
            case 4 :
                view();
                break;
            case 5 :
                enterToCont();
                return 0;
        }
    } while (1);
    return 0;
}

void printMenu() {
    system("clear");
    puts("SUNIB University Library");
    puts("1. Add Book");
    puts("2. Borrow Book");
    puts("3. Delete Stock");
    puts("4. Book List");
    puts("5. Exit");
}

void enterToCont() {
    printf("Press ENTER to continue..."); gc
}

void add() {
    // Book Name
    printf("Input book title : ");
    scanf("%[^\n]", dat[bookCount].title); gc

    // Book Quantity
    printf("Input book quantity : ");
    scanf("%d", &dat[bookCount].quantity); gc

    puts("Book has been successfully added");
    dat[bookCount].id++;
    bookCount++;
    enterToCont();
}

void view() {
    for (int i = 0; i < bookCount; i++) {
        printf("ID : %d\n", dat[i].id);
        printf("Title : %s\n", dat[i].title);
        printf("Quantity : %d\n", dat[i].quantity);
        puts("=====================");
    }
    enterToCont();
}

void borrow() {
    if (bookCount == 0) {
        puts("There is no book");
        enterToCont();
        return;
    }
    view();
    char validation[100];
    do {
        printf("Choose between id or title [id / title] : ");
        scanf("%s", validation); gc
    } while (strcmp(validation, "id") != 0 && strcmp(validation, "title") != 0);

    int idx = -1;
    if (strcmp(validation, "title") == 0) {
        do {
            char temp[100];
            printf("Input book title : ");
            scanf("%[^\n]", temp); gc

            for (int i = 0; i < bookCount; i++) {
                if (strcmp(temp, dat[i].title) == 0) {
                    idx = i;
                    break;
                }
            }
        } while (idx == -1);
    } else {
        do {
            printf("Input book id : ");
            scanf("%d", &idx); gc
            idx --;
        } while (idx < 0 || idx > bookCount);
    }
    
    puts("Book has been successfully borrowed");
    dat[idx].quantity--;
    enterToCont();
}

void del() {
    if (bookCount == 0) {
        puts("There is no book");
        enterToCont();
        return;
    }
    view();
    int temp;
    do {
        printf("Input book id : ");
        scanf("%d", &temp); gc
        temp--;
    } while (temp < 0 || temp > bookCount);

    for (int i =- 0; i < bookCount - 1; i++) {
        dat[i] = dat[i + 1];
    }
    bookCount--;
    puts("Book has been succesfully deleted");
    enterToCont();
}
