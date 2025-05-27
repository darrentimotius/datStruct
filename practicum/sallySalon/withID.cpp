#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define gc getchar();
#define clear system("clear");

struct Node {
    char id[10];
    char name[100];
    int price;
    char category[100];
    char availability[100];
    int height;
    Node* left;
    Node* right;
}*root = NULL;

int count = 0;

void enterToContinue() {
    printf("Press ENTER to continue..."); gc
}

void printMenu() {
    clear
    puts(" _____       _ _         _____       _             ");
    puts("/  ___|     | | |       /  ___|     | |            ");
    puts("\\ `--.  __ _| | |_   _  \\ `--.  __ _| | ___  _ __  ");
    puts(" `--. \\/ _` | | | | | |  `--. \\/ _` | |/ _ \\| '_ \\ ");
    puts("/\\__/ / (_| | | | |_| | /\\__/ / (_| | | (_) | | | |");
    puts("\\____/ \\__,_|_|_|\\__, | \\____/ \\__,_|_|\\___/|_| |_|");
    puts("                  __/ |                            ");
    puts("                 |___/                             ");
    printf("\nMenu:\n");
    puts("1. View available Treatment");
    puts("2. Insert New Treatment");
    puts("3. Delete Treatment");
    puts("4. Exit");
    puts("[1-4]");
}

void printData(Node* root) {
    printf("ID : %s\n",root->id);
    printf("Treatment : %s\n", root->name);
    printf("Price : %d\n", root->price);
    printf("Category : %s\n", root->category);
    printf("Availability : %s\n", root->availability);
    puts("==============================");
}

void pre(Node* root) {
    if (root == NULL) return;
    printData(root);
    pre(root->left);
    pre(root->right);
}

void in(Node* root) {
    if (root == NULL) return;
    in(root->left);
    printData(root);
    in(root->right);
}
void post(Node* root) {
    if (root == NULL) return;
    post(root->left);
    post(root->right);
    printData(root);
}

void viewTreatment() {
    clear
    if (root == NULL) {
        puts("no data");
        enterToContinue();
        return;
    }

    char order[100];
    do {
        printf("input view order [pre | in | post] : ");
        scanf("%[^\n]", order); gc
    } while(strcmp(order, "pre") != 0 && strcmp(order, "in") != 0 && strcmp(order, "post") != 0);

    printf("Total data = %d\n", count);
    if (strcmp(order, "pre") == 0) {
        pre(root);
    } else if (strcmp(order, "in") == 0) {
        in(root);
    } else {
        post(root);
    }

    enterToContinue();
}

void generateID(char* name, char* id) {
    sprintf(id, "%c%c%d%d%d", toupper(name[6]), toupper(name[7]), rand() % 10, rand() % 10, rand() % 10);
}

Node* createNode(char* name, int price, char* category, char* availability) {
    Node* c = (Node*)malloc(sizeof(Node));
    generateID(name, c->id);
    strcpy(c->name, name);
    c->price = price;
    strcpy(c->category, category);
    strcpy(c->availability, availability);
    c->height = 1;
    c->left = c->right = NULL;
    return c;
}

int height(Node* root) {
    if (root == NULL) return 0;
    return root->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int bf(Node* root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

Node* leftRotate(Node* root) {
    Node* right = root->right;
    Node* rightLeft = root->right->left;

    right->left = root;
    root->right = rightLeft;

    root->height = 1 + max(height(root->left), height(root->right));
    right->height = 1 + max(height(right->left), height(right->right));
    return right;
}

Node* rightRotate(Node* root) {
    Node* left = root->left;
    Node* leftRight = root->left->right;

    left->right = root;
    root->left = leftRight;

    root->height = 1 + max(height(root->left), height(root->right));
    left->height = 1 + max(height(left->left), height(left->right));
    return left;
}

Node* rebalancing(Node* root) {
    root->height = 1 + max(height(root->left), height(root->right));

    if (bf(root) > 1 && bf(root->left) >= 0) {
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) < 0) {
        return leftRotate(root);
    } else if (bf(root) > 1 && bf(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) >= 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* insertNode(Node* root, Node* c) {
    if (root == NULL) return c;

    if (strcmp(c->id, root->id) < 0) {
        root->left = insertNode(root->left, c);
    } else if (strcmp(c->id, root->id) > 0) {
        root->right = insertNode(root->right, c);
    }

    return rebalancing(root);
}

bool validName(char* name) {
    int l = strlen(name);
    if (l <= 5 || l > 20) return false;

    if (name[0] != 'S' || name[1] != 'a' || name[2] != 'l' || name[3] != 'l' || name[4] != 'y') return false;

    int flag = 1;
    for (int i = 0; i < l; i++) {
        if (name[i] == ' ' && !isalpha(name[i+1])) {
            flag = 0;
            break;
        }
    }
    if (!flag) return false;
    return true;
}

void insertTreatment() {
    clear
    puts("INSERT NEW TREATMENT");
    char name[100];
    int price;
    char category[100];
    char availability[100];

    do {
        printf("input new treatment name : ");
        scanf("%[^\n]", name); gc
    } while (!validName(name));

    do {
        printf("input treatment price : ");
        scanf("%d", &price); gc
    } while (price < 50000 || price > 1000000);

    do {
        printf("input treatment category [Hair Care | Nail Care | Body Care] : ");
        scanf("%[^\n]", category); gc
    } while (strcmp(category, "Hair Care") != 0 && strcmp(category, "Nail Care") != 0 && strcmp(category, "Body Care") != 0);

    do {
        printf("input treatment availability for home service [Available | Unavailable] : ");
        scanf("%[^\n]", availability); gc
    } while (strcmp(availability, "Available") != 0 && strcmp(availability, "Unavailable") != 0);

    root = insertNode(root, createNode(name, price, category, availability));
    count++;

    puts("\n[New Treatment is successfully inserted]");
    enterToContinue();
}

char idToDel[100];
bool search(Node* root, char* name) {
    if (root == NULL) return false;

    if (strcmp(root->name, name) == 0) {
        strcpy(idToDel, root->id);
        return true;
    }
    bool leftSide = search(root->left, name);
    if (leftSide) return true;
    return search(root->right, name);
}

Node* maxValNode(Node* root) {
    Node* c = root;
    while (c->right != NULL) {
        c = c->right;
    }
    return c;
}

Node* deleteNode(Node* root, char* id) {
    if (root == NULL) return root;

    if (strcmp(id, root->id) < 0) {
        root->left = deleteNode(root->left, id);
    } else if (strcmp(id, root->id) > 0) {
        root->right = deleteNode(root->right, id);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Node* temp = maxValNode(root->left);
            strcpy(root->id, temp->id);
            strcpy(root->name, temp->name);
            root->price = temp->price;
            strcpy(root->category, temp->category);
            strcpy(root->availability, temp->name);

            root->left = deleteNode(root->left, temp->id);
        }
    }

    return rebalancing(root);
}

void deleteTreatment() {
    clear
    if (root == NULL) {
        puts("no data");
        enterToContinue();
        return;
    }

    in(root);
    puts("\nDELETE TREATMENT");
    char name[100];
    printf("input treatment name to be deleted : ");
    scanf("%[^\n]", name); gc

    if (search(root, name)) {
        root = deleteNode(root, idToDel);
        count--;
        puts("\n[Delete successfully]");
    } else {
        puts("Data not found");
    }
    enterToContinue();
}

int main() {
    do {
        srand(time(NULL));
        int inp = -1;
        printMenu();
        do {
            printf(">> ");
            scanf("%d", &inp); gc
        } while (inp < 1 || inp > 4);

        switch(inp) {
            case 1:
                viewTreatment();
                break;
            case 2:
                insertTreatment();
                break;
            case 3:
                deleteTreatment();
                break;
            case 4:
                puts("Goodbye...");
                enterToContinue();
                return 0;
        }
    } while(1);
}