#include <stdio.h>
#include <stdlib.h>

struct Student {
    int age;
    int height;
}arrStudent[10];

int main() {
    Student student;
    student.age = 20;
    student.height = 158;
    // int a = 10;
    // int* ptr = &a;

    // printf("memory dari ptr: %d\n", &ptr);
    // printf("value dari ptr: %d\n", ptr);
    // printf("memory dari a: %d\n", &a);
    // printf("value dari memory yang disimpan: %d\n", *ptr);

    // *ptr = 20;
    // printf("nilai a sekarang : %d\n", a);

    // memory allocation example
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 20;

    printf("alamat baru : %d, value dari alamat : %d\n", ptr, *ptr);

    // Alokasi memori untuk struct
    Student* ptr2 = (Student*)malloc(sizeof(Student));

    // Akses anggota dari struct pointer
    ptr2->age = 21;
    ptr2->height = 175;

    printf("age : %d, height : %d\n", ptr2->age, ptr2->height);

    free(ptr2);
    arrStudent[0].age = 12;
    arrStudent[1].age = 13;
    return 0;
}