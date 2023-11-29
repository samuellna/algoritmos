#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int **matrix_adj;
    int edges_amount;
    int vertices_amount;
} Graph;

Graph *graph;
int **distance;
int **parent;

void destroy_graph(); // Function to destroy completely a graph.
Graph *create_graph(int num_vertices);  // Function to create a graph.
void add_edge(int from, int to, int d); // Function to add an edge between two vertices.
void initialize_dis_par(int **d0); // Function to initialize distance and parent arrays.
void copy(int **d0); // Copies the distance.
void print_floyd(); // Print the distance and parent's array after algorithm warshall-floyd.
void floyd_warshall(); // Floyd-warshall's algorithm.
void print_graph(); // Function to print graph.

int main(void){
    int indexes[2]; // Vertex or Edge indexes.
    int amount_of_vertices;
    int command;
    int distance;

    do{
        printf("\t..Graph's Menu..\n1... Create graph\n2... Add an edge\n3... Floyd-Warshall Algorithm\n4... Print graph\n5... Clean screen\n0... Quit\nType one of these options: ");
        scanf("%d", &command);

        switch(command){
            case 1:
                printf("Vertex amount: ");
                scanf("%d", &amount_of_vertices);
                graph = create_graph(amount_of_vertices);
                printf("\n");
            break;
            
            case 2:
                printf("From: ");
                scanf("%d", &indexes[0]);
                printf("To: ");
                scanf("%d", &indexes[1]);
                printf("Distance between %d and %d: ", indexes[0], indexes[1]);
                scanf("%d", &distance);
                add_edge(indexes[0], indexes[1], distance);
                printf("\n");
            break;

            case 3:
                floyd_warshall();
            break;
            
            case 4:
                print_graph();
                printf("\n");
            break;

            case 5:
                system("cls");
            break;
            default:
                if(command != 0) printf("Invalid option.\n");
            break;
        }
        // Reseting indexes to avoid some errors.
        indexes[0] = -1;
        indexes[1] = -1;
    }while(command != 0);

    destroy_graph();

    return 0;
}

void destroy_graph(){
    if(graph->matrix_adj == NULL) return; // Verifying if the graph really exists.
    for(int i = 0; i < graph->vertices_amount; i++){
        if(graph->matrix_adj[i]) free(graph->matrix_adj[i]); // Releasing memory.
        if(distance[i]) free(distance[i]);
        if(parent[i]) free(parent[i]);
    }
    graph->vertices_amount = 0;
    graph->edges_amount = 0;
    free(graph->matrix_adj);
    free(distance);
    free(parent);
}

Graph *create_graph(int num_vertices){
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    if(!graph){
        printf("There was an error at graph's creating.\n");
        free(graph);
        exit(1);
    }

    graph->matrix_adj = (int **) malloc(sizeof(int *) * num_vertices);
    for(int i = 0; i < num_vertices; i++){
        graph->matrix_adj[i] = (int *) malloc(sizeof(int) * num_vertices);
        if(!graph->matrix_adj[i]){
            printf("There was an error at matrix's creating.\n");
            destroy_graph(graph);
            return NULL;
        }
        for(int j = 0; j < num_vertices; j++){
            graph->matrix_adj[i][j] = -1;
        }
    }
    graph->vertices_amount = num_vertices;

    return graph;
}

void add_edge(int from, int to, int d){
    if((from < graph->vertices_amount && to < graph->vertices_amount) && (from >= 0 && to >= 0)){ // Checking if the index is greater than 0 and less than vertices amount.
        if(graph->matrix_adj){
            graph->matrix_adj[from][to] = d;
            graph->edges_amount++;
        }
        else printf("There isn't any vertex in the graph.\n");
    }
    else printf("The vertex indexes are out of matrix's limit.\n");
}

void initialize_dis_par(int **d0){
    distance = (int **) malloc(graph->vertices_amount * sizeof(int *));    
    parent = (int **) malloc(graph->vertices_amount * sizeof(int *));

    for(int i = 0; i < graph->vertices_amount; i++){
        distance[i] = (int *) malloc(graph->vertices_amount * sizeof(int));
        parent[i] = (int *) malloc(graph->vertices_amount * sizeof(int));
        for(int j = 0; j < graph->vertices_amount; j++){ // Setting distance and parent arrays.
            if(i != j){
                if(graph->matrix_adj[i][j] != -1) d0[i][j] = graph->matrix_adj[i][j]; // If there's an edge between i and j, then distance is the edge's weight.
                else d0[i][j] = 214748364; // Else, infinity. 
            }
            else{
                d0[i][j] = 0; // Distance between i and i is 0;
                distance[i][j] = 0;
            }
            parent[i][j] = i; // J's parent is i.
        }
    }
}

void copy(int **d0){
    for(int i = 0; i < graph->vertices_amount; i++){
        for(int j = 0; j < graph->vertices_amount; j++){
            distance[i][j] = d0[i][j];
        }
    }
}

void print_floyd(){
    for(int i = 0; i < graph->vertices_amount; i++){
        printf("Distance between %d and:\n", i);
        for(int j = 0; j < graph->vertices_amount; j++){
            printf("\t%d: %d\n", j, distance[i][j]);
        }
        printf("/---------------------------/\n");
    }
}

void floyd_warshall(){
    int **d0 = (int **) malloc(graph->vertices_amount * sizeof(int *));
    for(int i = 0; i < graph->vertices_amount; i++){
        d0[i] = (int *) malloc(graph->vertices_amount * sizeof(int));
    }

    initialize_dis_par(d0);
    for(int k = 1; k <= graph->vertices_amount; k++){
        copy(d0);
        for(int s = 0; s < graph->vertices_amount; s++){
            for(int t = 0; t < graph->vertices_amount; t++){
                if(d0[s][k - 1] + d0[k - 1][t] < distance[s][t]){
                    distance[s][t] = d0[s][k - 1] + d0[k - 1][t];
                    parent[s][t] = parent[k - 1][t];
                }
            }
            if(distance[s][s] < 0) printf("Negative cycle!!!!!!\n");
        }
    }
    print_floyd();
}

void print_graph(){ // Function to print graph.
    if(graph->matrix_adj){
        for(int i = 0; i < graph->vertices_amount; i++){
            if(i == 0) printf("    %d", i); // Printing the column's index.
            else printf("   %d", i);
        }
        printf("\n");
        for(int i = 0; i < graph->vertices_amount; i++){
            printf("%d: ", i); // Printing row's index.
            for(int j = 0; j < graph->vertices_amount; j++){
                printf("%d", graph->matrix_adj[i][j]); // Printing matrix's value.
                if(j < graph->vertices_amount - 1) printf(", ");
            }
            printf("\n");
        }
    }
    else printf("Empty graph\n");
}