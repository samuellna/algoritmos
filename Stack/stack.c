#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int key;
    struct no *next;
} node;

void initialize_stack(node **head);
node *push(node *h, int key_insert, int *size);
node *pop(node *head, int *size);
void print_list(node *list);

int main(void){
    node *head = NULL;
    int size_stack = 0;
    int option;
    int key;

    initialize_stack(&head);
    do{
        printf("\tLinked List\n1... Insert in the stack\n2... Remove top\n5... Print list\n6... Clear screen\n0... Quit\nType one of these options: ");
        scanf("%d", &option);

        switch(option){
            case 1:
                printf("Key: ");
                scanf("%d", &key);
                head = push(head, key, &size_stack);
            break;

            case 2:
                if(size_stack > 0) head = pop(head, &size_stack);
                else printf("The stack is empty.\n");
            break;
            
            case 5:
                print_list(head);
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

void initialize_stack(node **head){
    *head = (node *) malloc(sizeof(node)); // Memory allocation in head
    if(!head){
        printf("There was an error in memory allocation to initialize the list.\n");
        exit(1);
    }
    (*head)->key = -1;
    (*head)->next = NULL;
    // This function basically creates the head and makes it appoint to null.
}

node *push(node *h, int key_insert, int *size){
    node *new_node = (node *) malloc(sizeof(node));
    if(!new_node){
        printf("There was an error in memory allocation to add a new node.\n");
        exit(1);
    }
    new_node->key = key_insert;
    new_node->next = h->next;
    h->next = new_node;
    (*size)++;
    return h;
}

node *pop(node *head, int *size){
    node *remove_node = head->next;
    head->next = remove_node->next;
    printf("The head with %d as keynumber got removed from the stack.\n", remove_node->key);
    free(remove_node);
    (*size)--;
    return head;
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