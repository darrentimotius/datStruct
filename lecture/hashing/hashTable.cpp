#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100
#define gc getchar();

struct data {
    char name[100];
    char phone[100];
    char email[100];
    data *next;
}*h[max], *c;

void printMenu();
void enterToContinue();

int hash(char *name);
void push(char *name, char *phone, char *email);

void insert();
void search();
void del();
void view();

int main() {
    do {
        int inp = -1;
        printMenu();
        do {
            printf(">> ");
            scanf("%d", &inp); gc
        } while (inp < 1 || inp > 5);

        switch (inp) {
            case 1:
                insert();
                break;
            case 2:
                search();
                break;
            case 3:
                del();
                break;
            case 4:
                view();
                break;
            case 5:
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}

void printMenu() {
    system("clear");
    puts("Hash Table");
    puts("1. Insert");
    puts("2. Search");
    puts("3. Delete");
    puts("4. View");
    puts("5. Exit");
}

void enterToContinue() {
    printf("Press ENTER to continue..."); gc
}

int hash(char *name) {
    int key = 0;

    int ascii = 0;
    for (int i = 0; i < strlen(name); i++) {
        ascii += name[i];
    }
    int a = ascii * ascii;

    char temp[100];
    sprintf(temp, "%d", a);

    int len = strlen(temp);
    if (len % 2 == 1) {
        char mid[2] = {temp[len / 2], '\0'};
        key = atoi(mid);
        // key = a * a;
    } else {
        char mid[3] = {temp[(len / 2) - 1], temp[len / 2], '\0'};
        key = atoi(mid);
        // key = a * a;
    }
    return key % max;
}

void push(char *name, char *phone, char *email) {
    c = (data*)malloc(sizeof(data));
    strcpy(c->name, name);
    strcpy(c->phone, phone);
    strcpy(c->email, email);
    c->next = NULL;

    int pos = hash(name);

    // kalo belum ada data satupun
    if (h[pos] == NULL) {
        h[pos] = c;
        return;
    }

    // push tail
    data *temp = h[pos];
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = c;
}

void insert() {
    int flag = -1;
    char name[100];

    printf("Input name : ");
    scanf("%[^\n]", name); gc

    int pos = hash(name);

    data *temp = h[pos];
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            flag = 1;
            break;
        } else temp = temp->next;
    }

    if (flag == 1) {
        printf("%s already exist!\n", name);
        enterToContinue();
        return;
    }

    char phone[100];
    printf("Input phone : ");
    scanf("%[^\n]", phone); gc

    char email[100];
    printf("Input email : ");
    scanf("%[^\n]", email); gc

    push(name, phone, email);
    puts("Data has been succesfully inserted");
    enterToContinue();
}

void search() {
    char name[100];
    printf("Input name to search : ");
    scanf("%[^\n]", name); gc

    int pos = hash(name);

    data *temp = h[pos];
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            printf("Name : %s\n", temp->name);
            printf("Phone : %s\n", temp->phone);
            printf("Email : %s\n", temp->email);
            enterToContinue();
            return;
        } else temp = temp->next;
    }
    puts("Data not found!");
    enterToContinue();
}

void del() {
    char name[100];
    printf("Input name to delete : ");
    scanf("%[^\n]", name); gc

    int pos = hash(name);

    if (h[pos] == NULL) {
        puts("Not Found!");
        enterToContinue();
        return;
    }

    if (strcmp(h[pos]->name, name) == 0) {
        data *temp = h[pos];
        h[pos] = temp->next;
        free(temp);
    } else {
        data *temp = h[pos];
        while (temp->next != NULL && strcmp(temp->next->name, name) != 0) {
            temp = temp->next;
        }
        data *toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
    }

    printf("%s has been succesfully deleted\n", name);
    enterToContinue();
}

void view() {
    for (int i = 0; i < max; i++) {
        data *temp = h[i];
        printf("%02d. ", i + 1);

        while (temp) {
            printf("%s -> ", temp->name);
            temp = temp->next;
        }
        puts("NULL");
    }
    enterToContinue();
}