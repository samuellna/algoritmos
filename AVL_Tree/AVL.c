#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct t{
    int value;
    int bf;
    int height;
    struct t *right;
    struct t *left;
} Tree;

Tree *create_leaf();
Tree *rotate_left(Tree *tree);
Tree *rotate_right(Tree *tree);
Tree *AVL_insert(Tree *tree, int value, bool *height_changed);
Tree *AVL_search(Tree *tree, int value);
Tree *AVL_delete_min(Tree *tree, int *v);
Tree *AVL_remove(Tree *tree, int value);

// Printing functions
void print_menu();
void pre_order(Tree *tree);
void in_order(Tree *tree);
void post_order(Tree *tree);

int main(void){
    Tree *t = NULL;
    int value;
    int option;
    bool hc;

    do{
        print_menu();
        scanf("%d", &option);

        switch(option){
            case 1:
                printf("Value: ");
                scanf("%d", &value);
                t = AVL_insert(t, value, &hc);
            break;

            case 2:
                printf("Value: ");
                scanf("%d", &value);
                t = AVL_remove(t, value);
            break;

            case 3:
                printf("Value to search: ");
                scanf("%d", &value);
                if(AVL_search(t, value)) printf("%d is in the tree.\n", value);
                else printf("%d isn't in the tree.\n", value);
            break;

            case 4:
                in_order(t);
                printf("\n");
            break;

            case 5:
                system("cls");
            break;
            
            default:
                if(option != 0) printf("Invalid option.\n");
                else printf("Bye :)\n");
            break;
        }
    }while(option != 0);
    free(t);
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

Tree *AVL_insert(Tree *tree, int value, bool *height_changed){
    if(!tree){
        Tree *new_node = create_leaf();
        new_node->value = value;
        new_node->bf = 0;
        (*height_changed) = true;
        return new_node;
    }
    else if(value == tree->value){ // AVL doesn't accept repeated elements.
        (*height_changed) = false;
        return tree;
    }
    else if(value < tree->value){ 
        tree->left = AVL_insert(tree->left, value, height_changed);
        tree->bf = ((*height_changed) == true ? tree->bf - 1: tree->bf);
    }
    else{
        tree->right = AVL_insert(tree->right, value, height_changed);
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
    if(value == tree->value) return tree;
    else if(value > tree->value) return AVL_search(tree->right, value);
    else return AVL_search(tree->left, value);
}

Tree *AVL_delete_min(Tree *tree, int *v){
    if(!tree->left){
        Tree *min = tree->right;
        (*v) = tree->value;
        free(tree);
        return min;
    }
    else{
        tree->left = AVL_delete_min(tree->left, v);
        return tree;
    }
}

Tree *AVL_remove(Tree *tree, int value){
    if(!tree){
        printf("Empty tree\n");
        return NULL;
    }
    if(value == tree->value){ // If the node got found.
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
            printf("%d tem 2 filhos.\n", tree->value);
            int v = 0;
            tree->right = AVL_delete_min(tree->right, &v); // Promoting the lessest right's subtree soon. 
            tree->value = v;
            return tree;
        }
    }
    else{
        if(value > tree->value){
            tree->right = AVL_remove(tree->right, value);
            return tree;
        }
        else{
            tree->left = AVL_remove(tree->left, value);
            return tree;
        }
    }
}

// Printing functions.
void print_menu(){
    printf("\t...AVL...\n");
    printf("1... Insert a node in the tree\n2... Remove a node\n3... Search a value in the tree\n4... Print tree\n5... Clear the screen\n0... Exit program\nType one of these options: ");
}

void pre_order(Tree *tree){
    if(!tree) return ;
    printf("%d ", tree->value);
    pre_order(tree->left);
    pre_order(tree->right);
}

void in_order(Tree *tree){
    if(!tree) return ;
    in_order(tree->left);
    printf("%d ", tree->value);
    in_order(tree->right);
}

void post_order(Tree *tree){
    if(!tree) return ;
    post_order(tree->left);
    printf("%d ", tree->value);
    post_order(tree->right);
}