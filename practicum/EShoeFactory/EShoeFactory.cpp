#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Shoes{
	char name[101];
	int stock;
	long long price;
	char id[101];
	Shoes* left;
	Shoes* right;
	int height;
}*root = NULL;

void menu(){
	puts("EShoe Factory");
	puts("=================");
	puts("1. View Stock");
	puts("2. Insert New Shoe");
	puts("3. Delete Shoe");
	puts("4. Exit");
}

char* generateID(char name[]){
	char* id = (char*)malloc(11 * sizeof(char));
	char X;
	if (name[0] >= 'a' && name[0] <= 'z'){
		X = name[0] - 'a' + 'A';
	} else {
		X = name[0];
	}
	
	int Y = rand()%1000;
	sprintf(id, "%c%03d", X, Y);
	return id;
}

//buat node AVL
Shoes* makeShoe(char name[], int stock, long long price, char id[]){
    Shoes* node = (Shoes*)malloc(sizeof(Shoes));
    strcpy(node->name, name);
    node->stock = stock;
    node->price = price;
    strcpy(node->id, id);
    node->left = node->right = NULL;
    node->height = 1; // default height
    return node;
}

int height(Shoes* root){
	if(root == NULL){
		return 0;
	} else{
		root->height;
	}
}

int max(int a, int b){
	if (a > b){
		return a;
	} else {
		return b;
	}
}

int getBf(Shoes* root){
	if(root == NULL){
		return NULL;
	}
	return height(root->left) - height(root->right);
}

Shoes* rightRotate(Shoes* temp){
	Shoes* kiri = temp->left;
	Shoes* anak_kanan_si_kiri = kiri->left;
	kiri->right = temp;
	temp->left = anak_kanan_si_kiri;
	temp->height = max(height(temp->left), height(temp->right));
	kiri->height = max(height(kiri->left), height(kiri->right));
	return kiri;
}

Shoes* leftRotate(Shoes* temp){
	Shoes* kanan = temp->right;
	Shoes* anak_kiri_si_kanan = kanan->left;
	kanan->left = temp;
	temp->right = anak_kiri_si_kanan;
	temp->height = max(height(temp->left), height(temp->right));
	kanan->height = max(height(kanan->left), height(kanan->right));
	return kanan;
}

Shoes* insertShoe(Shoes* root, Shoes* node){
	if(root == NULL){
		return node;
	} else if(strcmp(root->id, node->id) == 0){
		return NULL;
	} else if(strcmp(root->id, node->id) < 0){ //node yang dimasukin lebih besar dari root, jadi ke kanan
		root->right = insertShoe(root->right, node);
	} else if(strcmp(root->id, node->id) > 0){
		root->left = insertShoe(root->left, node);
	}
	
	root->height = 1 + max(height(root->left), height(root->right));
	
	//cari balance
	int bf = getBf(root);
	
	if(bf > 1 && strcmp(node->id, root->left->id)<0){
		return rightRotate(root);
	}
	
	if(bf > 1 && strcmp(node->id, root->left->id)>0){
		root->left = leftRotate(root);
		return rightRotate(root);
	}
		
	if(bf > -1 && strcmp(node->id, root->left->id)<0){
		return leftRotate(root);
	}
	
	if(bf > -1 && strcmp(node->id, root->left->id)>0){
		root->right = rightRotate(root);
		return leftRotate(root);
	}
	
	return root;
}

void insert(){
	char name[101];
	int stock;
	long long price;
	char id[101];
	
	int length;
	do{
		printf("Input Shoes Name [between 5 and 20 character]: ");
		scanf("%s", name); getchar();
		length = strlen(name);
	}while(length < 5 || length > 20);
	
	do{
		printf("Input Shoes Stock: ");
		scanf("%d", &stock); getchar();
	}while(stock <= 0);
	
	do{
		printf("Input Shoes Price [between 500000 and 520000]: ");
		scanf("%lld", &price); getchar();
	}while(price < 500000 || price > 520000);
	
	strcpy(id, generateID(name));
	
	printf("%s\n", name);
	printf("%d\n", stock);
	printf("%lld\n", price);
	printf("%s\n", id);
	
	Shoes* node = makeShoe(name, stock, price, id);
	root = insertShoe(root, node);
}

void preOrder(Shoes* root){
	if(root != NULL){
		printf("%-10s | %-20s | %-3d | %-6d |\n", root->id, root->name, root->stock, root->price);
		preOrder(root->left);
		preOrder(root->right);
	}	
}

void inOrder(Shoes* root){
	if(root != NULL){
		inOrder(root->left);
		printf("%-10s | %-20s | %-3d | %-6d |\n", root->id, root->name, root->stock, root->price);
		inOrder(root->right);
	}	
}

void postOrder(Shoes* root){
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("%-10s | %-20s | %-3d | %-6d |\n", root->id, root->name, root->stock, root->price);
	}	
}

void view(){
	if (root == NULL){
		puts("There is no data");
		return;
	} else {
		int choice = -1;
		puts("View Menu");
		puts("=================");
		puts("1. Pre Order");
		puts("2. In Order");
		puts("3. Post Order");
		do{
			printf(">>");
			scanf("%d", &choice); getchar();
		} while(choice < 1 || choice > 3);
		switch(choice){
			case 1:
				preOrder(root);
				break;
			case 2:
				inOrder(root);
				break;
			case 3:
				postOrder(root);
				break;
		}	
	}
}

Shoes* search(Shoes* root, char id[11]){
	if(root == NULL){
		return NULL;
	} else if (strcmp(id, root->id) < 0){
		return search(root->left, id);
	} else if (strcmp(id, root->id) > 0){
		return search(root->right, id);
	} else {
		return root;
	}
}

Shoes* successor(Shoes* node){
    Shoes* curr = node;
    while (curr && curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}

Shoes* deletShoe(Shoes* root, char id[]){
    if (root == NULL){
        return NULL;
    }

    if (strcmp(id, root->id) < 0){
        root->left = deletShoe(root->left, id);
    } else if (strcmp(id, root->id) > 0){
        root->right = deletShoe(root->right, id);
    } else {
        // Node ditemukan
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        } else if (root->left == NULL){
            Shoes* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL){
            Shoes* temp = root->left;
            free(root);
            return temp;
        } else {
            Shoes* temp = successor(root->right);  // ? gunakan subtree kanan untuk successor
            strcpy(root->id, temp->id);
            strcpy(root->name, temp->name);
            root->stock = temp->stock;
            root->price = temp->price;
            root->right = deletShoe(root->right, temp->id);
        }
    }

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Cek balance
    int bf = getBf(root);

    // Left Left Case
    if (bf > 1 && getBf(root->left) >= 0){
        return rightRotate(root);
    }

    // Left Right Case
    if (bf > 1 && getBf(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (bf < -1 && getBf(root->right) <= 0){
        return leftRotate(root);
    }

    // Right Left Case
    if (bf < -1 && getBf(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void del(){
	char id[11];
	char option[4];
	if(root == NULL){
		puts("There is no data!");
		return;
	} else {
		inOrder(root);
		printf("Input Shoes ID to be deleted: ");
		scanf("%s", &id);
		if(search(root, id) != NULL){
			do{
				printf("Are u sure u want to delete? ");
				scanf("%s", option);
			}while(strcmp(option, "Yes") != 0 && strcmp(option, "No") != 0);
			
			if(strcmp(option, "Yes") == 0){
				deletShoe(root, id);
				puts("Shoe deleted successfully!");
			} else{
				puts("Delete cancelled.");
			}
		} else{
			puts("ID not found!");
		}
	}
}

int main(){
	srand(time(NULL));
	int choice = -1;
	do{
		menu();
		do{
			printf(">> ");
			scanf("%d", &choice); getchar();
		}while(choice < 1 || choice > 4);
		switch(choice){
			case 1:
				view();
				break;
			case 2:
				insert();
				break;
			case 3:
				del();
				break;
			case 4:
				exit(0);
		}
	}while(1);
}