#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX;

typedef struct{
    int **matrix_adj;
    int edges_amount;
    int vertices_amount;
} Graph;

typedef struct{
    int distance;
    int vertex;
} element;

typedef struct{
    element *arr;
    int num_elementos;
} Heap;

typedef struct{
    int *parent;
    int *distance;
} d_p;

d_p arr;
Heap Min_Heap;
Graph graph;
int qtd_elementos;

void menu();
void destroy_graph(); // Function to destroy completely a graph.
void create_graph(int num_vertices);  // Function to create a graph.
void add_edge(int from, int to, int w); // Function to add an edge between two vertices.
void remove_edge(int from, int to); // Function to remove an edge between two vertices.
int *adjacent_edges(int vertex, int *n_v);
int edge_exists(int index1, int index2);
void print_graph(); // Function to print graph.
void initialize_d_p();
void dijkstra(int source);

// Heap Functions
void initialize_heap(int qtd);
void swap(element *a, element *b);
void bubble_up(int index);
void heap_insert(int dist, int vertex);
element heap_extract();
void bubble_down(int index);

int main(void){
    int indexes[2]; // Vertex or Edge indexes.
    int amount_of_vertices;
    int command;
    int weight;

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
                printf("Weight: ");
                scanf("%d", &weight);
                add_edge(indexes[0], indexes[1], weight);
                printf("\n");
            break;
            
            case 3:
                printf("Remove from (i j): ");
                scanf("%d %d", &indexes[0], &indexes[1]);
                remove_edge(indexes[0], indexes[1]);
                printf("\n");
            break;

            case 4:
                printf("Source: ");
                scanf("%d", &indexes[0]);
                dijkstra(indexes[0]);
            break;

            case 5:
                print_graph(graph);
                printf("\n");
            break;

            case 6:
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

    destroy_graph(graph);

    return 0;
}

void menu(){
    printf("\t..Graph's Menu..\n1... Create graph\n2... Add an edge\n3... Remove an edge\n4... Dijkstra\n5... Print edge\n6... Clean screen\n0... Quit\nType one of these options: ");
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

void add_edge(int from, int to, int w){
    if((from < graph.vertices_amount && to < graph.vertices_amount) && (from >= 0 && to >= 0)){ // Checking if the index is greater than 0 and less than vertices amount.
        if(graph.matrix_adj){
            if(graph.matrix_adj[from][to] == 0){
                graph.matrix_adj[from][to] = w;
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

int edge_exists(int index1, int index2){ // This function returns if an edge exists in a vertex V.
    if((index1 < graph.vertices_amount && index2 < graph.vertices_amount) && (index1 >= 0 && index2 >= 0)){
        return (graph.matrix_adj[index1][index2]) ? 1: 0;
    }
    else return 0;
}

int *adjacent_edges(int vertex, int *n_v){ // This function returns all adjacent edges of a vertex V
    if(vertex < graph.vertices_amount){
        int *edges = NULL, edges_pointer = 0;
        for(int i = 0; i < graph.vertices_amount; i++){
            int a = edge_exists(vertex, i);
            if(a){
                edges = (int *) realloc(edges, sizeof(int)); // Memory alocating in the edge's pointer.
                if(!edges){
                    printf("There was an error on memory allocate to edges.\n");
                    exit(1);
                }
                edges[edges_pointer] = i; // Edge's pointer receives the vertex's index where the edge is.
                edges_pointer++;
                (*n_v)++;
            }
        }
        return edges;
    }
    else printf("Vertex's index (%d) has surpassed matrix's limit size.\n", vertex);
    return NULL;
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

void initialize_heap(int qtd){
    Min_Heap.arr = (element *) realloc(Min_Heap.arr, qtd * sizeof(int));
    if(!Min_Heap.arr) printf("SMT.\n");
}

void swap(element *a, element *b){
    element c = *a;
    *a = *b;
    *b = c;
}

void bubble_up(int index){
    int i = index;
    while(i > 0 && Min_Heap.arr[i].distance <= Min_Heap.arr[(i - 1) / 2].distance){
        swap(&Min_Heap.arr[i], &Min_Heap.arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heap_insert(int dist, int vertex){
    if(Min_Heap.num_elementos == qtd_elementos){
        qtd_elementos++;
        initialize_heap(qtd_elementos);
    }
    Min_Heap.arr[Min_Heap.num_elementos].distance = dist;
    Min_Heap.arr[Min_Heap.num_elementos].vertex = vertex;
    Min_Heap.num_elementos++;
    bubble_up(Min_Heap.num_elementos - 1);
}

void bubble_down(int index){
    int left = 2 * index + 1, right = 2 * index + 2 + 1, m = index;
    if(left < Min_Heap.num_elementos && Min_Heap.arr[left].distance <= Min_Heap.arr[m].distance) m = left;
    if(right < Min_Heap.num_elementos && Min_Heap.arr[right].distance <= Min_Heap.arr[m].distance) m = right;
    if(m != index){
        swap(&Min_Heap.arr[m], &Min_Heap.arr[index]);
        bubble_down(m);
    }
}

element heap_extract(){
    element r = Min_Heap.arr[0];
    swap(&Min_Heap.arr[0], &Min_Heap.arr[Min_Heap.num_elementos - 1]);
    Min_Heap.num_elementos--;
    bubble_down(0);
    return r;
}

void initialize_d_p(){
    arr.distance = (int *) malloc(graph.vertices_amount * sizeof(int));
    arr.parent = (int *) malloc(graph.vertices_amount * sizeof(int));
    for(int i = 0; i < graph.vertices_amount; i++){
        arr.distance[i] = INF;
        arr.parent[i] = -1;
    }
}

void dijkstra(int source){
    initialize_d_p();
    arr.distance[source] = 0;

    initialize_heap(graph.vertices_amount);
    heap_insert(arr.distance[source], source);

    for(int i = 0; i < graph.vertices_amount; i++){
        element d_u = heap_extract();
        int n_adj_vertices = 0;
        int *edges = adjacent_edges(d_u.vertex, &n_adj_vertices);
        if(edges){
            int i = 0;
            while(i < n_adj_vertices){
                element aux;
                aux.vertex = edges[i];
                aux.distance = graph.matrix_adj[aux.vertex][edges[i]];
                if(arr.distance[d_u.vertex] + aux.distance < arr.distance[aux.vertex]){
                    arr.distance[aux.vertex] = arr.distance[d_u.vertex] + aux.distance;
                    arr.parent[aux.vertex] = d_u.vertex;
                }
                i++;
            }
            free(edges);
        }
    }
}