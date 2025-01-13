#include <stdio.h>
#include <stdlib.h>

struct data {
    int value;
    data *next;
} *h, *t, *c;

void pushHead(int a) {
    c = (data*)malloc(sizeof(data));
    c->value = a;
    c->next = NULL;

    if (!h) {
        h = c = t;
    } else {
        c->next = h;
        h = c;
    }
}

void pushTail(int a) {
    c = (data*)malloc(sizeof(data));
    c->value = a;
    c->next = NULL;

    if (!h) {
        h = c = t;
    } else {
        t->next = c;
        t = c;
    }
}

void pushMiddle(int a) {
    c = (data*)malloc(sizeof(data));
    c->value = a;
    c->next = NULL;

    if (!h) {
        h = c = t;
    } else if (a > t->value) {
        t->next = c;
        t = c;
    } else if (h->value > a) {
        c->next = h;
        h = c;
    } else {
        data *temp;
        temp = h;

        while (a > temp->next->value) {
            temp = temp->next;
            c->next = temp->next;
            temp->next = c;
        }
    }
}

void popHead() {
    if (h == NULL) return;
    data *temp = h;
    h = h->next;
    free(temp);
}

void popTail() {
    if (t == NULL) return;
    data *temp = h;

    while (temp->next->value != t->value) {
        temp = temp->next;
    }

    t = temp;
    data *curr;
    curr = temp->next;
    temp->next = NULL;
    free(curr);
}