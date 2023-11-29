#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int custo;
    int diversao;
    int fat_ab;
} Brinquedo;

Brinquedo *b;
int num_b;

int max_item(int item1, int item2);
int knapsack(int capacidade);
int unbounded_knapsack(int capacity);
int nova_diversao(int index, int t);


int main(){
    int num_visitas;
    int cred;

    scanf("%d", &num_b);

    b = (Brinquedo *) malloc(num_b * sizeof(Brinquedo));
    for(int i = 0; i < num_b; i++){
        scanf("%d %d %d", &b[i].diversao, &b[i].fat_ab, &b[i].custo);
    }

    for(int i = 0; i < num_b; i++){
        
    }



    scanf("%d", &num_visitas);
    for(int i = 0; i < num_visitas; i++){
        scanf("%d", &cred);

    }

    free(b);
    return 0;
}

void merge(Brinquedo br[], int l, int m, int r, Brinquedo aux[]){
    int i = l, j = m + 1;
    for(int k = l; k <= r; k++){
        if(i > m){
            aux[k] = br[j];
            j++;
        }
        else if(j > r){
            aux[k] = br[i];
            i++;
        }
        else if(br[i].custo <= br[j].custo){
            aux[k] = br[i];
            i++;
        }
        else{
            aux[k] = br[j];
            j++;
        }
    }
    for(int k = l; k <= r; k++){
        br[k] = aux[k];
    }
}

void msort(Brinquedo B[], int l, int r, Brinquedo brinq[]){
    if(l < r){
        int m = (l + r) / 2;
        msort(B, l, m, brinq);
        msort(B, m + 1, r, brinq);
        merge(B, l, m, r, brinq);
    }
}

void mergesort(Brinquedo brinquedos[]){
    Brinquedo *brinq = (Brinquedo *) malloc(num_b * sizeof(Brinquedo));
    msort(brinquedos, 0, num_b - 1, brinq);
}

int max_item(int item1, int item2){
    return item1 >= item2 ? item1 : item2;
}

int nova_diversao(int index, int t){
    return (t - 1) * (t - 1) * b[index].fat_ab;
}

void adicionar_brinquedos(int index_b, int valor_brinq){
    int t = 2;
    while(valor_brinq >= 0){
        valor_brinq = nova_diversao(index_b, t);
        num_b++;
        b = (Brinquedo *) realloc(b, num_b * sizeof(Brinquedo));
        b[num_b].diversao = valor_brinq;
        b[num_b].custo = b[index_b].custo;
        b[num_b].fat_ab = b[index_b].fat_ab;
        t++;
    }
}

int knapsack(int capacidade){
    int **solucao = (int **) malloc((num_b + 1) * sizeof(int *));
    for(int i = 0; i < capacidade; i++){
        solucao[i] = (int *) calloc(num_b, sizeof(int));
    }

    int m = 1, k = 1;
    for(m = 1; m <= num_b; m++){
        for(k = 1; k <= capacidade; k++){
            if(k < b[m - 1].custo) solucao[m][k] = solucao[m - 1][k];
            else solucao[m][k] = max_item(solucao[m - 1][k], solucao[m - 1][k - b[m - 1].custo] + b[m - 1].diversao);
        }
    }
    return solucao[num_b][k];
}

int unbounded_knapsack(int capacity){
    int *s = (int *) calloc((num_b + 1), sizeof(int));
    int *counter = (int *) malloc(num_b * sizeof(int));

    for(int i = 0; i < num_b; i++){
        counter[i] = 1;
    }

    for(int i = 1; i <= capacity; i++){
        for(int j = 0; j < num_b; j++){
            if(b[j].custo <= i){
                s[i] = max_item(s[i], s[i - b[j].custo] + b[j].diversao);
                counter[j]++;
            }
            b[j].diversao = nova_diversao(j, counter[j]);
        }
    }

    free(counter);
    return s[capacity];
}