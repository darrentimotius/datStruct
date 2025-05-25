#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id;
    char name[100];
    char exp[100];
    int height;
    Node* left;
    Node* right;
}*root = NULL;

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

    if (c->id < root->id) {
        root->left = insertNode(root->left, c);
        return root;
    } else if (c->id > root->id) {
        root->right = insertNode(root->right, c);
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    
    if (bf(root) > 1 && bf(root->left) >= 0) {
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) < 0) {
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

void insertData(int id, char* name, char* exp) {
    Node* c = (Node*)malloc(sizeof(Node));
    c->id = id;
    strcpy(c->name, name);
    strcpy(c->exp, exp);
    c->height = 1;
    c->left = c->right = NULL;

    root = insertNode(root, c);
}

Node* maxNode(Node* root) {
    Node* c = root;

    while(c->right != NULL) {
        c = c->right;
    }

    return c;
}

Node* deleteNode(Node* root, int id) {
    if (id < root->id) {
        root->left = deleteNode(root->left, id);
        return root;
    } else if (id > root->id) {
        root->right = deleteNode(root->right, id);
        return root;
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Node* temp = maxNode(root->left);

            root->id = temp->id;
            strcpy(root->name, temp->name);
            strcpy(root->exp, temp->exp);

            root->left = deleteNode(root->left, temp->id);
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));
    
    if (bf(root) > 1 && bf(root->left) >= 0) {
        return rightRotate(root);
    } else if (bf(root) < -1 && bf(root->right) < 0) {
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

int count = 0;
Node* searched[10000];

void search(Node* root, char* start, char* end) {
    if (root == NULL) return;

    search(root->left, start, end);
    if (strcmp(root->exp, start) >= 0 && strcmp(root->exp, end) <= 0) {
        searched[count++] = root;
    }
    search(root->right, start, end);
}

void sort() {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (strcmp(searched[j]->exp, searched[j + 1]->exp) > 0) {
                Node* temp = searched[j];
                searched[j] = searched[j + 1];
                searched[j + 1] = temp;
            }
        }
    }
}

void in(Node* root) {
    if(root == NULL) return;
    in(root->left);
    printf("%d - %s - %s\n", root->id, root->name, root->exp);
    in(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int id;
        char name[100];
        char exp[100];
        scanf("%d;%[^;];%s", &id, name, exp); getchar();
        insertData(id, name, exp);
    }

    int m;
    scanf("%d", &m); getchar();
    for (int i = 0; i < m; i++) {
        int id;
        scanf("%d", &id); getchar();
        root = deleteNode(root, id);
    }

    
    char start[100];
    char end[100];
    scanf("%s", start); getchar();
    scanf("%s", end); getchar();
    search(root, start, end);

    // in(root);
    // puts("");
    sort();
    for (int i = 0; i < count; i++) {
        printf("%s - %s\n", searched[i]->exp, searched[i]->name);
    }
}