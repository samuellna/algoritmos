#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int Union_height;
    int parent;
} Union;

Union *u; // Global variable.
int num_cells;

Union *initialize(int num_elements);
Union *make_set(int n_elements);
int find(int index_parent);
void union_(int index_u1, int index_u2);
void calculate_wall(int wall[], int num_r_w);
void arvore();
int binary_search(int vetor[], int tam_vet, int valor);

int main(void){
    int num_cases, num_removed_walls, num_query;
    int i = 0;

    scanf("%d", &num_cases);

    do{
        scanf("%d %d %d", &num_cells, &num_removed_walls, &num_query);

        u = make_set(pow(num_cells, 2));
        int *r_walls = (int *) malloc(num_removed_walls * sizeof(int));

        for(int i = 0; i < num_removed_walls; i++){
            scanf("%d", &r_walls[i]);
        }

        calculate_wall(r_walls, num_removed_walls);
        // int cells_pair[2];

        // for(int j = 0; j < num_query; j++){
        //     scanf("%d %d", &cells_pair[0], &cells_pair[1]);
            
        //     printf("%d.%d ", i, j);
        //     if(find(cells_pair[0]) == find(cells_pair[1])) printf("1\n");
        //     else printf("0\n");
        // }
        printf("\n");
        arvore();
        free(u);
        free(r_walls);
        i++;
    }while(i < num_cases);

    return 0;
}

Union *initialize(int num_elements){
    Union *un = (Union *) malloc(num_elements * sizeof(Union));
    if(!un){
        printf("There was an error at union's creating.\n");
        return NULL;
    }
    return un;
}

Union *make_set(int n_elements){ 
    Union *n = initialize(n_elements);
    for(int i = 0; i < n_elements; i++){
        n[i].Union_height = 1;
        n[i].parent = i;
    }
    return n;
}

int find(int index_parent){
    if(u[index_parent].parent != index_parent) u[index_parent].parent = find(u[index_parent].parent);
    return u[index_parent].parent;
}

void union_(int index_u1, int index_u2){
    int root_a = find(index_u1); // Representant of cell A.
    int root_b = find(index_u2); // Representant of cell B.

    if(u[root_a].Union_height >= u[root_b].Union_height){
        u[root_b].parent = root_a; // B receives the A tree.
        if(u[root_a].Union_height == u[root_b].Union_height) u[root_a].Union_height++; // Increasing B tree if A and B have the same height.
    }
    else u[root_a].parent = root_b; // A receives the B tree.
}

int binary_search(int vetor[], int tam_vet, int valor){
    int l = 0, r = tam_vet - 1;
    while(l <= r){
        int m = (r + l) / 2;
        if(vetor[m] == valor) {printf("%d esta entre as paredes procuradas.\n", valor);return m; }
        else{
            if(valor < vetor[m]) r = m - 1;
            else l = m + 1;
        }
    }
    printf("%d nao esta entre as paredes procuradas.\n", valor);
    return -1;
}

void calculate_wall(int wall[], int num_r_w){
    int index_wall = 0;
    short int edges_setted = 0;

    for(int i = 0; i < pow(num_cells, 2) && !edges_setted; i++){
        int row = i / num_cells; // The row of the cell [i]
        int col = i % num_cells; // The column of the cell [i]

        int r_w, b_w; // Right wall and bottom wall.
        
        if((i + 1) % num_cells != 0) r_w = row * (num_cells - 1) + row * num_cells + (col % num_cells); // Verifying if the cell [i] is the last one in the row.  
        else r_w = -1; // The last cell in the row i doesnt have a right wall.
        
        if(i < num_cells * num_cells - num_cells) b_w = row * (num_cells - 1) + row * num_cells + (col % num_cells) + num_cells - 1; // The last cell in the column doesnt have a bottom wall.
        else b_w = -1;
        
        // printf("Celula %d: r_w = %d, b_w = %d\n", i, r_w, b_w);
        if(binary_search(wall, num_r_w, r_w) != -1){
            union_(i, i + 1); // Removing a vertical wall between cell i and cell i + 1.
            index_wall++;
        }
        if(binary_search(wall, num_r_w, b_w) != -1){
            union_(i, i + num_cells); // Removing an horizontal wall between the cell (i) and cell (i + num_cells). 
            index_wall++;
        }
        if(index_wall == num_r_w) edges_setted = 1; // Stop after remove all edges.
    }
}

void arvore(){
    int n = num_cells;
    int j, l, c, ll; j = 0; ll = 0;
    
    for (int i = 0; i < n * n; i++) {
        l = i / n;
        c = i % n;
	    printf("(%d, %d)", i, u[i].parent);
        if(c < (n - 1)){
            printf("|%d|", j);
            j++;
        }
        if(l > ll){
            for(int u = 0; u < n; u++){
                printf("-----%d-----", j);
                j++;
            }
            printf("\n");
	    }
	    ll = l;
    }
}