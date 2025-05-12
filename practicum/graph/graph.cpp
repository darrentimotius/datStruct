#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Jumlah vertex = 5
#define MAX 5

void createMatrix(int matrix[][MAX], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0;
        }
    }
}

void addEdgeMatrix(int matrix[][MAX], int src, int dst) {
    matrix[src][dst] = 1; // Kalo punya jalur, tandain 1
    matrix[dst][src] = 1;
}

void bfsMatrix(int matrix[][MAX], int vertices, int startVertex) {
    // Step 1 : Initialize Visited Matrix
    bool visited[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false; // Di awal, belum ada vertex yang di visit
    }

    // Step 2 : Initialize Queue
    int queue[100];
    int front = 0; // Depan queuenya
    int rear = 0; // Belakang queuenya

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    // Kita pengen looping untuk BFS
    while (front < rear) { // Selama masi ada node di dalam queue = ga bakal sama
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Kita pengen explore vertex tersebut punya neighbors
        for (int i = 0; i < vertices; i++) {
            // Untuk cek apakah ada edge
            if (matrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true; 
                queue[rear++] = i;
            }
        }
    }
    puts("");
}

void dfsMatrix(int matrix[][MAX], int vertices, int startVertex) {
    // Step 1 : Initialize Visited Matrix
    bool visited[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false; // Di awal, belum ada vertex yang di visit
    }

    int stack[100], top = -1; // Kalo stack empty -> Top -1
    stack[++top] = startVertex;

    while (top >= 0) {
        int currentVertex = stack[top--];

        if (!visited[currentVertex]) {
            printf("%d ", currentVertex);
            visited[currentVertex] = true;
        }

        // Visit semua neighbor dari gede ke kecil karena stack
        for (int i = vertices - 1; i >= 0; i--) {
            if (matrix[currentVertex][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
    puts("");
}

void printMatrix(int matrix[][MAX], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        puts("");
    }
}

int main() {
    int vertices = MAX;

    int matrix[MAX][MAX];
    createMatrix(matrix, vertices);

    addEdgeMatrix(matrix, 0, 1);
    addEdgeMatrix(matrix, 0, 2);
    addEdgeMatrix(matrix, 1, 2);
    addEdgeMatrix(matrix, 1, 3);
    addEdgeMatrix(matrix, 2, 4);

    puts("Adjacency Matrix :");
    printMatrix(matrix, vertices);
    puts("");
    
    puts("BFS Matrix :");
    bfsMatrix(matrix, vertices, 0);
    puts("");

    puts("DFS Matrix :");
    dfsMatrix(matrix, vertices, 0);
    return 0;
}