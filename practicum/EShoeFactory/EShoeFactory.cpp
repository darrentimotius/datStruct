#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

struct Node{
    char name[25];
    int stock;
    int price;
    int height;
    Node* left;
    Node* right;
}*root = NULL;

Node* createNode(char* name, int stock, int price) {
    Node* c = (Node*)malloc(sizeof(Node));

    strcpy(c->name, name);
    c->stock = stock;
    c->price = price;
    c->height = 1;
    c->left = NULL;
    c->right = NULL;

    return c;
}

int height(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->height;
    }
}

int max(int a, int b) {
return a > b ? a : b;
}

int getBalance(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        height(root->left) - height(root->right);
    }
}



int main() {
    return 0;
}