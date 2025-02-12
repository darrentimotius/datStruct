#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

struct tnode {
    char value;
    tnode *left;
    tnode *right;
}*node;

tnode *createNode(char value) {
    tnode *newNode = (tnode*)malloc(sizeof(tnode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int rank(char c) {
    if (c == '^') return 3;
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    else return 0;
}

void buildPrefTree(tnode **root, char *prefeq, int *pos) {
    if (*root == NULL) {
        *root = createNode(prefeq[*pos]);
    }

    if (isOperator(prefeq[*pos])) {
        *pos = *pos + 1;
        (*root)->left = createNode(prefeq[*pos]);
        buildPrefTree((&(*root)->left), prefeq, pos);
        *pos = *pos + 1;
        (*root)->right = createNode(prefeq[*pos]);
        buildPrefTree((&(*root)->right), prefeq, pos);
    }
}

tnode *buildPostTree(char postfix[]) {
    tnode *stack[100];
    int top = -1;
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        tnode *newNode = createNode(postfix[i]);

        if (isdigit(postfix[i])) {
            stack[++top] = newNode;
        } else if (isOperator(postfix[i])) {
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }
    return stack[top];
}

tnode *buildInTree(char infix[]) {
    tnode *operandStack[100];
    char operatorStack[100];
    int operandTop = -1, operatorTop = -1;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            operandStack[++operandTop] = createNode(infix[i]);
        } else if (isOperator(infix[i])) {
            while (operandTop != -1 && rank(operatorStack[operatorTop]) >= rank(infix[i])) {
                tnode *opNode = createNode(operatorStack[operatorTop--]);
                opNode->right = operandStack[operandTop--];
                opNode->left = operandStack[operandTop--];
                operandStack[++operandTop] = opNode;
            }
            operatorStack[++operatorTop] = infix[i];
        }
    }
    
    while (operatorTop != -1) {
        tnode *opNode = createNode(operatorStack[operandTop--]);
        opNode->right = operandStack[operandTop--];
        opNode->left = operandStack[operandTop--];
        operandStack[++operandTop] = opNode;
    }

    return operandStack[operandTop];
}

void inOrder(tnode *root) {
    if (root != NULL) {
        if (isOperator(root->value)) printf("(");
        inOrder(root->left);
        printf("%c ", root->value);
        inOrder(root->right);
        if (isOperator(root->value)) printf(")");
    }
}

void preOrder(tnode *root) {
    if (root != NULL) {
        printf("%c ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(tnode *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%c ", root->value);
    }
}

int evaluate(tnode *root) {
    if (root->value == '+') {
        return evaluate(root->left) + evaluate(root->right);
    } else if (root->value == '-') {
        return evaluate(root->left) - evaluate(root->right);
    } else if (root->value == '*') {
        return evaluate(root->left) * evaluate(root->right);
    } else if (root->value == '/') {
        return evaluate(root->left) / evaluate(root->right);
    } else if (root->value == '^') {
        return (int) pow(evaluate(root->left), evaluate(root->right));
    } else {
        return root->value - '0';
    }
}

int main() {
    char prefeq[] = "+*234";
    char postfeq[] = "351^+";
    char infeq[] = "1*2+4/4";
    int pos = 0;

    tnode *root = NULL;
    buildPrefTree(&root, prefeq, &pos);
    
    inOrder(root);
    puts("");
    
    preOrder(root);
    puts("");

    postOrder(root);
    puts("");
    
    int res = evaluate(root);
    printf("result : %d\n", res);
    
    tnode *postTree = buildPostTree(postfeq);
    inOrder(postTree);
    puts("");
    tnode *inTree = buildInTree(infeq);
    inOrder(inTree);
    puts("");
    return 0;
}