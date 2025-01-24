#include<stdio.h>
#include<stdlib.h>

struct nodes{
    int value;
    nodes* next;
    nodes* prev;
}*h, *t, *c;

void printNodes(){
    nodes *temp = h;
    if (!h){
        puts("No nodes available");getchar();
        return;
    }
    while (temp != NULL){
        if(!(temp->next == NULL))printf("%d - ", temp->value);
        else printf("%d\n", temp->value);
        temp = temp->next;
    }getchar();
}

void pushHead(int nilai){
    c = (nodes*) malloc (sizeof(nodes));
    c->value = nilai;
    c->next = NULL;
    c->prev = NULL;

    if (!h) h = t = c;
    else {
        c->next = h;
        h->prev = c;
        h = c;
    }
    printNodes();
}

void pushTail(int nilai){
    c = (nodes*) malloc (sizeof(nodes));
    c->value = nilai;
    c->next = NULL;
    c->prev = NULL;

    if (!h) h = t = c;
    else {
        t->next = c;
        c->prev = t;
        t = c;
    }
    printNodes();
}

void popHead(){
    if (!h){
        puts("No nodes available");getchar();
        return;
    }
    nodes *temp = h;
    if (h != t){
        h = temp->next;
        h->prev = NULL;
        printf("Nilai Keluar : %d\n", temp->value);
        free(temp);
    }else {
        printf("Nilai Keluar : %d\n", h->value);
        free(h);
        h = t = NULL;
    }
    printNodes();
}

void popTail(){ // karena pake double link list
    if (!h){
        puts("No nodes available");getchar();
        return;
    }
    nodes *temp = t;
    if (t != h){
        t = temp->prev;
        t->next = NULL;
        printf("Nilai Keluar : %d\n", temp->value);
        free(temp);
    }else {
        printf("Nilai Keluar : %d\n", t->value);
        free(t);
        h = t = NULL;
    }

    // Kalo single link list
    // temp = h;
    // while (temp->next != t) temp = temp->next;
    // 
    // nodes *del = temp->next; // nanti berada di Tail
    // t = temp;
    // t->next = NULL;
    // free(del);
    printNodes();
}

void reset(){
    nodes *temp = h, *del;
    while (temp != NULL){
        del = temp;
        temp = temp->next;
        free(del);
    }
    h = t = NULL;

    printNodes();
}

/*
Konsep Queue
Fisrt In First Out -> Masuk pertama Keluar pertama
push head -> pop tail 
push tail -> pop head
*/

/*
Konsep Stack
Last In First Out -> Masuk terakhir Keluar pertama
push head -> pop head
push tail -> pop tail
*/


void queue(){
    int input;
    do {
        system("cls");
        puts("Simulasi Queue");
        puts("1. Push");
        puts("2. Pop");
        puts("3. Back");
        do {
            printf(">> ");scanf("%d", &input);getchar();
        }while (!(1<=input && input<= 3));
        
        int nilai;
        switch(input){
            case 1:printf("Nilai : ");scanf("%d", &nilai);getchar();pushHead(nilai);break;
            case 2:popTail();break;
            case 3:reset(); return; break;
        }
    } while(1);
}

void stack(){
    int input;
    do {
        system("cls");
        puts("Simulasi Stack");
        puts("1. Push");
        puts("2. Pop");
        puts("3. Back");
        do {
            printf(">> ");scanf("%d", &input);getchar();
        }while (!(1<=input && input<= 3));
        
        int nilai;
        switch(input){
            case 1:printf("Nilai : ");scanf("%d", &nilai);getchar();pushHead(nilai);break;
            case 2:popHead();break;
            case 3:reset(); return; break;
        }
    } while(1);
}


int main(){
    int input;
    do{
        system("cls");
        puts("1. Queue");
        puts("2. Stack");
        puts("3. Exit");
        do {
            printf(">> ");scanf("%d", &input);getchar();
        }while (!(1<=input && input<=3));
        switch(input){
            case 1: queue();break;
            case 2: stack();break;
            case 3: return 0;break;
        }
    }while (1);
}