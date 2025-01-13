#include <stdio.h>
#include <stdlib.h>

struct data {
    int value;
    data *next;
    data *prev;
} *h, *t, *c;

void pushHead(int a) {
    c = (data*)malloc(sizeof(data));
    c->value = a;
    c->prev = NULL;
    c->next = NULL;

    if (!h) {
        h = t = c;
    } else {
        c->next = h;
        h->prev = c;
        h = c;
    }
}