#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STR_SIZE 1000

typedef struct{
    int ID;
    int WEI;
    int RNK;
} Dispositivo;

typedef struct t{
    Dispositivo disp;
    int bf;
    struct t *right;
    struct t *left;
} Tree;

Tree *create_leaf();
Tree *rotate_left(Tree *tree);
Tree *rotate_right(Tree *tree);
Tree *AVL_insert(Tree *tree, int id, int wei, bool *height_changed);
Tree *AVL_search(Tree *tree, int id);

// ID e WEI do dispositivo.
int ID_dispositivo(char string[], int *index);
int qtd_bytes(char string[], int *index);

// Printing functions
void in_order(Tree *tree);

int main(void){
    char comando[STR_SIZE];
    Tree *t = NULL;
    bool hc;

    do{
        scanf(" %[^\n]", comando);
        if(comando[0] != 'E'){
            int index = 4;
            int id = ID_dispositivo(comando, &index);
            
            if(comando[0] == 'A'){
                int qtd_b = qtd_bytes(comando, &index);
                t = AVL_insert(t, id, qtd_b, &hc);
            }
            else{
                if(comando[0] == 'W'){
                    Tree *aux = AVL_search(t, id);
                    printf("%d\n", aux->disp.WEI);
                }
            }
        }
    }while(comando[0] != 'E');

    return 0;
}

Tree *create_leaf(){
    Tree *New_Leaf = (Tree *) malloc(sizeof(Tree));
    if(!New_Leaf){
        printf("There was an error to create a new leaf.\n");
        return NULL;
    }
    New_Leaf->left = NULL;
    New_Leaf->right = NULL;
    New_Leaf->disp.RNK = 0;
    return New_Leaf;
}

Tree *rotate_left(Tree *tree){
    Tree *R, *RL;
    R = tree->right;
    RL = R->left;
    R->left = tree;
    tree->right = RL;
    
    if(R->bf <= 0) tree->bf -= 1;
    else tree->bf = tree->bf - 1 - R->bf;

    if(tree->bf >= 0) R->bf -= 1;
    else R->bf = R->bf - 1 + tree->bf;

    return R;
}

Tree *rotate_right(Tree *tree){
    Tree *L, *LR;
    L = tree->left;
    LR = L->right;
    L->right = tree;
    tree->left = LR;

    if(L->bf <= 0) tree->bf -= 1;
    else tree->bf = tree->bf - 1 - L->bf;

    if(tree->bf >= 0) L->bf -=1;
    else L->bf = L->bf - 1 + tree->bf;
    
    return L;
}

Tree *AVL_insert(Tree *tree, int id, int wei, bool *height_changed){
    if(!tree){
        Tree *new_node = create_leaf();
        new_node->disp.ID = id;
        new_node->disp.WEI = wei;
        new_node->bf = 0;
        (*height_changed) = true;
        return new_node;
    }
    else if(id == tree->disp.ID){ // AVL doesn't accept repeated elements.
        (*height_changed) = false;
        return tree;
    }
    else if(id < tree->disp.ID){ 
        tree->left = AVL_insert(tree->left, id, wei, height_changed);
        tree->bf = ((*height_changed) == true ? tree->bf - 1: tree->bf);
    }
    else{
        tree->right = AVL_insert(tree->right, id, wei, height_changed);
        tree->bf = ((*height_changed) == true ? tree->bf + 1: tree->bf);
    }
    if(!(*height_changed)) return tree;
    else if(tree->bf == 0){
        (*height_changed) = false;
        return tree;
    }
    else if(tree->bf == 1 || tree->bf == -1){
        (*height_changed) = true;
        return tree;
    }
    else if(tree->bf == -2){
        if(tree->left->bf == 1) tree->left = rotate_left(tree->left);
        (*height_changed) = 0;
        return rotate_right(tree);
    }
    else if(tree->bf == 2){
        if(tree->right->bf == -1) tree->right = rotate_right(tree->right);
        (*height_changed) = 0;
        return rotate_left(tree);
    }
    return tree;
}

Tree *AVL_search(Tree *tree, int id){
    if(!tree) return NULL;
    if(id == tree->disp.ID) return tree;
    else if(id > tree->disp.ID) return AVL_search(tree->right, id);
    else return AVL_search(tree->left, id);
}

// ID e WEI do dispositivo.

int ID_dispositivo(char string[], int *index){
    int tam = strlen(string);
    int i = 0;
    char *str_aux = (char *) malloc(sizeof(char));

    while(string[(*index)] != ' ' && (*index) < tam){
        str_aux[i] = string[(*index)];
        (*index)++;
        i++;
    }
    str_aux[i] = '\0';
    return atoi(str_aux);
}

int qtd_bytes(char string[], int *index){
    int tam = strlen(string);
    int i = 0;
    char *str_aux = (char *) malloc(sizeof(char));

    while((*index) < tam){
        str_aux[i] = string[(*index)];
        (*index)++;
        i++;
    }
    str_aux[i] = '\0';
    return atoi(str_aux);
}

// Printing functions.
void in_order(Tree *tree){
    if(!tree) return ;
    in_order(tree->left);
    printf("%d ", tree->disp.ID);
    in_order(tree->right);
}