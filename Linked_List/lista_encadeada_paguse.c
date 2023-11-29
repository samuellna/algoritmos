#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int key;
    struct no *next;
} node;

void initialize_list(node **head);
node *list_insert(node *h, int key_insert);
void print_list(node *list);

int main(void){
    node *list = NULL;
    int option;
    int key;

    initialize_list(&list);
    do{
        printf("\tLinked List\n1... Insert in the list\n5... Print list\n6... Clear screen\n0... Quit\nType one of these options: ");
        scanf("%d", &option);

        switch(option){
            case 1:
                printf("Key: ");
                scanf("%d", &key);
                list = list_insert(list, key);
            break;
            
            case 5:
                print_list(list);
            break;

            case 6:
                system("cls");
            break;

            default:
                if(option != 0) printf("Invalid option.\n");
                else printf("Goodbye!\n");
            break;
        }
    }while(option != 0);

    return 0;
}

void initialize_list(node **head){
    *head = (node *) malloc(sizeof(node)); // Memory allocation in head
    if(!head){
        printf("There was an error in memory allocation to initialize the list.\n");
        exit(1);
    }
    (*head)->next = NULL;
    // This function basically creates the head and makes it appoint to null.
}

node *list_insert(node *h, int key_insert){
    node *new_node = (node *) malloc(sizeof(node));
    if(!new_node){
        printf("There was an error in memory allocation to add a new node.\n");
        exit(1);
    }
    new_node->key = key_insert;
    new_node->next = h->next;
    h->next = new_node;
    return h;
}

void print_list(node *list){
    node *aux = list;
    while(aux->next){
        printf("%d", aux->next->key);
        aux = aux->next;
        if(aux->next) printf(" -> ");
    }
    printf("\n");
}