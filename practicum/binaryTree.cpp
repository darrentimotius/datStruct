#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[101];
    struct Student *left, *right;
};

struct Student *createStudent(int id, char *name){
    struct Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

struct Student *insert(struct Student *root, int id, char *name){
    //case 1: kalo treenya belum kebuat, kita buat root nodenya
    if(root == NULL){
        return createStudent(id, name);
    }
    //case 2: id yang mau kita insert > current node punya ID
    else if (id > root->id){
        root->right = insert(root->right, id, name); //rekursinya
    }
    //case 3: id yang mau kita insert < current node punya ID
    else if(id < root->id){
        root->left = insert(root->left, id, name);
    }
    //case 4: kalo valuenya udh ada (duplicate), kita return nodenya aja
    return root;
}
//inorder = left, print, right
//preorder = 
void inorder(struct Student *root){
    if(root == NULL) return;
    inorder(root->left);
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    inorder(root->right);
}
//preorder = print, left, right 
void preorder(struct Student *root){
    if(root == NULL) return;
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    preorder(root->left);
    preorder(root->right);
}

//preorder = left, right, print 
void postorder(struct Student *root){
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
}
struct Student *search(struct Student *root, int id){
    //case 1: kalo search ga ketemu
    if(root == NULL){
        puts("Not Found");
        return NULL;
    }

    //case 2: kalo search ketemu
    else if(root->id == id){
        puts("Found");
        return root;
    }

    //case 3: kalo id yang mau di search itu lebih besar dari current id
    else if(id > root->id){
        return search(root->right, id);
    }

    //case 4: kalo id yang mau di search itu lebih kecil dari current id
    else {
        return search(root->left, id);
    }
}

struct Student *update(struct Student *root, int id, char *name){
    //case 1: kalo search ga ketemu
    if(root == NULL){
        puts("Not Found");
        return NULL;
    }

    //case 2: kalo search ketemu tinggal ganti namanya
    else if(root->id == id){
        puts("Found");
        strcpy(root->name, name);
        return root;
    }

    //case 3: kalo id yang mau di search itu lebih besar dari current id
    else if(id > root->id){
        return update(root->right, id, name);
    }

    //case 4: kalo id yang mau di search itu lebih kecil dari current id
    else {
        return update(root->left, id, name);
    }
}


int main(){
    struct Student *root = NULL;

    puts("Inserting... ");
    root = insert(root, 3, "bill");
    root = insert(root, 1, "tom");
    root = insert(root, 16, "jake");
    root = insert(root, 78, "diana");
    root = insert(root, 33, "eve");
    root = insert(root, 78, "diana");
    root = insert(root, 78, "diana");
    root = insert(root, 178, "cxzczczc");
    root = insert(root, 278, "asd");
    root = insert(root, 378, "a");
    root = insert(root, 37, "bbbbbb");
    root = insert(root, 12, "cccc");
    
    puts("Inserted Successful");

    //tracersal
    puts("Inorder Traversal");
    inorder(root);

    //searching
    struct Student *searchedStudent = search(root, 378);
    if(searchedStudent != NULL){
        printf("Found Student with id %d and name %s\n", searchedStudent->id, searchedStudent->name);
    }

    //updated
    puts("\nupdating\n");
    struct Student *updatedStudent = update(root, 1, "tommy");
    if(updatedStudent != NULL){
        printf("updating Student with id %d and name %s\n", updatedStudent->id, updatedStudent->name);
    }

    puts("traversal after updating: ");
    inorder(root);
    return 0;
}