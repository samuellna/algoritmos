#include <stdio.h>
#include <stdlib.h>

#define MAX_BRINQUEDOS 1000
typedef struct{
    int custo;
    int diversao;
    int fat_ab;
} Brinquedo;

Brinquedo b[MAX_BRINQUEDOS];
int num_b; // Numero de brinquedos

int nova_diversao(int fat_ab, int t);
void adicionar_brinquedos();
int max_item(int item1, int item2);
int knapsack(int capacidade);

int main(void){
    int num_visitas;
    int *cred;

    scanf("%d", &num_b);

    for(int i = 0; i < num_b; i++){
        scanf("%d %d %d", &b[i].diversao, &b[i].fat_ab, &b[i].custo);
    }

    scanf("%d", &num_visitas);
    cred = (int *) malloc(num_visitas * sizeof(int));

    for(int i = 0; i < num_visitas; i++){
        scanf("%d", &cred[i]);
    }
    
    adicionar_brinquedos();

    // for(int i = 0; i < num_b; i++){
    //     printf("Brinquedo %d:\n\tDiversao: %d\n\tCusto: %d\n\tFator de Aborrecimento: %d\n", i, b[i].diversao, b[i].custo, b[i].fat_ab);
    // }

    // for(int i = 0; i < num_visitas; i++){
    //     printf("Capacidade %d: %d\n", i, cred[i]);
    // }

    for(int i = 0; i < num_visitas; i++){
        printf("%d: %d\n", i, knapsack(cred[i]));
    }
    return 0;
}

int nova_diversao(int fat_ab, int t){
    return (t - 1) * (t - 1) * fat_ab;
}

void adicionar_brinquedos(){
    int qtd_aux = num_b; // Quantidade auxiliar de brinquedos.
    int t = 2;

    for(int i = 0; i < num_b; i++){ // O for vai passar em cada brinquedo
        int novo_brinquedo = b[i].diversao - nova_diversao(b[i].fat_ab, t); // O brinquedo com o novo valor apos incluir o fator de aborrecimento.
        while(novo_brinquedo >= 0){
            b[qtd_aux].diversao = novo_brinquedo;
            b[qtd_aux].fat_ab = b[i].fat_ab;
            b[qtd_aux].custo = b[i].custo;
            t++;
            qtd_aux++;
            novo_brinquedo = b[i].diversao - nova_diversao(b[i].fat_ab, t);
        }
        t = 2;
    }
    num_b = qtd_aux;
}

int max_item(int item1, int item2){
    return item1 >= item2 ? item1 : item2;
}

int knapsack(int capacidade){
    int **solucao = (int **) malloc((num_b + 1) * sizeof(int *));
    for(int i = 0; i <= num_b; i++){
        solucao[i] = (int *) calloc((capacidade + 1), sizeof(int));
    }

    int m = 1, k = 1;
    for(m = 1; m <= num_b; m++){
        for(k = 1; k <= capacidade; k++){
            if(k < b[m - 1].custo) solucao[m][k] = solucao[m - 1][k];
            else{
                solucao[m][k] = max_item(solucao[m - 1][k], solucao[m - 1][k - b[m - 1].custo] + b[m - 1].diversao);
                // printf("Solucao[%d][%d] = %d\n", m, k, solucao[m][k]);
            }
        }
    }
    return solucao[num_b][k];
}