#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define gc getchar();
#define clear system("clear");

int count = 0;

struct Node {
    char id[10];
    char name[100];
    int stock;
    int price;
    int height;
    Node* left;
    Node* right;
}*root = NULL;

void printMenu() {
    clear
    puts("EShoe Factory");
    puts("1. View Stock");
    puts("2. Insert New Shoe");
    puts("3. Delete Shoe");
    puts("4. Exit");
}

void enterToContinue() {
    printf("Press ENTER to continue..."); gc
}

void printData(Node* c) {
    printf("Total item(s) = %d\n", count);
    printf("ID : %s\n", c->id);
    printf("Name : %s\n", c->name);
    printf("Stock : %d\n", c->stock);
    printf("Price : %d\n", c->price);
    puts("================================");
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

void viewStock() {
    clear
    if (root == NULL) {
        puts("There is no data");
        enterToContinue();
        return;
    }

    char valid[100];
    do {
        printf("Choose show method [Pre-Order | In-Order | Post-Order] : ");
        scanf("%[^\n]", valid); gc
    } while (strcmp(valid, "Pre-Order") != 0 && strcmp(valid, "In-Order") != 0 && strcmp(valid, "Post-Order") != 0);

    if (strcmp(valid, "Pre-Order") == 0) {
        pre(root);
    } else if (strcmp(valid, "In-Order") == 0) {
        in(root);
    } else if (strcmp(valid, "Post-Order") == 0) {
        post(root);
    }

    enterToContinue();
}


void generateID(char* id, char* name) {
    sprintf(id, "%c%d%d%d", toupper(name[5]), rand() % 10, rand() % 10, rand() % 10);
}

Node* createNode(char* name, int stock, int price) {
    Node* c = (Node*)malloc(sizeof(Node));
    strcpy(c->name, name);
    c->stock = stock;
    c->price = price;
    c->height = 1;
    c->left = c->right = NULL;
    generateID(c->id, name);

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

Node* insertNode(Node* root, Node* c) {
    if (root == NULL) return c;
    
    if (strcmp(c->id, root->id) < 0) {
        root->left = insertNode(root->left, c);
    } else if (strcmp(c->id, root->id) > 0) {
        root->right = insertNode(root->right, c);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    if (bf(root) > 1 && bf(root->left) >= 0) {
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) <= 0) {
        return leftRotate(root);
    } else if (bf(root) > 1 && bf(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

bool validName(char* name) {
    int l = strlen(name);
    if (l < 5 || l > 20) return false;

    if (name[0] != 'S' || name[1] != 'h' || name[2] != 'o' || name[3] != 'e') return false;

    int flag = 1;
    for (int i = 0; i < l; i++) {
        if (name[i] == ' ' && !isalpha(name[i + 1])) {
            flag = 0;
            break;
        }
    }

    if (flag == 0) return false;

    return true;
}

void insertShoe() {
    clear
    char name[100];
    int stock;
    int price;

    do {
        printf("Input shoe name : ");
        scanf("%[^\n]", name); gc
    } while (!validName(name));

    do {
        printf("Input shoe stock : ");
        scanf("%d", &stock); gc
    } while (stock < 1);

    do {
        printf("Input shoe price [500.000 - 5.200.000] : ");
        scanf("%d", &price); gc
    } while (price < 500000 || price > 5200000);

    root = insertNode(root, createNode(name, stock, price));

    puts("Shoe has been successfully inserted");
    count++;
    enterToContinue();
}

int search(Node* root, char* id) {
    if (root == NULL) return 0;
    if (strcmp(root->id, id) == 0) return 1;

    int left = search(root->left, id);
    if (left == 1) return 1;
    return search(root->right, id);
}

Node* maxValue(Node* root) {
    Node* c = root;
    while (c->right != NULL) {
        c = c->right;
    }

    return c;
}

Node* delNode(Node* root, char* id) {
    if (strcmp(id, root->id) < 0) {
        root->left = delNode(root->left, id);
    } else if (strcmp(id, root->id) > 0) {
        root->right = delNode(root->right, id);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Node* c = maxValue(root->left);
            strcpy(root->id, c->id);
            strcpy(root->name, c->name);
            root->stock = c->stock;
            root->price = c->price;

            root->left = delNode(root->left, c->id);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));

    if (bf(root) > 1 && bf(root->left) >= 0) {
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) <= 0) {
        return leftRotate(root);
    } else if (bf(root) > 1 && bf(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

void deleteShoe() {
    if (root == NULL) {
        puts("There is no data");
        enterToContinue();
        return;
    }

    in(root);

    char id[100];
    do {
        printf("Input shoe ID to delete : ");
        scanf("%[^\n]", id); gc
    } while (!search(root, id));

    if (search(root, id)) {
        root = delNode(root, id);
    } else {
        puts("ID not found!");
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
                viewStock();
                break;
            case 2:
                insertShoe();
                break;
            case 3:
                deleteShoe();
                break;
            case 4:
                puts("Thank you for using our program!");
                enterToContinue();
                return 0;
        }
    } while (1);
    return 0;
}