#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE 100
#define SUBSTRING_SIZE 20

typedef struct no{
    int key;
    struct no *next;
} node;

typedef struct{
    node *head;
    int size;
} stacks;

void initialize_stack(stacks **head, int *amount_stacks);
void shift_right_stack(stacks **stack, int number_of_stacks);
void shift_left_stack(stacks **stack, int *number_of_stacks, int index_remove);
node *push(node *h, int key_insert, int *size_stack);
node *pop(node *head, int *size);
int column(char string[], size_t *index); 
int key_value(char string[], size_t *index);
bool verify_insertion(node *head, int key);
void print_list(stacks *stack, int number_stacks);
void print_case(stacks *stack, int num_cases, int num_stacks);
void destroy_stacks(stacks **stack, int *num_stacks);

int main(void){
    stacks *stack = NULL;
    char command[STRING_SIZE];
    int amount_stacks = 0, number_cases;
    int i = 0;
    int key, index_column;
    
    printf("Number of cases: ");
    scanf("%d", &number_cases);

    while(i < number_cases){
        
        // index_column = 0, key = 0;
        do{
            printf("Command: ");
            scanf(" %[^\n]", command);
            if(strcmp(command, "END") != 0){ // If command isn't "END".
                bool insert_right = false;
                size_t index = 0;
                index_column = column(command, &index); 
                key = key_value(command, &index);

                if(index_column > amount_stacks || index_column == 0){ // -1 because is the stack's index. 
                    initialize_stack(&stack, &amount_stacks); // Creating another stack column.
                    if(index_column == 0){// If index_column == 0, then we'll add the column on the left.
                        shift_right_stack(&stack, amount_stacks);
                    }
                    else{ // Else we'll set index_column as amount_stacks - 1 (because is the last index in the vector) and set flag as true.
                        index_column = amount_stacks - 1;
                        insert_right = true;
                    }
                }
                if(!insert_right && index_column > 0) index_column--; // Verifying if we just need to insert whithout another operation.
                
                if(verify_insertion(stack[index_column].head, key)){  // Verifying if the stack's top is equal to the number we'll insert.
                    stack[index_column].head = pop(stack[index_column].head, &stack[index_column].size); // Removing the head.
                    if(!stack[index_column].head->next) shift_left_stack(&stack, &amount_stacks, index_column); // Deleting column if there's nothing inside it.
                }
                else stack[index_column].head = push(stack[index_column].head, key, &stack[index_column].size); // Inserting.
            }
            else{
                amount_stacks > 0 ? print_case(stack, i, amount_stacks): printf("caso %d:\n", i);
                destroy_stacks(&stack, &amount_stacks);                
            }
            
        } while(strcmp(command, "END" ) != 0); 
        i++;
    }
    return 0;
}

void initialize_stack(stacks **head, int *amount_stacks){
    (*head) = (stacks *) realloc((*head), ((*amount_stacks) + 1) * sizeof(stacks)); // Allocating memory in the new column stack.
    if(!(*head)){
        printf("There was an error in memory allocating to initialize the stack.\n");
        exit(1);
    }

    (*head)->size = 0; // It's 0 because there's nothing in the stack.
    (*head)[(*amount_stacks)].head = (node *) malloc(sizeof(node)); // Allocating memory to stack's head.

    if(!(*head)[(*amount_stacks)].head){ // Verifying if that's null.
        printf("Error to add a column.\n");
        exit(1);
    }

    (*head)[(*amount_stacks)].head->next = NULL;
    (*head)[(*amount_stacks)].head->key = -1;

    (*amount_stacks)++; // Updating the number of columns.
}

void shift_right_stack(stacks **stack, int number_of_stacks){
    int i = 0, last_index = number_of_stacks - 1, cur = last_index - 1;
    stacks aux = (*stack)[last_index];
    while(i < number_of_stacks){
        (*stack)[last_index] = (*stack)[cur];
        last_index--;
        cur--;
        i++;
    }
    (*stack)[0] = aux;
}

void shift_left_stack(stacks **stack, int *number_of_stacks, int index_remove){
    int next_index = index_remove + 1, aux = index_remove;
    while(next_index < (*number_of_stacks)){
        (*stack)[aux] = (*stack)[next_index];
        next_index++;
        aux++;
    }
    (*number_of_stacks)--;
    (*stack) = (stacks *) realloc((*stack), (*number_of_stacks) * sizeof(stacks));
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

int column(char string[], size_t *index){
    char aux_string[SUBSTRING_SIZE];
    while(string[(*index)] != ' '){
        aux_string[(*index)] = string[(*index)];
        (*index)++;
    }
    aux_string[(*index)] = '\0';
    (*index)++;
    return atoi(aux_string);
}

int key_value(char string[], size_t *index){
    char aux_string[SUBSTRING_SIZE];
    int i = 0;
    while((*index) < strlen(string)){ 
        aux_string[i] = string[(*index)];
        (*index)++;
        i++;
    }
    aux_string[i] = '\0';
    return atoi(aux_string);
}

void destroy_stacks(stacks **stack, int *num_stacks){
    for(int i = 0; i < (*num_stacks); i++){
        free((*stack)[i].head);
    }
    // free(stack);
    (*num_stacks) = 0;
}

bool verify_insertion(node *head, int key){
    if(head->next){
        if(head->next->key == key) return true;
    }
    return false;
}

void print_case(stacks *stack, int current_case, int num_stacks){
    printf("caso %d:", current_case);
    int i = 0;
    while(i < num_stacks){
        printf(" %d", stack[i].head->next->key);
        i++;
    }
    printf("\n");
}