#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int custo;
    int *diversao;
    int fat_ab;
} Brinquedo;

Brinquedo *b;
int num_b;

int max_item(int item1, int item2);
// int knapsack(int capacidade);
int unbounded_knapsack(int capacidade); 
int *index_diversao(); // Retorna um vetor, cada index do vetor possui o valor da diversao atualizada apos as repeticoes.
int nova_diversao(int index_b, int t); // Funcao que retorna o valor da diversao apos t tentativas.
void inicializa_diversoes(int index, int valor_diversao);
void otimizar(int credito[], int qtd_visitas); // Enquanto o preco do item mais barato > 1, divido o preco de todos os itens e a "capacidade da mochila" por 2.

// Ordeno os brinquedos de acordo com o preco de cada um. O objetivo dessa ordenacao e otimizar o preco dos brinquedos e a "capacidade da mochila".
void mergesort();
void msort(int l, int r, Brinquedo brinq[]);
void merge(int l, int m, int r, Brinquedo aux[]);

int main(){
    int num_visitas;
    int *cred;
    int diversao;
    
    scanf("%d", &num_b);

    b = (Brinquedo *) malloc(num_b * sizeof(Brinquedo));
    
    for(int i = 0; i < num_b; i++){
        scanf("%d %d %d", &diversao, &b[i].fat_ab, &b[i].custo);
        inicializa_diversoes(i, diversao);
    }
    
    mergesort();

    scanf("%d", &num_visitas);
    cred = (int *) malloc(num_visitas * sizeof(int));

    for(int i = 0; i < num_visitas; i++){
        scanf("%d", &cred[i]);
    }
    printf("\n");
    otimizar(cred, num_visitas);

    for(int i = 0; i < num_visitas; i++){
        unbounded_knapsack(cred[i]);
    }

    free(b);
    return 0;
}

void merge(int l, int m, int r, Brinquedo aux[]){
    int i = l, j = m + 1;
    for(int k = l; k <= r; k++){
        if(i > m){
            aux[k] = b[j];
            j++;
        }
        else if(j > r){
            aux[k] = b[i];
            i++;
        }
        else if(b[i].custo <= b[j].custo){
            aux[k] = b[i];
            i++;
        }
        else{
            aux[k] = b[j];
            j++;
        }
    }
    for(int k = l; k <= r; k++){
        b[k] = aux[k];
    }
}

void msort(int l, int r, Brinquedo brinq[]){
    if(l < r){
        int m = (l + r) / 2;
        msort(l, m, brinq);
        msort(m + 1, r, brinq);
        merge(l, m, r, brinq);
    }
}

void mergesort(){
    Brinquedo *brinq = (Brinquedo *) malloc(num_b * sizeof(Brinquedo));
    msort(0, num_b - 1, brinq);
}

int max_item(int item1, int item2){
    return item1 >= item2 ? item1 : item2;
}

int nova_diversao(int index_b, int t){
    return (t - 1) * (t - 1) * b[index_b].fat_ab;
}

void inicializa_diversoes(int index, int valor_diversao){
    b[index].diversao = (int *) malloc(sizeof(int));
    b[index].diversao[0] = valor_diversao; // A diversao inicialmente possui o valor integral de "valor_diversao"
    
    int t = 1; 
    while(b[index].diversao[t - 1] > 0){
        b[index].diversao = (int *) realloc(b[index].diversao, (t + 1) * sizeof(int));
        b[index].diversao[t] = (valor_diversao - nova_diversao(index, t + 1)) > 0 ? valor_diversao - nova_diversao(index, t + 1) : 0;
        t++;
    }
}

void otimizar(int credito[], int qtd_visitas){
    while(b[0].custo != 1){
        b[0].custo /= 2; // Divido o item de menor preco por 2.
        for(int i = 1; i < num_b; i++){
            b[i].custo /= 2; // Divido todos os outros itens por 2.
        }
        for(int i = 0; i < qtd_visitas; i++){
            credito[i] /= 2; // Divido a capacidade da mochila por 2 para cada visita.
        }
    }
}

// int knapsack(int capacidade){
//     int **solucao = (int **) malloc((num_b + 1) * sizeof(int *));
//     for(int i = 0; i < capacidade; i++){
//         solucao[i] = (int *) calloc(num_b, sizeof(int));
//     }

//     int m = 1, k = 1;
//     for(m = 1; m <= num_b; m++){
//         for(k = 1; k <= capacidade; k++){
//             if(k < b[m - 1].custo) solucao[m][k] = solucao[m - 1][k];
//             else solucao[m][k] = max_item(solucao[m - 1][k], solucao[m - 1][k - b[m - 1].custo] + b[m - 1].diversao);
//         }
//     }
//     return solucao[num_b][k];
// }

int *index_diversao(){
    int *arr_index = (int *) malloc(num_b * sizeof(int)); 
    for(int i = 0; i < num_b; i++){
        int j = 0;
        while(b[i].diversao[j]){
            j++;
        }
        arr_index[i] = j + 1;
    }
    return arr_index;
}

int unbounded_knapsack(int capacidade){
    int *s = (int *) calloc((capacidade + 1), sizeof(int)); // Vetor de solucoes.
    int *arr = index_diversao(); // Array com o "numero de diversoes" de cada brinquedo, esse numero de diversoes e o calculo do aborrecimento.
    int *arr_aux = (int *) calloc(num_b, sizeof(int));

    for(int i = 1; i <= capacidade; i++){
        for(int j = 0; j < num_b; j++){
            if(b[j].custo <= i) s[i] = max_item(s[i], s[i - b[j].custo] + b[j].diversao[arr_aux[j]]);
            if(s[i] == s[i - b[j].custo] + b[j].diversao[arr_aux[j]] && arr_aux[j] != arr[j]) arr_aux[j]++;
        }
    }
    return s[capacidade];
}