#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int value;
    int price;
} Item;

Item *item;
int items_amount;

Item *initialize_item();
int max_item(int item1, int item2);
int knapsack(int capacity);
int unbounded_knapsack(int capacity);

int main(void){
    int max_capacity; 

    printf("Items amount: ");
    scanf("%d", &items_amount);

    item = initialize_item();

    for(int i = 0; i < items_amount; i++) {
        printf("Value of item %d: ", i);
        scanf("%d", &item[i].value);
    }

    for(int i = 0; i < items_amount; i++) {
        printf("Price of item %d: ", i);
        scanf("%d", &item[i].price);
    }

    printf("Bag capacity: ");
    scanf("%d", &max_capacity);

    printf("The best sollution is %d.\n", unbounded_knapsack(max_capacity));
    return 0;
}

Item *initialize_item(){
    Item *i = (Item *) malloc(items_amount * sizeof(Item));
    return i;
}

int max_item(int item1, int item2){
    return item1 >= item2 ? item1 : item2;
}

int knapsack(int capacity){
    int **s = (int **) malloc((items_amount + 1) * sizeof(int *));
    for(int i = 0; i < capacity; i++){
        s[i] = (int *) calloc(capacity + 1, sizeof(int));
    }

    int m = 1, k = 1;
    for(m = 1; m <= items_amount; m++){
        for(k = 1; k <= capacity; k++){
            if(k < item[m - 1].price) s[m][k] = s[m - 1][k];
            else s[m][k] = max_item(s[m - 1][k], s[m - 1][k - item[m - 1].price] + item[m - 1].value);
        }
    }
    return s[items_amount][capacity];
}

int unbounded_knapsack(int capacity){
    int *s = (int *) calloc((items_amount + 1), sizeof(int));
    for(int i = 1; i <= capacity; i++){
        for(int j = 0; j < items_amount; j++){
            if(item[j].price <= i) s[i] = max_item(s[i], s[i - item[j].price] + item[j].value); 
            printf("Current S: %d\n", s[i]);
        }
    }
    return s[capacity];
}