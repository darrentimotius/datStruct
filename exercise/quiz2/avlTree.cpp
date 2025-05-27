#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define gc getchar();

struct Node {
    int id;
    int exam_pass;
    int have_c_grade;
    int international_achievements;
    int value;
    int height;
    Node* left;
    Node* right;
}*root = NULL;

Node* createNode(int id, int exam_pass, int have_c_grade, int international_achievements) {
    Node* c = (Node*)malloc(sizeof(Node));
    c->id = id;
    c->exam_pass = exam_pass;
    c->have_c_grade = have_c_grade;
    c->international_achievements = international_achievements;
    if (!c->exam_pass) {
        if (c->have_c_grade) c->value = 0;
        else c->value = 1;
    } else {
        if (c->have_c_grade) c->value = 2;
        else c->value = 3;
    }
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

Node* insertNode(Node* root, Node* c) {
    if (root == NULL) return c;
    
    if (c->value > root->value) {
        root->right = insertNode(root->right, c);
    } else if (c->value < root->value) {
        root->left = insertNode(root->left, c);
    } else if (c->value == root->value) {
        if (c->international_achievements > root->international_achievements) {
            root->right = insertNode(root->right, c);
        } else {
            root->left = insertNode(root->left, c);
            return root;
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
    } else if (bf(root) < -1 && bf(root->right) >= 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int valueTemp = 0;
int international_achievements_temp = 0;

void searchValue(Node* root, int id) {
    if (root == NULL) return;
    if (root->id == id) {
        valueTemp = root->value;
        international_achievements_temp = root->international_achievements;
        return;
    }
    searchValue(root->left, id);
    searchValue(root->right, id);
}

Node* maxNode(Node* root) {
    Node* c = root;
    if (c == NULL) return root;
    while (c->right != NULL) {
        c = c->right;
    }
    return c;
}

Node* deleteNode(Node* root, int value, int international_achievements) {
    if (root == NULL) return root;

    if (value > root->value) {
        root->right = deleteNode(root->right, value, international_achievements);
    } else if (value < root->value) {
        root->left = deleteNode(root->left, value, international_achievements);
    } else if (value == root->value) {
        if (international_achievements > root->international_achievements) {
            root->right = deleteNode(root->right, value, international_achievements);
        } else if (international_achievements < root->international_achievements) {
            root->left = deleteNode(root->left, value, international_achievements);
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
                root->exam_pass = temp->exam_pass;
                root->have_c_grade = temp->have_c_grade;
                root->international_achievements = temp->international_achievements;

                root->left = deleteNode(root->left, temp->value, temp->international_achievements);
            }
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
    } else if (bf(root) < -1 && bf(root->right) >= 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int count = 0;
Node* data[1000];
void move(Node* root) {
    if (root == NULL) return;
    data[count++] = root;
    move(root->left);
    move(root->right);
}

void sort() {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (data[j]->value < data[j+1]->value || (data[j]->value == data[j+1]->value && data[j]->international_achievements < data[j+1]->international_achievements)) {
                Node* temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

int main() {
    count = 0;
    int n;
    scanf("%d", &n); gc

    for (int i = 0; i < n; i++) {
        valueTemp = 0;
        international_achievements_temp = 0;
        char f;
        scanf("%c", &f);

        if (f == 'i') {
            int id;
            int exam_pass;
            int have_c_grade;
            int international_achievements;

            scanf(" %d %d %d %d", &id, &exam_pass, &have_c_grade, &international_achievements); gc
            root = insertNode(root, createNode(id, exam_pass, have_c_grade, international_achievements));
        } else if (f == 'd') {
            int id;
            scanf("%d", &id); gc
            searchValue(root, id);
            root = deleteNode(root, valueTemp, international_achievements_temp);
        }
    }

    move(root);
    sort();
    if (count < 3) {
        for (int i = 0; i < count; i++) {
            printf("%d ", data[i]->id);
        }
    } else {
        for (int i = 0; i < 3; i++) {
            printf("%d ", data[i]->id);
        }
    }
    puts("");
    return 0;
}