#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STR_SIZE 20

typedef struct{
    int **matrix_adj;
    int edges_amount;
    int vertices_amount;
} Graph;

void destroy_graph(Graph *g); // Function to destroy completely a graph.
Graph *create_graph(int num_vertices);  // Function to create a graph.
void add_edge(Graph *g, int from, int to); // Function to add an edge between two vertices.
int edge_exists(Graph *g, int index1, int index2); // This function returns if an edge exists in a vertex V.
void amount_edges_vertex(Graph *g, int vertex, int *amount);  // This function returns the number of edges who are in a vertex.
int *adjacent_edges(Graph *g, int vertex); // This function returns all adjacent edges of a vertex V
void print_graph(Graph *g); // Function to print graph.

int from_to(char command[], int *to);
int walls_into_edges(int *walls, int number_walls, Graph *g);

int main(void){
    Graph *graph;
    int indexes[2]; // Vertex or Edge indexes.
    int amount_of_vertices, removed_walls, number_cases;
    int i = 0;
    int *walls;
    char pair_cells[STR_SIZE];

    printf("Number of cases: ");
    scanf("%d", &number_cases);
    
    while(i < number_cases){
        printf("Number of vertices: ");
        scanf("%d", &amount_of_vertices);

        graph = create_graph(amount_of_vertices);
        
        printf("Number of removed walls: ");
        scanf("%d", &removed_walls);

        walls = (int *) malloc(removed_walls * sizeof(walls));
        if(!walls){
            printf("There was an error at memory allocating.\n");
            exit(1);
        }

        for(int j = 0; j < removed_walls; j++){ // Receiving the walls to remove.
            printf("Wall %d: ", j);
            scanf("%d", &walls[j]);
        }
        
        do{
            printf("Cells pair: ");
            scanf(" %[^\n]", pair_cells);
            indexes[0] = from_to(pair_cells, &indexes[1]);
            // DFS...

        } while(strcmp(pair_cells, "\n"));

        free(walls);
        destroy_graph(graph);
        i++;
    }
    return 0;
}

void destroy_graph(Graph *g){
    if(g->matrix_adj == NULL) return; // Verifying if the graph really exists.
    for(int i = 0; i < g->vertices_amount; i++){
        if(g->matrix_adj[i]) free(g->matrix_adj[i]); // Releasing memory.
    }
    g->vertices_amount = 0;
    g->edges_amount = 0;
    free(g->matrix_adj);
}

Graph *create_graph(int num_vertices){
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    if(!graph){
        printf("There was an error at graph's creating.\n");
        free(graph);
        exit(1);
    }

    graph->matrix_adj = (int **) calloc(sizeof(int *), num_vertices);
    for(int i = 0; i < num_vertices; i++){
        graph->matrix_adj[i] = (int *) calloc(sizeof(int), num_vertices);
        if(!graph->matrix_adj[i]){
            printf("There was an error at matrix's creating.\n");
            destroy_graph(graph);
            return NULL;
        }
    }
    graph->vertices_amount = num_vertices;

    return graph;
}

void add_edge(Graph *g, int from, int to){
    if((from < g->vertices_amount && to < g->vertices_amount) && (from >= 0 && to >= 0)){ // Checking if the index is greater than 0 and less than vertices amount.
        if(g->matrix_adj){
            if(g->matrix_adj[from][to] == 0 && g->matrix_adj[to][from] == 0){
                g->matrix_adj[from][to] = 1;
                g->matrix_adj[to][from] = 1;
                g->edges_amount++;
            }
            else printf("There's already an edge betwen %d and %d.\n", from, to);
        }
        else printf("There isn't any vertex in the graph.\n");
    }
    else printf("The vertex indexes are out of matrix's limit.\n");
}

int edge_exists(Graph *g, int index1, int index2){ // This function returns if an edge exists in a vertex V.
    if((index1 < g->vertices_amount && index2 < g->vertices_amount) && (index1 >= 0 && index2 >= 0)){
        return (g->matrix_adj[index1][index2] || g->matrix_adj[index2][index1]) ? 1: 0;
    }
    else return 0;
}

void amount_edges_vertex(Graph *g, int vertex, int *amount){ // This function returns the number of edges who are in a vertex.
    if(vertex < g->vertices_amount && vertex >= 0){
        for(int i = 0; i < g->vertices_amount; i++){
            if(g->matrix_adj[vertex][i]) (*amount)++;
        }
    }
    else printf("Vertex's index has surpassed matrix's limit size.\n");
}

int *adjacent_edges(Graph *g, int vertex){ // This function returns all adjacent edges of a vertex V
    if(vertex < g->vertices_amount){
        int *edges = NULL, edges_pointer = 0;
        for(int i = 0; i < g->vertices_amount; i++){
            int a = edge_exists(g, vertex, i);
            if(a){
                edges = (int *) realloc(edges, sizeof(int)); // Memory alocating in the edge's pointer.
                if(!edges){
                    printf("There was an error on memory allocate to edges.\n");
                    exit(1);
                }
                edges[edges_pointer] = i; // Edge's pointer receives the vertex's index where the edge is.
                edges_pointer++;
                // edges[edges_pointer] = NULL; // Next position's edge will be NULL.
            }
        }
        return edges;
    }
    else printf("Vertex's index has surpassed matrix's limit size.\n");
    return NULL;
}

void print_graph(Graph *g){ // Function to print graph.
    if(g->matrix_adj){
        for(int i = 0; i < g->vertices_amount; i++){
            if(i == 0) printf("   %d", i); // Printing the column's index.
            else printf("  %d", i);
        }
        printf("\n");
        for(int i = 0; i < g->vertices_amount; i++){
            printf("%d: ", i); // Printing row's index.
            for(int j = 0; j < g->vertices_amount; j++){
                printf("%d", g->matrix_adj[i][j]); // Printing matrix's value.
                if(j < g->vertices_amount - 1) printf(", ");
            }
            printf("\n");
        }
    }
    else printf("Empty graph\n");
}

int from_to(char command[], int *to){
    int i = 0, j = 0;
    bool spacebar_found = false;
    char from[STR_SIZE], to_[STR_SIZE];
    while(i < strlen(command)){
        if(command[i] == ' '){
            spacebar_found = true; 
            from[i] = '\0';
            i++; // Ignoring the space.
        }
        if(!spacebar_found) from[i] = command[i];
        else{
            to_[j] = command[i];
            j++;
        }
        i++;
    }
    to_[j] = '\0';
    (*to) = atoi(to_);
    return atoi(from);
}
    
int line_matrix(int num_vertices, int wall, Graph *g){ // This function returns the lessest and greatest values of a matrix's line.
    int *vert, *horiz;
    vert = (int *) malloc(num_vertices * sizeof(int));
    horiz = (int *) malloc(num_vertices * sizeof(int));

    vert[0] = 0; //  First vertex at line 0.
    horiz[0] = 2 * num_vertices - 2; // Last vertex at line 0.

    if(wall <= horiz[0] && wall >= vert[0]) return 0;
    else{
        for(int i = 1; i < num_vertices; i++){
            vert[i] = horiz[i - 1] + 1;
            if(i == num_vertices - 1) horiz[i] = vert[i] + num_vertices - 2;
            else horiz[i] = vert[i] + 2 * num_vertices - 2;
            if(wall <= horiz[i] && wall >= vert[i]) return i;
        }
    }
}


int walls_into_edges(int *walls, int number_walls, Graph *g){
    bool edges_setted = false;
    int counter = 0;
    for(int i = 0; i < g->vertices_amount && !edges_setted; i++){
        if(counter == number_walls) edges_setted = true;
    }
}