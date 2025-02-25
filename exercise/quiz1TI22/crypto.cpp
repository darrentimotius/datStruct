#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 50

struct Data{
    char coin[5];
    double price;
    Data *next;
} *arr[SIZE];

int midSquare(char coin[]){
    /*
    Step Melakukan Mid Square Division :
    1. Jumlahin ASCII tiap hurufnya
    misal : "BTC" = B + T + C

    2. Kuadratin total ASCIInya
    Misal :
    BTC -> ASCIINYA = 10
    Kuadratnya = 10 * 10 = 100

    3. Convert dari Integer ke String pake sprintf

    4. Ambil tengahnya
    Misal = 616 -> ganjil
    Tengahnya = 1

    Misal : 6161 -> genap
    Tengahnya = 16

    5. Tengah % Hash Size
    */

    // Step 1
    int sumASCII = 0;
    for (int i = 0; i < strlen(coin); i++) {
        sumASCII += coin[i];
    }

    // Step 2
    sumASCII *= sumASCII;
    // sumASCII = sumASCII * sumASCII;

    // Step 3
    char arrASCII[10000];
    sprintf(arrASCII, "%d", sumASCII);

    printf("ASCII = %s\n", arrASCII);

    // Step 4
    int l = strlen(arrASCII);
    int key = 0;
    if (l % 2 == 1) { // Ganjil (ga perlu atoi karena atoi itu string -> integer)
        key = arrASCII[l / 2] - '0';
        printf("key = %d\n", key);
    } else { // Genap (pake atoi karena genap itu string (lebih dari 1 huruf))
        char mid[3] = {arrASCII[l / 2], arrASCII[l / 2 + 1], '\0'}; // Wajib ada '\0' di paling belakang supaya dianggap sebagai string
        key = atoi(mid);
        printf("key = %d\n", key);
    }
    
    return key % SIZE;
}

void insert(char coin[], double price){
    Data *data = (Data*)malloc(sizeof(Data));

    data->price = price;
    strcpy(data->coin, coin);
    data->next = NULL;

    int index = midSquare(coin);
    //Insert with chaining collision handling
    if (arr[index] == NULL) {
        arr[index] = data;
    } else {
        Data* temp = arr[index];
        // Push Tail
        while (temp->next != NULL) { // Berhenti tepat di sebelum kita masukin
            temp = temp->next;
        }
        temp->next = data;
    }
}

void view() {
    for (int i = 0; i < SIZE; i++) {
        Data* temp = arr[i];
        
        if (temp == NULL) continue;
        printf("%d. ", i);
        while (temp != NULL) {
            printf("%s %.2lf -> ", temp->coin, temp->price);
            temp = temp->next;
        }
        puts("");
    }
}

int main(){
    insert("BTC", 97000.00);
    insert("ETH", 2700.00);
    insert("SOL", 172.59);
    insert("XRP", 2.57);

    view();

    return 0;
}
