#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define gc getchar();

struct Node {
    char name[100];
    int price;
    char category[100];
    char avail[100];
    int height;
    Node* left;
    Node* right;
} *root = NULL;

int count = 0;

void enterToCont() {
    printf("Press ENTER to continue..."); gc
}

void printMenu() {
    system("clear");
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
    printf("Name : %s\n", root->name);
    printf("Category : %s\n", root->category);
    printf("Price : %d\n", root->price);
    printf("Home Service : %s\n", root->avail);
    puts("=======================================");
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

void view() {
    system("clear");
    if (root == NULL) {
        puts("No Data");
        enterToCont();
        return;
    }

    char valid[100];

    do {
        printf("input view order [pre | in | post] : ");
        scanf("%[^\n]", valid); gc
    } while (strcmp(valid, "pre") != 0 && strcmp(valid, "in") != 0 && strcmp(valid, "post") != 0);

    printf("Total Treatment = %d\n", count);
    if (strcmp(valid, "pre") == 0) {
        pre(root);
    } else if (strcmp(valid, "in") == 0) {
        in(root);
    } else {
        post(root);
    }

    enterToCont();
}

bool validName(char* name) {
    if (strlen(name) < 5 || strlen(name) > 20) {
        return false;
    }

    if (name[0] != 'S' || name[1] != 'a' || name[2] != 'l' || name[3] != 'l' || name[4] != 'y') {
        return false;
    }

    int flag = 1;

    for (int i = 0; i < strlen(name); i++) {
        if (name[i] == ' ' && !isalpha(name[i + 1])) {
            flag = 0;
            break;
        }
    }

    if (flag == 0) return false;

    return true;
}

Node* createNode(char* name, int price, char* category, char* avail) {
    Node* c = (Node*)malloc(sizeof(Node));
    strcpy(c->name, name);
    c->price = price;
    strcpy(c->category, category);
    strcpy(c->avail, avail);
    c->height = 1;
    c->left = c->right = NULL;
    return c;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Node* root) {
    if (root == NULL) return 0;
    return root->height;
}

int getBalanceFactor(Node* root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

Node* leftRotate(Node* curr) {
    Node* currRight = curr->right;
    Node* currRightLeft = curr->right->left;

    currRight->left = curr;
    curr->right = currRightLeft;

    curr->height = 1 + max(height(curr->left), height(curr->right));
    currRight->height = 1 + max(height(currRight->left), height(currRight->right));
    return currRight;
}

Node* rightRotate(Node* curr) {
    Node* currLeft = curr->left;
    Node* currLeftRight = curr->left->right;

    currLeft->right = curr;
    curr->left = currLeftRight;
    
    curr->height = 1 + max(height(curr->left), height(curr->right));
    currLeft->height = 1 + max(height(currLeft->left), height(currLeft->right));
    
    return currLeft;
}

Node* insertNode(Node* root, Node* c) {
    if (root == NULL) {
        return c;
    }

    if (strcmp(c->name, root->name) > 0) {
        root->right = insertNode(root->right, c);
    } else if (strcmp(c->name, root->name) < 0) {
        root->left = insertNode(root->left, c);
    } else return root;

    root->height = 1 + max(height(root->left), height(root->right));

    // R
    if (getBalanceFactor(root) > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);

    // R
    } else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);

    // LR
    } else if (getBalanceFactor(root) > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);

    // RL
    } else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void insertData() {
    system("clear");
    char name[100];
    int price;
    char category[100];
    char avail[100];

    puts("INSERT NEW TREATMENT");
    do {
        printf("input new treatment name : ");
        scanf("%[^\n]", name); gc
    } while (!validName(name));

    do {
        printf("input treatment price [50000 - 1000000] : ");
        scanf("%d", &price); gc
    } while(price < 50000 || price > 1000000);

    do {
        printf("input treatment category [Hair Care | Nail Care | Body Care]: ");
        scanf("%[^\n]", category); gc
    } while (strcmp(category, "Hair Care") != 0 && strcmp(category, "Nail Care") != 0 && strcmp(category, "Body Care") != 0);

    do {
        printf("input treatment availability for home service [Available | Unavailable] : ");
        scanf("%[^\n]", avail); gc
    } while (strcmp(avail, "Available") != 0 && strcmp(avail, "Unavailable") != 0);

    Node* c = createNode(name, price, category, avail);

    root = insertNode(root, c);

    puts("[New Treatment is successfully inserted]");
    count++;
    enterToCont();
}

int checkNode(Node* root, char* name) {
    if (root == NULL) return -1;
    if (strcmp(root->name, name) == 0) {
        return 1;
    }
    
    int leftSide = checkNode(root->left, name);
    if (leftSide == 1) return 1;
    return checkNode(root->right, name);
}

Node* minValueNode(Node* root) {
    Node* c = root;

    while (c->left != NULL) {
        c = c->left;
    }

    return c;
}

Node* maxValueNode(Node* root) {
    Node* c = root;

    while (c->right != NULL) {
        c = c->right;
    }

    return c;
}

Node* delNode(Node* root, char* name) {
    if (strcmp(name, root->name) > 0) {
        root->right = delNode(root->right, name);
    } else if (strcmp(name, root->name) < 0) {
        root->left = delNode(root->left, name);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Node* temp = maxValueNode(root->left);

            strcpy(root->name, temp->name);
            root->price = temp->price;
            strcpy(root->category, temp->category);
            strcpy(root->avail, temp->avail);

            root->left = delNode(root->left, temp->name);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));


    // R
    if (getBalanceFactor(root) > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);

    // L
    } else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);

    // LR
    } else if (getBalanceFactor(root) > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);

    // RL
    } else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void del() {
    system("clear");
    if (root == NULL) {
        puts("no data");
        enterToCont();
        return;
    }

    char name[100];

    in(root);
    printf("Delete Treatment\n");
    printf("input treatment name to be deleted : ");
    scanf("%[^\n]", name); gc

    if (checkNode(root, name) == 1) {
        root = delNode(root, name);
        puts("Delete Successfully");
        count--;
    } else {
        puts("Data not found");
    }

    enterToCont();
}

int main() {
    int inp = -1;
    do {
        printMenu();

        do {
            printf(">> ");
            scanf("%d", &inp); gc
        } while (inp < 1 || inp > 4);

        switch(inp) {
            case 1:
                view();
                break;
            case 2:
                insertData();
                break;
            case 3:
                del();
                break;
            case 4:
                puts("Thank you for using our program...");
                enterToCont();
                return 0;
        }
    } while(1);
    return 0;
}