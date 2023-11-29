#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_QUADRAS 500
#define INF INT_MAX // tempo de viagem extremamente longo

typedef struct {
    int destino;
    int minutos;
} Rua;

int quadras;
int ruas;
int matrizAdj[MAX_QUADRAS][MAX_QUADRAS];

void inicializarMatrizAdj() {
    for (int i = 0; i < quadras; i++) {
        for (int j = 0; j < quadras; j++) {
            matrizAdj[i][j] = INF;
        }
        matrizAdj[i][i] = 0; // 0 na diagonal principal
    }
}

void adicionarRua(int a, int b, int minutos) {
    matrizAdj[a][b] = minutos;
}

void dijkstra(int origem, int destino) {
    int dist[MAX_QUADRAS];
    int visitado[MAX_QUADRAS] = {0};

    for (int i = 0; i < quadras; i++) {
        dist[i] = INF;
    }

    dist[origem] = 0;

    for (int contador = 0; contador < quadras - 1; contador++) {
        int u, min_dist = INF;

        for (int v = 0; v < quadras; v++) {
            if (!visitado[v] && dist[v] < min_dist) {
                u = v;
                min_dist = dist[v];
            }
        }

        visitado[u] = 1;

        for (int v = 0; v < quadras; v++) {
            if (!visitado[v] && matrizAdj[u][v] != INF &&
                dist[u] + matrizAdj[u][v] < dist[v]) {
                dist[v] = dist[u] + matrizAdj[u][v];
            }
        }
    }

    if (dist[destino] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[destino]);
    }
}


int main() {
    int eventos;
    scanf("%d %d %d", &quadras, &ruas, &eventos);

    inicializarMatrizAdj();

    for (int i = 0; i < ruas; i++) {
        int a, b, minutos;
        scanf("%d %d %d", &a, &b, &minutos);
        adicionarRua(a, b, minutos);
    }

    for (int i = 0; i < eventos; i++) {
        int tipo, a, b;
        scanf("%d %d %d", &tipo, &a, &b);
        if (tipo == 1) {
            int minutos;
            scanf("%d", &minutos);
            adicionarRua(a, b, minutos);
        } else if (tipo == 2) {
            dijkstra(a, b);
        }
    }

    return 0;
}

