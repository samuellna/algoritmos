#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int **matrix_adj;
    int edges_amount;
    int vertices_amount;
} Graph;

Graph graph;

void menu();
void destroy_graph(); // Function to destroy completely a graph.
void create_graph(int num_vertices);  // Function to create a graph.
void add_edge(int from, int to); // Function to add an edge between two vertices.
void remove_edge(int from, int to); // Function to remove an edge between two vertices.
void print_graph(); // Function to print graph.

int main(void){
    int indexes[2]; // Vertex or Edge indexes.
    int amount_of_vertices;
    int command;
    do{
        menu();
        scanf("%d", &command);

        switch(command){
            case 1:
                printf("Vertex amount: ");
                scanf("%d", &amount_of_vertices);
                create_graph(amount_of_vertices);
                printf("\n");
            break;
            
            case 2:
                printf("From: ");
                scanf("%d", &indexes[0]);
                printf("To: ");
                scanf("%d", &indexes[1]);
                add_edge(indexes[0], indexes[1]);
                printf("\n");
            break;
            
            case 3:
                printf("Remove from (i j): ");
                scanf("%d %d", &indexes[0], &indexes[1]);
                remove_edge(indexes[0], indexes[1]);
                printf("\n");
            break;

            case 4:
                print_graph(graph);
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
    }while(command != 0);

    destroy_graph(graph);

    return 0;
}

void menu(){
    printf("\t..Graph's Menu..\n1... Create graph\n2... Add an edge\n3... Remove an edge\n4... Print graph\n5... Clean screen\n0... Quit\nType one of these options: ");
}

void destroy_graph(){
    if(graph.matrix_adj == NULL) return; // Verifying if the graph really exists.
    for(int i = 0; i < graph.vertices_amount; i++){
        if(graph.matrix_adj[i]) free(graph.matrix_adj[i]); // Releasing memory.
    }
    graph.vertices_amount = 0;
    graph.edges_amount = 0;
    free(graph.matrix_adj);
}

void create_graph(int num_vertices){
    graph.matrix_adj = (int **) calloc(sizeof(int *), num_vertices);
    for(int i = 0; i < num_vertices; i++){
        graph.matrix_adj[i] = (int *) calloc(sizeof(int), num_vertices);
        if(!graph.matrix_adj[i]){
            printf("There was an error at matrix's creating.\n");
            destroy_graph(graph);
            return ;
        }
    }
    graph.vertices_amount = num_vertices;
}

void add_edge(int from, int to){
    if((from < graph.vertices_amount && to < graph.vertices_amount) && (from >= 0 && to >= 0)){ // Checking if the index is greater than 0 and less than vertices amount.
        if(graph.matrix_adj){
            if(graph.matrix_adj[from][to] == 0 && graph.matrix_adj[to][from] == 0){
                graph.matrix_adj[from][to] = 1;
                graph.edges_amount++;
            }
            else printf("There's already an edge betwen %d and %d.\n", from, to);
        }
        else printf("There isn't any vertex in the graph.\n");
    }
    else printf("The vertex indexes are out of matrix's limit.\n");
}

void remove_edge(int from, int to){
    if((from >= 0 && to >= 0) && (from < graph.vertices_amount && to < graph.vertices_amount)){
        if(graph.matrix_adj[from][to] == 1){
            graph.matrix_adj[from][to] = 0;
            graph.edges_amount--;
        }
        else if(graph.matrix_adj[to][from] == 1){
            graph.matrix_adj[to][from] = 0;
            graph.edges_amount--;
        }
        else printf("There isn't edge betwen %d and %d.\n", from, to);
    }
    else printf("The edge indexes are out of matrix's limit.\n");
}

void print_graph(){ // Function to print graph.
    if(graph.matrix_adj){
        for(int i = 0; i < graph.vertices_amount; i++){
            if(i == 0) printf("   %d", i); // Printing the column's index.
            else printf("  %d", i);
        }
        printf("\n");
        for(int i = 0; i < graph.vertices_amount; i++){
            printf("%d: ", i); // Printing row's index.
            for(int j = 0; j < graph.vertices_amount; j++){
                printf("%d", graph.matrix_adj[i][j]); // Printing matrix's value.
                if(j < graph.vertices_amount - 1) printf(", ");
            }
            printf("\n");
        }
    }
    else printf("Empty graph\n");
}