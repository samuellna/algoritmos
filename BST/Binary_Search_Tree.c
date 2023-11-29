#include <stdio.h>
#include <stdlib.h>

typedef struct leaf{
    int value;
    struct leaf *right;
    struct leaf *left;
} Tree;

int height_tree = 0;

Tree *create_leaf();
Tree *BST_insert(int value, Tree *root);
Tree *BST_delete_min(Tree *root, int *v);
Tree *BST_remove(Tree *root, int value);
int set_heigth(Tree *tree);

// Print:
void print_menu();
void pre_order(Tree *tree);
void in_order(Tree *tree);
void post_order(Tree *tree);

int main(void){
    Tree *root = NULL;
    int option;
    int value;

    do{
        print_menu();
        scanf("%d", &option);

        switch(option){
            case 1:
                printf("Value to insert: ");
                scanf("%d", &value);
                root = BST_insert(value, root);
                height_tree = set_heigth(root);
            break;

            case 2:
                printf("Value to remove: ");
                scanf("%d", &value);
                root = BST_remove(root, value);
                height_tree = set_heigth(root);
            break;

            case 4:
                in_order(root);
                printf("\n");
            break;
            
            case 5:
                system("cls");
            break;

            default:
                if(option) printf("Invalid option.\n");
                else printf("Goodbye :)\n");
            break;
        }
        printf("\n");

    }while(option != 0);

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

Tree *BST_insert(int value, Tree *root){
    if(!root){
        Tree *l = create_leaf();
        l->value = value;
        return l;
    }
    if(value < root->value){
        root->left = BST_insert(value, root->left);
        return root;
    }
    else{
        root->right = BST_insert(value, root->right);
        return root;
    }
}

Tree *BST_delete_min(Tree *root, int *v){
    if(!root->left){
        Tree *min = root->right;
        (*v) = root->value;
        free(root);
        return min;
    }
    else{
        root->left = BST_delete_min(root->left, v);
        return root;
    }
}

Tree *BST_remove(Tree *root, int value){
    if(!root){
        printf("Empty tree\n");
        return NULL;
    }
    if(value == root->value){ // If the node got found.
        Tree *rem;
        if(!root->right){
            rem = root->left; // Promoting left's son.
            free(root);
            return rem;
        }
        else if(!root->left){
            rem = root->right; // Promoting right's son.
            free(root);
            return rem;
        }
        else{
            printf("%d tem 2 filhos.\n", root->value);
            int v = 0;
            root->right = BST_delete_min(root->right, &v); // Promoting the lessest right's subtree soon. 
            root->value = v;
            return root;
        }
    }
    else{
        if(value > root->value){
            root->right = BST_remove(root->right, value);
            return root;
        }
        else{
            root->left = BST_remove(root->left, value);
            return root;
        }
    }
}

int set_heigth(Tree *root){
    if(!root) return 0;
    int heigth_left = set_heigth(root->left);
    int heigth_right = set_heigth(root->right);
    return 1 + (heigth_left > heigth_right ? heigth_left: heigth_right);
}

// Printing:

void print_menu(){
    printf("\t...BST...\n");
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