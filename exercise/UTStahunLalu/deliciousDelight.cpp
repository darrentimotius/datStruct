#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar();
#define clear system("clear");

struct Node {
    char name[100];
    char foodType[100];
    int quantity;
    double distance;
    char address[100];
    int priority;
    char priorityString[100];
    Node* next;
}*h, *t;

void printList() {
    puts("----------------------------------");
    puts("| Menu           | Price         |");
    puts("----------------------------------");
    puts("| Pizza          | $8            |");
    puts("| Burgers        | $6            |");
    puts("| Sushi          | $12           |");
    puts("| Tacos          | $7            |");
    puts("| Pasta          | $10           |");
    puts("----------------------------------");
}

void printMenu() {
    clear
    puts("--- Delicioud Delights Food Order Management System ---");
    printList();
    puts("1. Add Order");
    puts("2. Process Order");
    puts("3. Display Queue");
    puts("4. Exit");
}

void enterToContinue() {
    puts("Press ENTER To Continue...."); gc
}

Node* createNode(char* name, char* foodType, int quantity, double distance, char* address, int priority) {
    Node* c = (Node*)malloc(sizeof(Node));

    strcpy(c->name, name);
    strcpy(c->foodType, foodType);
    c->quantity = quantity;
    c->distance = distance;
    strcpy(c->address, address);
    c->priority = priority;

    if (priority == 0) {
        strcpy(c->priorityString, "Standard");
    } else if (priority == 1) {
        strcpy(c->priorityString, "Rush");
    } else if (priority == 2) {
        strcpy(c->priorityString, "High Priority");
    }

    c->next = NULL;

    return c;
}

void push(Node* c) {
    if (h == NULL) {
        h = t = c;
    } else if (c->priority > h->priority) {
        c->next = h;
        h = c;
    } else if (c->priority <= t->priority) {
        t->next = c;
        t = c;
    } else {
        Node* temp = h;
        while (temp != NULL && temp->next->priority >= c->priority) {
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

bool pop(char* name) {
    if (strcmp(h->name, name) == 0) {
        Node* temp = h;
        h = h->next;
        free(temp);
        return true;
    } else {
        Node* temp = h;
        while (temp != NULL && strcmp(temp->next->name, name) != 0) {
            temp = temp->next;
        }
        Node* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
        return true;
    }
    return false;
}

bool validName(char* name) {
    return strlen(name) <= 20;
}

bool validFoodType(char* foodType) {
    return strcmp(foodType, "Pizza") == 0 || strcmp(foodType, "Burgers") == 0 || strcmp(foodType, "Sushi") == 0 || strcmp(foodType, "Tacos") == 0 || strcmp(foodType, "Pasta") == 0;
}

bool validQuantity(int quantity) {
    return quantity >= 1;
}

bool validDistance(double distance) {
    return distance >= 1 && distance <= 10;
}

bool validAddress(char* address) {
    return strlen(address) <= 30;
}

bool validPriority(int priority) {
    return priority >= 0 && priority <= 2;
}

void addOrder() {
    clear
    printList();
    char name[100];
    char foodType[100];
    int quantity;
    double distance;
    char address[100];
    int priority;

    do {
        printf("Enter Customer Name (max 20 characters): ");
        scanf("%[^\n]", name); gc

        if (!validName(name)) puts("Input cannot be proceed. Please enter no more than 20 characters.");
    } while (!validName(name));

    do {
        printf("Select Food (Pizza, Burgers, Sushi, Tacos, Pasta): ");
        scanf("%[^\n]", foodType); gc
    
        if (!validFoodType(foodType)) puts("Input cannot be proceed. Please select from the list.");
    } while (!validFoodType(foodType));
    
    do {
        printf("Enter Quantity (must be at least 1): ");
        scanf("%d", &quantity); gc
    
        if (!validQuantity(quantity)) puts("Input cannot be proceed. Please enter a value at least 1.");
    } while (!validQuantity(quantity));
    
    do {
        printf("Enter Distance (min. 1 km, max. 10 km): ");
        scanf("%lf", &distance); gc
    
        if (!validDistance(distance)) puts("Input cannot be proceed. Please enter a value between 1 and 10.");
    } while (!validDistance(distance));
    
    do {
        printf("Enter Delivery Address (max 30 characters): ");
        scanf("%[^\n]", address); gc
    
        if (!validAddress(address)) puts("Input cannot be proceed. Please enter no more than 20 characters.");
    } while (!validAddress(address));
    
    do {
        printf("Enter Priority (0 for standard, 1 for rush, 2 for high priority): ");
        scanf("%d", &priority); gc
    
        if (!validPriority(priority)) puts("Input cannot be proceed. Please enter a value between 0 and 2");
    } while (!validPriority(priority));

    push(createNode(name, foodType, quantity, distance, address, priority));
    puts("Order added");
    enterToContinue();
}

double calculatePrice(Node* data) {
    if (strcmp(data->foodType, "Pizza") == 0) {
        return 8;
    } else if (strcmp(data->foodType, "Burgers") == 0) {
        return 6;
    } else if (strcmp(data->foodType, "Sushi") == 0) {
        return 12;
    } else if (strcmp(data->foodType, "Tacos") == 0) {
        return 7;
    } else if (strcmp(data->foodType, "Pasta") == 0) {
        return 10;
    }
}

void processOrder() {
    clear
    if (h == NULL) {
        puts("No orders in the queue.");
        enterToContinue();
        return;
    }

    double deliveryFee = h->distance < 5 ? 2.5 : 5;
    double serviceFee;
    if (h->priority == 1) serviceFee = 10;
    else if (h->priority == 2) serviceFee = 20;

    puts("----------------------------------------------------------------------------------------");
    puts("| Customer Name           | Food     | Qty   | Delivery Fee | Service Fee | Total Cost |");
    puts("----------------------------------------------------------------------------------------");
    printf("| %-24s| %-9s| %-5d | $%-12.2lf| $%-11.2lf| $%-10.2lf|\n", h->name, h->foodType, h->quantity, deliveryFee, serviceFee, (calculatePrice(h) * h->quantity) + deliveryFee + serviceFee);
    puts("----------------------------------------------------------------------------------------");

    Node* temp = h;
    h = h->next;
    free(temp);

    enterToContinue();
}

void displayQueue() {
    clear

    if (h == NULL) {
        puts("No orders in the queue.");
        enterToContinue();
        return;
    }

    puts("--- Current Orders in Queue --- ");
    puts("----------------------------------------------------------------------------------------------------------------");
    puts("| No | Customer Name           | Food     | Qty   | Priority       | Distance | Address                        |");
    puts("----------------------------------------------------------------------------------------------------------------");

    Node* temp = h;
    int count = 1;
    while (temp != NULL) {
        printf("| %-2d | %-24s| %-9s| %-5d | %-15s| %-9.2lf| %-31s|\n", count++, temp->name, temp->foodType, temp->quantity, temp->priorityString, temp->distance, temp->address);
        temp = temp->next;
    }
    puts("----------------------------------------------------------------------------------------------------------------");

    char confirm;
    do {
        printf("Do you want to cancel any order? (y/n): ");
        scanf("%c", &confirm); gc
    } while (confirm != 'y' && confirm != 'n');

    if (confirm == 'n') {
        enterToContinue();
        return;
    }
    
    char name[100];
    printf("Enter Customer Name to cancel the order: ");
    scanf("%[^\n]", name); gc

    if (pop(name)) {
        printf("Order for %s has been canceled\n", name);
    } else {
        puts("Order not found.");
    }

    enterToContinue();
}


int main() {
    do {
        int inp = -1;
        printMenu();
        do {
            printf("Enter your choice: ");
            scanf("%d", &inp); gc
        } while (inp < 1 || inp > 4);

        switch (inp) {
            case 1:
                addOrder();
                break;
            case 2:
                processOrder();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                clear
                printf("Thank you\nExiting the program...\n");
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}