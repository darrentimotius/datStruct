#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 200

struct Data {
    char name[100];
    int key = -1;
}*hash[HASH_SIZE];

long long int getHashKey(const char* name) {
    int l = strlen(name);

    long long int sumASCII = 1;
    for (int i = 0; i < l; i++) {
        sumASCII *= name[i];
    }

    sumASCII %= 1000;
    return sumASCII % HASH_SIZE;
}

void createData(const char* name, int key) {
    Data *c = (Data*)malloc(sizeof(Data));

    long long int hashLoc = getHashKey(name);
    strcpy(c->name, name);
    c->key = key;

    if (hash[hashLoc] == NULL) {
        hash[hashLoc] = c;
    } else {
        while (hash[hashLoc] != NULL) {
            hashLoc = (hashLoc + 1) % HASH_SIZE;
        }
        hash[hashLoc] = c;
    }
}

void viewData() {
    bool found = false;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash[i] != NULL) {
            printf("%d. %s-%d\n", i + 1, hash[i]->name, hash[i]->key);
            found = true;
        }
    }
    if (!found) puts("There is no data!");
}

int main() {
    createData("pineapple", 45);
    createData("papaya", 32);
    createData("banana", 12);
    createData("coconut", 67);

    viewData();
    return 0;
}