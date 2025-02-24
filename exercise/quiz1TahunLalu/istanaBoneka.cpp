#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define gc getchar();

struct node {
    char name[11];
    char ticket[11];
    int ticketNum;
    node *next;
    node *prev;
}*h, *t;

int count = 0;

node *createNewNode(char *name, char *ticket, int ticketNum) {
    node *c = (node*)malloc(sizeof(node));
    strcpy(c->name, name);
    strcpy(c->ticket, ticket);
    c->ticketNum = ticketNum;
    c->next = NULL;
    c->prev = NULL;

    return c;
}

void push(node *c) {
    if (h == NULL) {
        h = t = c;
    } else if (c->ticketNum < h->ticketNum) {
        c->next = h;
        h->prev = c;
        h = c;
    } else if (c->ticketNum > h->ticketNum) {
        t->next = c;
        c->prev = t;
        t = c;
    } else {
        node *temp = h;
        while (c->ticketNum >= temp->next->ticketNum) {
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next->prev = c;
        c->prev = temp;
        temp->next = c;
    }
}

void view() {
    node *c = h;
    puts("No Name     Ticket");
    int countView = 1;
    while (c != NULL) {
        printf("%02d %-8s %s\n", countView, c->name, c->ticket);
        countView++;
        c = c->next;
    }
}
void reg(int num) {
    for (int i = 0; i < num; i++) {
        char name[11];
        char ticket[11];
        int ticketNum = -1;
        scanf("%s %s", name, ticket); gc
        
        if (strcmp(ticket, "FAST_TRACK") == 0) {
            ticketNum = 1;
        } else ticketNum = 2;
        
        node *c = createNewNode(name, ticket, ticketNum);
        push(c);
        count++;
    }
    view();
}

void pop(char *name) {
    if (strcmp(h->name, name) == 0) {
        node *temp = h;
        h = h->next;
        h->prev = NULL;
        free(temp);
    } else if (strcmp(t->name, name) == 0) {
        // node *temp = h;
        // while (strcmp(temp->next->name, name) != 0) {
        //     temp = temp->next;
        // }
        // free(t);
        // t = temp;
        // t->next = NULL;
        node *temp = t->prev;
        free(t);
        t = temp;
        t->next = NULL;
    } else {
        node *temp = h;
        while (strcmp(temp->next->name, name) != 0) {
            temp = temp->next;
        }
        node *c;
        c = temp->next;
        temp->next = c->next;
        c->next->prev = temp;
        free(c);
    }
}

void remove(int num) {
    for (int i = 0; i < num; i++) {
        char name[11];
        scanf("%s", name); gc

        pop(name);
        count--;
    }
    view();
}


void call() {
    if (h == NULL) return;
    for (int i = 0; i < 4; i++) {
        if (h == NULL) break;
        node *temp = h;
        printf("%s ", temp->name);
        h = h->next;
        if (h != NULL) {
            h->prev = NULL;
        }
        free(temp);
        count--;
    }
    puts("got into the boat.");
    printf("%d queues remaining.\n", count);
}

int main() {
    char inp[100];
    do {
        scanf("%s", inp); gc
        if (strcmp(inp, "REGISTER") == 0) {
            int a;
            scanf("%d", &a); gc
            reg(a);
        } else if (strcmp(inp, "REMOVE") == 0) {
            int a;
            scanf("%d", &a); gc
            remove(a);
        } else if (strcmp(inp, "CALL") == 0) {
            call();
        }
    } while (1);
    return 0;
}