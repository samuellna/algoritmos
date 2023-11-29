#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int X;
    int W;
    int R;
} dispositivo;

typedef struct t{
    dispositivo d;
    int bf;
    int height;
    struct t *right;
    struct t *left;
} Tree;

// Tree functions
Tree *create_leaf();
Tree *rotate_left(Tree *tree);
Tree *rotate_right(Tree *tree);
Tree *AVL_insert(Tree *tree, int value, int bytes, bool *height_changed);
Tree *AVL_search(Tree *tree, int value);
Tree *AVL_delete_min(Tree *tree, int *v);
Tree *AVL_remove(Tree *tree, int value);

// Tratar strings
int ID_dispositivo(char string[], int *index);
int qtd_bytes(char string[], int *index);

// Printing functions
void print_menu();
void pre_order(Tree *tree);
void in_order(Tree *tree);
void post_order(Tree *tree);

int main(void){
    Tree *tree = NULL;
    char *comando = (char *) malloc(sizeof(char));
    bool hc;

    while(scanf(" %[^\n]", comando) && comando[0] != 'E'){
        int index = 4;
        int id = ID_dispositivo(comando, &index);

        if(comando[0] == 'A'){
            int num_bytes = qtd_bytes(comando, &index);
            tree = AVL_insert(tree, id, num_bytes, &hc);
        }
        else{
            Tree *aux;
            aux = AVL_search(tree, id);
            printf("%d\n", comando[0] == 'W' ? aux->d.W: aux->d.R);
            free(aux);
        }
    }

    free(tree);
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
    New_Leaf->d.R = 0;
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

Tree *AVL_insert(Tree *tree, int value, int bytes, bool *height_changed){
    if(!tree){
        Tree *new_node = create_leaf();
        new_node->d.X = value;
        new_node->d.W = bytes;
        new_node->bf = 0;
        (*height_changed) = true;
        return new_node;
    }
    else if(value == tree->d.X){ // AVL doesn't accept repeated elements.
        (*height_changed) = false;
        return tree;
    }
    else if(value < tree->d.X){
        tree->left = AVL_insert(tree->left, value, bytes, height_changed);
        tree->bf = ((*height_changed) == true ? tree->bf - 1: tree->bf);
    }
    else{
        tree->right = AVL_insert(tree->right, value, bytes, height_changed);
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

Tree *AVL_search(Tree *tree, int value){
    if(!tree) return NULL;
    if(value == tree->d.X) return tree;
    else if(value > tree->d.X) return AVL_search(tree, value);
    else return AVL_search(tree, value);
}

Tree *AVL_delete_min(Tree *tree, int *v){
    if(!tree->left){
        Tree *min = tree->right;
        (*v) = tree->d.X;
        free(tree);
        return min;
    }
    else{
        tree->left = AVL_delete_min(tree, v);
        return tree;
    }
}

Tree *AVL_remove(Tree *tree, int value){
    if(!tree){
        printf("Empty tree\n");
        return NULL;
    }
    if(value == tree->d.X){ // If the node got found.
        Tree *rem;
        if(!tree->right){
            rem = tree->left; // Promoting left's son.
            free(tree);
            return rem;
        }
        else if(!tree->left){
            rem = tree->right; // Promoting right's son.
            free(tree);
            return rem;
        }
        else{
            // printf("%d tem 2 filhos.\n", tree->value);
            int v = 0;
            tree->right = AVL_delete_min(tree, &v); // Promoting the lessest right's subtree soon. 
            tree->d.X = v;
            return tree;
        }
    }
    else{
        if(value > tree->d.X){
            tree->right = AVL_remove(tree, value);
            return tree;
        }
        else{
            tree->left = AVL_remove(tree, value);
            return tree;
        }
    }
}
// ID e numero de bytes.


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
void print_menu(){
    printf("\t...AVL...\n");
    printf("1... Insert a node in the tree\n2... Remove a node\n3... Search a value in the tree\n4... Print tree\n5... Clear the screen\n0... Exit program\nType one of these options: ");
}

void pre_order(Tree *tree){
    if(!tree) return ;
    printf("%d ", tree->d.X);
    pre_order(tree->left);
    pre_order(tree->right);
}

void in_order(Tree *tree){
    if(!tree) return ;
    in_order(tree->left);
    printf("%d ", tree->d.X);
    in_order(tree->right);
}

void post_order(Tree *tree){
    if(!tree) return ;
    post_order(tree->left);
    printf("%d ", tree->d.X);
    post_order(tree->right);
}