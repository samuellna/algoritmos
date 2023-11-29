#include <stdio.h>
#include <stdlib.h>

typedef struct n {
    int Union_height;
    int parent;
} Union;

Union *initialize(int num_elements);
Union *make_set(int n_elements);
int find(Union n[], int index_parent);
void union_(Union u[], int index_u1, int index_u2);

int main(void){
    Union *u;
    int num_elements;
    int indexes[2];

    printf("Number of elements: ");
    scanf("%d", &num_elements);

    u = make_set(num_elements);

    for(int i = 0; i < 5; i++){
        printf("Union (a, b): ");
        scanf("%d %d", &indexes[0], &indexes[1]);
        union_(u, indexes[0], indexes[1]);
    }

    for(int i = 0; i < num_elements; i++){
        printf("Elemento %d:\n\tRepresentante: %d\n\tAltura:%d\n", i, u[i].parent, u[i].Union_height);
    }

    free(u);
    return 0;
}

Union *initialize(int num_elements){
    Union *u = (Union *) malloc(num_elements * sizeof(Union));
    if(!u){
        printf("There was an error at union's creating.\n");
        return NULL;
    }
    return u;
}

Union *make_set(int n_elements){ // Setting the equivalency class.
    Union *n = initialize(n_elements);
    for(int i = 0; i < n_elements; i++){
        n[i].Union_height = 1;
        n[i].parent = i;
    }
    return n;
}

int find(Union n[], int index_parent){
    if(n[index_parent].parent != index_parent) n[index_parent].parent = find(n, n[index_parent].parent);
    return n[index_parent].parent;
}

void union_(Union u[], int index_u1, int index_u2){
    int root_a = find(u, index_u1);
    int root_b = find(u, index_u2);

    if(u[root_a].Union_height >= u[root_b].Union_height){ // root_a is th
        u[root_b].parent = root_a;
        if(u[root_a].Union_height == u[root_b].Union_height) u[root_a].Union_height++;
        // return u[root_a];
    }
    else{
        u[root_a].parent = root_b;
        // return u[root_b];
    }   
}