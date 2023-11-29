#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXDEVERTICES 500
#define CAPACIDADE 500

struct Edge{
    int vertic;
    int peso;
    struct Edge *next;
};

struct Graph{
    int num_vertices;
    struct Edge *listaAdjc[MAXDEVERTICES];
};

struct MinHeap{
    int *array;
    int capacity;
    int size;
};

void Mineheap(struct MinHeap *minHeap, int p){
    int menor = p;
    int left = 2 * p + 1;
    int right = 2 * p + 2;

    if(left < minHeap->size && minHeap->array[left] < minHeap->array[menor]){
        menor = left;
    }

    if(right < minHeap->size && minHeap->array[right] < minHeap->array[menor]){
        menor = right;
    }

    if (menor != p){
        int temp = minHeap->array[p];
        minHeap->array[p] = minHeap->array[menor];
        minHeap->array[menor] = temp;
        Mineheap(minHeap, menor);
    }
}

struct MinHeap *criarMinHeap(int capacity){
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (int *)malloc(capacity * sizeof(int));
    return minHeap;
}

void insertMinHeap(struct MinHeap *minHeap, int k){
    if (minHeap->size == minHeap->capacity){
        printf("erro heap cheia man\n");
        return;
    }

    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i] = k;

    while (i != 0 && minHeap->array[(i - 1) / 2] > minHeap->array[i]){
        int temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        minHeap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int extractMin(struct MinHeap *minHeap){
    if (minHeap->size <= 0){
        printf("erro heap cheia man\n");
        return -1;
    }

    if (minHeap->size == 1){
        minHeap->size--;
        return minHeap->array[0];
    }

    int root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    Mineheap(minHeap, 0);

    return root;
}

struct Graph *criargrafo(int num_vertices){
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++){
        graph->listaAdjc[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph *graph, int s, int destino, int peso){
    struct Edge *new_edge = (struct Edge *)malloc(sizeof(struct Edge));
    new_edge->vertic = destino;
    new_edge->peso = peso;
    new_edge->next = graph->listaAdjc[s];
    graph->listaAdjc[s] = new_edge;
}

void dijkstra(struct Graph *graph, int source, int *dist, int *anteriores, struct MinHeap *minHeap){
    int num_vertices = graph->num_vertices;

    for(int i = 0; i < num_vertices; i++){
        dist[i] = INT_MAX;
        anteriores[i] = -1;
    }

    dist[source] = 0;
    insertMinHeap(minHeap, source);

    while(minHeap->size > 0){
        int u = extractMin(minHeap);

        struct Edge *edge = graph->listaAdjc[u];
        while (edge != NULL){
            int v = edge->vertic;
            int w = edge->peso;

            if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                anteriores[v] = u;
                insertMinHeap(minHeap, v);
            }

            edge = edge->next;
        }
    }
}

int main(){
    int num_vertices, num_streets, num_events;
    scanf("%d %d %d", &num_vertices, &num_streets, &num_events);

    struct Graph *graph = criargrafo(num_vertices);
    struct MinHeap *minHeap = criarMinHeap(CAPACIDADE);

    for(int i = 0; i < num_streets; i++){
        int A, B, M;
        scanf("%d %d %d", &A, &B, &M);
        addEdge(graph, A, B, M);
    }

    for(int i = 0; i < num_events; i++){
        int type, A, B, M;
        scanf("%d", &type);

        if(type == 1){
            scanf("%d %d %d", &A, &B, &M);
            addEdge(graph, A, B, M);
        }else if (type == 2){
            scanf("%d %d", &A, &B);
            int *dist = (int *)malloc(num_vertices * sizeof(int));
            int *anteriores = (int *)malloc(num_vertices * sizeof(int));

            dijkstra(graph, A, dist, anteriores, minHeap);
            int result = dist[B];
            if (result == INT_MAX)
                result = -1;
            printf("%d\n", result);
            free(dist);
            free(anteriores);

        }
    }

    for (int i = 0; i < num_vertices; i++){
        struct Edge *edge = graph->listaAdjc[i];
        while (edge != NULL)
        {
            struct Edge *temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph);
    free(minHeap->array);
    free(minHeap);

    return 0;
}