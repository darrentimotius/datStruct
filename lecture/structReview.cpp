#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mahasiswa {
    char NIM[10];
    char nama[50];
};

int main() {
    // mahasiswa ppti21[100];
    // strcpy(ppti21[0].NIM, "2897347632");

    // printf("%s\n", ppti21[0].NIM);

    mahasiswa* ppti = (mahasiswa*)malloc(sizeof(mahasiswa));
    return 0;
}