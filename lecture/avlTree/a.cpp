#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    int height;
    Node* left;
    Node* right;
};

Node* createNode(int val) {
    Node* c = (Node*)malloc(sizeof(Node));
    c->val = val;
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
    return (a > b) ? a : b;
}

int getBalance(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return height(root->left) - height(root->right);
    }
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    x->right = T2;
    y->left = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return x;
}

Node* insert(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    } else if (val < root->val) {
        root->left = insert(root->left, val);
    } else if (val > root->val) {
        root->right = insert(root->right, val);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance < -1 && val > root->right->val) {
        return leftRotate(root);
    }

    if (balance > 1 && val < root->left->val) {
        return rightRotate(root);
    }

    if (balance < -1 && val < root->right->val) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    if (balance > 1 && val > root->left->val) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    Node* c = node;

    while (c->left != NULL) {
        c = c->left;
    }

    return c;
}

Node* delNode(Node* root, int val) {
    if (root == NULL) {
        return root;
    }

    if (val < root->val) {
        root->left = delNode(root->left, val);
    } else if (val > root->val) {
        root->right = delNode(root->right, val);
    } else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = delNode(root->right, temp->val);
        }
    }
    
    if (root == NULL) {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(Node* root) {
    if (root == NULL) return;

    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

int main() {
    Node* root = NULL;

    root = insert(root, 20);
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 35);
    root = insert(root, 25);

    inOrder(root);
    puts("");

    printf("%d\n", root->val);

    root = delNode(root, 25);
    puts("");
    inOrder(root);
    puts("");

    printf("%d\n", root->left->val);
    return 0;
}