#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int **matrix_adj;
    int edges_amount;
    int vertices_amount;
} Graph;

void destroy_graph(Graph *g); // Function to destroy completely a graph.
Graph *create_graph(int num_vertices);  // Function to create a graph.
void add_edge(Graph *g, int from, int to); // Function to add an edge between two vertices.
void remove_edge(Graph *graph, int from, int to); // Function to remove an edge between two vertices.
int edge_exists(Graph *g, int index1, int index2); // This function returns if an edge exists in a vertex V.
void amount_edges_vertex(Graph *g, int vertex, int *amount);  // This function returns the number of edges who are in a vertex.
int *adjacent_edges(Graph *g, int vertex); // This function returns all adjacent edges of a vertex V
int amount_edges(Graph *gr, int amount); // This function returns all edges in the graph.
void print_graph(Graph *g); // Function to print graph.

int main(void){
    Graph *graph;
    int indexes[2]; // Vertex or Edge indexes.
    int amount_of_vertices;
    int command;
    int *edges;
    do{
        printf("\t..Graph's Menu..\n1... Create graph\n2... Add an edge\n3... Remove an edge\n4... Verify if an edge belongs to a graph\n5... Get all adjacents vertices from a vertex\n6... Number of vertices and edges in all graph\n7... Print edge\n8... Clean screen\n0... Quit\nType one of these options: ");
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
                add_edge(graph, indexes[0], indexes[1]);
                printf("\n");
            break;
            
            case 3:
                printf("Remove from (i j): ");
                scanf("%d %d", &indexes[0], &indexes[1]);
                remove_edge(graph, indexes[0], indexes[1]);
                printf("\n");
            break;

            case 4:
                printf("Edge's index (i j): ");
                scanf("%d %d", &indexes[0], &indexes[1]);
                (edge_exists(graph, indexes[0], indexes[1])) != 0 ? printf("Edge exists.\n"): printf("Edge doesn't exists.\n");
                printf("\n");
            break;

            case 5:
                printf("Vertex's index: ");
                scanf("%d", &indexes[0]);
                int aux = 0; // Amount of edges in a vertex v.
                amount_edges_vertex(graph, indexes[0], &aux); // "aux" receives the amount of vertices.
                edges = adjacent_edges(graph, indexes[0]); // Edges receives a list with all adjacent edges in a vertex v.
                if(edges){
                    int i = 0;
                    printf("List of adjacent vertices: ");
                    while(i < aux){ 
                        printf("%d", edges[i]);
                        i++;
                        if(i < aux) printf(", ");
                    }
                }
                else printf("There isn't any edge on this vertex.\n");
                printf("\n");
            break;

            case 6:
                if(graph->vertices_amount > 0) printf("Number of vertices: %d - Number of edges: %d\n\n", graph->vertices_amount, amount_edges(graph, graph->vertices_amount));
                else printf("There isn't any vertex in the graph\n\n");
            break;

            case 7:
                print_graph(graph);
                printf("\n");
            break;

            case 8:
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

    free(edges);
    destroy_graph(graph);

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
                g->edges_amount++;
            }
            else printf("There's already an edge betwen %d and %d.\n", from, to);
        }
        else printf("There isn't any vertex in the graph.\n");
    }
    else printf("The vertex indexes are out of matrix's limit.\n");
}

void remove_edge(Graph *graph, int from, int to){
    if((from >= 0 && to >= 0) && (from < graph->vertices_amount && to < graph->vertices_amount)){
        if(graph->matrix_adj[from][to] == 1){
            graph->matrix_adj[from][to] = 0;
            graph->edges_amount--;
        }
        else if(graph->matrix_adj[to][from] == 1){
            graph->matrix_adj[to][from] = 0;
            graph->edges_amount--;
        }
        else printf("There isn't edge betwen %d and %d.\n", from, to);
    }
    else printf("The edge indexes are out of matrix's limit.\n");
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

int amount_edges(Graph *gr, int amount){ // This function returns all edges in the graph.
    int amount_e = 0;
    if(amount > 0){
        for(int i = 0; i < amount; i++){
            for(int j = 0; j < amount; j++){
                if(gr->matrix_adj[i][j]) amount_e++;
            }
        }
    }
    return amount_e;
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