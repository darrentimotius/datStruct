//
//  main.c
//  DoubleLinkedList
//

#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int valueNode;
    struct tnode *next;
    struct tnode *prev;
}*h,*t,*c;

void pushHead(int value)
{
    c = (struct tnode*) malloc(sizeof(struct tnode));
    c->valueNode = value;
    c->next = NULL;
    c->prev = NULL;
    if(!h){
        h=t=c;
    }else{
        c->next = h;
        h->prev = c;
        h = c;
    }
}

void pushTail(int value){
    c = (struct tnode*) malloc(sizeof(struct tnode));
    c->valueNode = value;
    c->next = NULL;
    c->prev = NULL;
    if(!h){
        h=t=c;
    }
    else{
        t->next = c;
        c->prev = t;
        t=c;
    }
}

void pushMiddle(int value){
    c = (struct tnode*) malloc(sizeof(struct tnode));
    c->valueNode = value;
    c->next = NULL;
    c->prev = NULL;
    if(!h){
        h=t=c;
    }
    else if (h->valueNode > value){
        c->next = h;
        h->prev = c;
        h = c;
    }
    else if (t->valueNode < value){
        t->next = c;
        c->prev = t;
        t=c;
    }
    else{
        struct tnode *temp;
        temp = h;
        while(value > temp->next->valueNode)
            temp=temp->next;
        c->next = temp->next;
        temp->next->prev = c;
        c->prev = temp;
        temp->next = c;
    }
}

void popHead(){
    if (h == NULL) return;
    struct tnode *temp = h;
    h = h->next;
    h->prev = NULL;
    free(temp);
}

void popTail(){
    if (t == NULL) return;
    struct tnode *temp = t->prev;
    t = temp;
    struct tnode *curr;
    curr = temp->next;
    temp->next = NULL;
    free(curr);
}

void popMiddle(int value)
{
    if (h == NULL) return;
    
    struct tnode *temp = h;
    
    while (temp->valueNode != value){
        temp = temp->next;
        if (temp == NULL)
            break;
    }
    
    if (temp == NULL) return;
    
    
    if (temp->valueNode == h->valueNode){
        h = h->next;
        h->prev = NULL;
        free(temp);
    }
    
    else if (temp->valueNode == t->valueNode){
        struct tnode *temp = h;
        while (temp->next->valueNode != t->valueNode){
            temp = temp->next;
        }
        free(t);
        t = temp;
        t->next = NULL;
    }
    
    else {
        struct tnode *temp = h;
        while (temp->next->valueNode != value){
            temp = temp->next;
        }
        struct tnode *curr;
        curr = temp->next;
        temp->next = curr->next;
        curr->next->prev = temp;
        free(curr);
        
    }
        
}


void PrintallNext(){
    struct tnode *temp = h;
    while (temp!=NULL){
        printf("%d ", temp->valueNode);
        temp=temp->next;
    }
    printf("\n");
}

void PrintallPrev(){
    struct tnode *temp = t;
    while (temp!=NULL){
        printf("%d ", temp->valueNode);
        temp=temp->prev;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    pushMiddle(1);
    pushMiddle(4);
    pushMiddle(2);
    pushMiddle(3);
    pushMiddle(6);
    pushMiddle(5);
    PrintallNext();
    PrintallPrev();
    popTail();
    popHead();
    PrintallNext();
    PrintallPrev();
    
    return 0;
}
