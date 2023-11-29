#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define TAM 30

typedef struct{
    int *jazigos;
    int q_jazigos;
    int jazigos_ocupados;
} Cemiterio;

// Ordenacao:
void merge(int *vetor, int l, int m, int r, int *a);
void msort(int *vetor, int l, int r, int *a);
void mergesort(int *vetor, int jazigos_ocupados);

// Busca:
int busca_binaria(int *vetor, int tam_vet, int valor);

// Operacoes:
Cemiterio *inicializar_cemi(int qtd_j, int qtd_a);
int funcao_hash(int K, int M, int i);
bool existe_jazigo(int index, int qtd_j, Cemiterio *cemiterio);
int andar_a_inserir(Cemiterio *c, int num_pessoa,  int qtd_andares);
void inserir(Cemiterio **c, int index, int chave);
void realocar(Cemiterio *cemi_antigo, int qtd_a, Cemiterio **cemi_atualizado);
Cemiterio *novo_cemiterio(Cemiterio *c, int *qtd_andares);
int procurar_pessoa(int num_pessoa, int qtd_andares, int *andar, Cemiterio *c);
void remover_pessoa(int num_pessoa, int num_andares, Cemiterio **c);

int main(void){
    Cemiterio *cemiterio = NULL;
    int qtd_jazigos, qtd_andares;
    char comando[TAM];
    int index;
    int andar = 0;
    int jazigo;

    // printf("Jazigos e Andares: ");
    scanf("%d %d", &qtd_andares, &qtd_jazigos);

    cemiterio = inicializar_cemi(qtd_jazigos, qtd_andares);    

    do{
        int chave;
        // printf("Comando: ");
        scanf(" %[^\n]", comando);

        int index_chave = 4, a = 0, tam_string = strlen(comando);
        char str_aux[TAM];
        while(index_chave < tam_string){
            str_aux[a] = comando[index_chave];
            index_chave++;
            a++;
        }
        str_aux[a] = '\0';
        chave = atoi(str_aux);

        switch(comando[0]){
            case 'A':
                index = andar_a_inserir(cemiterio, chave, qtd_andares);
                if(index == -1){
                    cemiterio = novo_cemiterio(cemiterio, &qtd_andares);
                    index = andar_a_inserir(cemiterio, chave, qtd_andares);
                }
                inserir(&cemiterio, index, chave);
                jazigo = procurar_pessoa(chave, qtd_andares, &andar, cemiterio);
                if(jazigo != -1) printf("%d.%d\n", andar, jazigo);
                else printf("?.?\n");
            break;

            case 'R':
                remover_pessoa(chave, qtd_andares, &cemiterio);
            break;

            case 'Q':
                jazigo = procurar_pessoa(chave, qtd_andares, &andar, cemiterio);
                if(jazigo != -1) printf("%d.%d\n", andar, jazigo);
                else printf("?.?\n");
                andar = 0;
            break;
        }

    }while(comando[0] != 'E');

    return 0;
}

// Ordenacao:
void merge(int *vetor, int l, int m, int r, int *a){
    int i = l, j = m + 1;
    for(int k = l; k <= r; k++){
        if(i > m){
            a[k] = vetor[j];
            j++;
        }
        else if(j > r){
            a[k] = vetor[i];
            i++;
        }
        else if(abs(vetor[i]) <= abs(vetor[j])){
            a[k] = vetor[i];
            i++;
        }
        else{
            a[k] = vetor[j];
            j++;
        }
    }
    for(int k = l; k <= r; k++){
        vetor[k] = a[k];
    }
}

void msort(int *vetor, int l, int r, int *a){
    if(l < r){
        int m = (l + r) / 2;
        msort(vetor, l, m, a);
        msort(vetor, m + 1, r, a);
        merge(vetor, l, m, r, a);
    }
}

void mergesort(int *vetor, int jazigos_ocupados){
    int *a = (int *) calloc(jazigos_ocupados, sizeof(int));
    if(!a){
        printf("Houve um erro ao tentar fazer o mergesort.\n");
        exit(1);
    }
    msort(vetor, 0, jazigos_ocupados - 1, a);
}

// Busca:
int busca_binaria(int *vetor, int tam_vet, int valor){
    int l = 0, r = tam_vet - 1;
    while(l <= r){
        int m = (r + l) / 2;
        if(vetor[m] == valor) return m;
        else{
            if(valor < abs(vetor[m])) r = m - 1;
            else l = m + 1;
        }
    }
    return -1;
}

// Operacoes:
Cemiterio *inicializar_cemi(int qtd_j, int qtd_a){
    Cemiterio *c = (Cemiterio *) calloc(qtd_a, sizeof(Cemiterio));
    if(!c){
        printf("Houve um erro ao alocar memoria para criar os andares do cemiterio.\n");
        exit(1);
    }

    for(int i = 0; i < qtd_a; i++){
        c[i].q_jazigos = qtd_j;
        c[i].jazigos_ocupados = 0;
        c[i].jazigos = (int *) calloc(qtd_j, sizeof(int));
        if(!c[i].jazigos){
            printf("Houve um erro ao alocar memoria para criar os jazigos de cada andar do cemiterio.\n");
            exit(1);
        }
    }
    return c;
}

int funcao_hash(int K, int M, int i){
    if(K < 0) return ((K * (-1)) + i) % M;
    return (K + i) % M;
}

bool existe_jazigo(int index, int qtd_j, Cemiterio *cemiterio){
    if(cemiterio[index].jazigos_ocupados < qtd_j) return true;
    return false;
}

int andar_a_inserir(Cemiterio *c, int num_pessoa,  int qtd_andares){
    int tentativas = 0;
    bool lotado = true;
    int index;
    while(tentativas < qtd_andares && lotado){ // Enquanto nao visitamos todos os andares e os que visitamos estão lotados, faca...
        index = funcao_hash(num_pessoa, qtd_andares, tentativas);
        if(existe_jazigo(index, c[index].q_jazigos, c)) lotado = false; // Se existir um jazigo disponivel no andar, sairemos do while.
        else tentativas++;
    }
    if(!lotado) return index;
    return -1;
    // Se todos os andares estiverem lotados, retorna -1 para aumentar o tamanho da tabela.
}

void inserir(Cemiterio **c, int index, int chave){
    int ultimo_jazigo = (*c)[index].jazigos_ocupados; // Index da ultima posicao na sequência de jazigos do andar.
    (*c)[index].jazigos[ultimo_jazigo] = chave;
    (*c)[index].jazigos_ocupados++;
    if((*c)[index].jazigos_ocupados > 1) mergesort((*c)[index].jazigos, (*c)[index].jazigos_ocupados); // Ordenando apos a insercao.
}

void realocar(Cemiterio *cemi_antigo, int qtd_a, Cemiterio **cemi_atualizado){
    for(int i = 0; i < qtd_a; i++){
        for(int j = 0; j < cemi_antigo[i].jazigos_ocupados; j++){
            if(cemi_antigo[i].jazigos[j] > 0){
                int index = andar_a_inserir(*cemi_atualizado, cemi_antigo[i].jazigos[j], ((qtd_a * 2) + 1));
                inserir(cemi_atualizado, index, cemi_antigo[i].jazigos[j]);
            }
        }
    }
}

Cemiterio *novo_cemiterio(Cemiterio *c, int *qtd_andares){
    Cemiterio *novo = inicializar_cemi(c->q_jazigos, (((*qtd_andares) * 2) + 1)); // Criando um novo cemiterio com (2 * M) + 1 andares.
    realocar(c, (*qtd_andares), &novo);
    (*qtd_andares) = ((*qtd_andares) * 2) + 1; // Atualizando a quantidade de andares.
    // printf("\tO cemiterio agora possui %d andares\n", (*qtd_andares));
    return novo;
}

int procurar_pessoa(int num_pessoa, int qtd_andares, int *andar, Cemiterio *c){ // Retorna o jazigo e o andar que a pessoa se encontra.
    int andares_visitados = 0; // Andares visitados serve tanto como "numero" de tentativas da funcao hash, quanto como um contador para verificar se ja percorremos todo o cemiterio.
    int andar_p;
    while(andares_visitados < qtd_andares){
        andar_p = funcao_hash(num_pessoa, qtd_andares, andares_visitados);
        // printf("andar = %d\n", andar_p);
        int index_pessoa = busca_binaria(c[andar_p].jazigos, c[andar_p].jazigos_ocupados, num_pessoa);
        if(index_pessoa != -1){
            (*andar) = andar_p;
            return index_pessoa;
        }
        andares_visitados++; 
    }
    return -1;
}

void remover_pessoa(int num_pessoa, int num_andares, Cemiterio **c){
    int andar = 0;
    int removido = procurar_pessoa(num_pessoa, num_andares, &andar, (*c));
    if(removido != -1){
        (*c)[andar].jazigos[removido] *= -1;
        printf("%d.%d\n", andar, removido);
    }
    else printf("?.?\n");
}