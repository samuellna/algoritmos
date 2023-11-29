#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 5

typedef struct no{
    int key;
    struct no *next;
} node;

void initialize_stack(node **head);
node *push(node *h, int key_insert, int *size_stack);
node *pop(node *head, int *size);

int main(void){
    node *head = NULL;
    int stack_size = 0;
    int number_cases, i = 0;
    char number_or_end[5];
    
    printf("Number of cases: ");
    scanf("%d", &number_cases);

    initialize_stack(&head);

    while(i < number_cases){
        printf("Command: ");
        scanf(" %[^\n]", number_or_end);
        if(strcmp(number_or_end, "END") != 0){
            int number = atoi(number_or_end); // Convertendo a string em um inteiro
            if(head->next){ // Se head->next existir, então há algum elemento na pilha
                // Fazendo as comparações para decidir se iremos inserir ou remover da pilha
                if(head->next->key != number) head = push(head, number, &stack_size); 
                else head = pop(head, &stack_size);
            }
            else head = push(head, number, &stack_size); // Se não houver, então adicionamos o 1o elemento na pilha.
        }
        else{
            printf("caso %d: %d %d\n", i, stack_size, (head->next ? head->next->key: head->key));
            while(stack_size > 0){
                head = pop(head, &stack_size);
            }
            i++;
        }
    }

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

node *push(node *h, int key_insert, int *size_stack){
    node *new_node = (node *) malloc(sizeof(node));
    if(!new_node){
        printf("There was an error in memory allocation to add a new node.\n");
        exit(1);
    }
    new_node->key = key_insert;
    new_node->next = h->next;
    h->next = new_node;
    (*size_stack)++;
    return h;
}

node *pop(node *head, int *size){
    node *remove_node = head->next;
    head->next = remove_node->next;
    free(remove_node);
    (*size)--;
    return head;
}