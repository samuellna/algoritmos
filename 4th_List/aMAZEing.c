#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int Union_height;
    int parent;
} Union;

Union *initialize(int num_elements);
Union *make_set(int n_elements);
int find(Union n[], int index_parent);
void union_(int index_u1, int index_u2);
void calculate_wall(int num_cells, int wall[], int num_r_w);
void print(int size_union);

Union *u; // Global variable.

int main(void){
    int num_cases, num_cells, num_removed_walls, num_query;
    int i = 0;

    printf("Number of cases: ");
    scanf("%d", &num_cases);

    do{
        printf("Number of cells: ");
        scanf("%d", &num_cells);

        u = make_set(pow(num_cells, 2));

        printf("Number of removed walls: ");
        scanf("%d", &num_removed_walls);

        printf("Query number: ");
        scanf("%d", &num_query);

        int *r_walls = (int *) malloc(num_removed_walls * sizeof(int));

        for(int i = 0; i < num_removed_walls; i++){
            printf("Wall %d: ", i);
            scanf("%d", &r_walls[i]);
        }

        calculate_wall(num_cells, r_walls, num_removed_walls);
        int cells_pair[2];

        for(int j = 0; j < num_query; j++){
            printf("Cells pair: ");
            scanf("%d %d", &cells_pair[0], &cells_pair[1]);
            
            printf("%d.%d ", i, j);
            if(find(u, cells_pair[0]) == find(u, cells_pair[1])) printf("1\n");
            else printf("0\n");
        }
        printf("\n");
        free(u);
        free(r_walls);
        i++;
    }while(i < num_cases);

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

void union_(int index_u1, int index_u2){
    int root_a = find(u, index_u1);
    int root_b = find(u, index_u2);

    if(u[root_a].Union_height >= u[root_b].Union_height){ // root_a is th
        u[root_b].parent = root_a;
        if(u[root_a].Union_height == u[root_b].Union_height) u[root_a].Union_height++;
    }
    else u[root_a].parent = root_b;
}

void calculate_wall(int num_cells, int wall[], int num_r_w){
    int index_wall = 0;
    short int edges_setted = 0;

    for(int i = 0; i < pow(num_cells, 2) && !edges_setted; i++){
        int row = i / num_cells; // The row of the cell [i]
        int col = i % num_cells; // The column of the cell [i]

        int r_w, d_w; // Right wall and Down wall.
        
        if((i + 1) % num_cells != 0){  
            r_w = row * (num_cells - 1) + row * num_cells + (col % num_cells); // The last cell in the row i doesnt have a right wall.
            if(i < num_cells * num_cells - num_cells) d_w = r_w + num_cells - 1; // The last cell in the column doesnt have a down wall.
            else d_w = -1;
        }
        else r_w = -1;

        int index_aux = i > num_cells - 1 ? sqrt(i) : i;

        if(r_w == wall[index_wall]){
            union_(index_aux, index_aux + 1);
            index_wall++;
        }
        else if(d_w == wall[index_wall]){
            union_(index_aux, index_aux + num_cells - 1);
            index_wall++;
        }
        if(index_wall == num_r_w) edges_setted = 1;
    }
}

void print(int size_union){
    printf("\n---------------\n");
    for(int i = 0; i < size_union; i++){
        printf("Element %d:\n\tParent: %d\n", i, u[i].parent);
    }
    printf("\n---------------\n");
}