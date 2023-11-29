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

// Busca:
int busca_binaria(int *vetor, int tam_vet, int valor, char comando);

// Tratando string:
int chave(char ch[], int tam_string);

// Operacoes:
Cemiterio *inicializar_cemi(int qtd_j, int qtd_a);
int funcao_hash(int K, int M, int i);
bool existe_jazigo(int index, int qtd_j, Cemiterio *cemiterio);
int andar_a_inserir(Cemiterio *c, int num_pessoa,  int qtd_andares);
void mover_a_direita(Cemiterio **c, int index, int intervalo);
void inserir(Cemiterio **c, int index, int *index_jazigo, int chave);
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
        // printf("Comando: ");
        scanf(" %[^\n]", comando);
        int valor = chave(comando, strlen(comando));

        switch(comando[0]){
            case 'A':
                index = andar_a_inserir(cemiterio, valor, qtd_andares);
                if(index == -1){
                    cemiterio = novo_cemiterio(cemiterio, &qtd_andares);
                    index = andar_a_inserir(cemiterio, valor, qtd_andares);
                }
                inserir(&cemiterio, index, &jazigo, valor);
                printf("%d.%d\n", andar, jazigo);
            break;

            case 'R':
                remover_pessoa(valor, qtd_andares, &cemiterio);
            break;

            case 'Q':
                jazigo = procurar_pessoa(valor, qtd_andares, &andar, cemiterio);
                if(jazigo != -1) printf("%d.%d\n", andar, jazigo);
                else printf("?.?\n");
                andar = 0;
            break;
        }

    }while(comando[0] != 'E');

    return 0;
}

// Busca:
int busca_binaria(int *vetor, int tam_vet, int valor, char comando){
    // A variavel "comando" serve para dizer se a busca binaria esta sendo usada para a insercao.
    if(tam_vet == 0) return 0; // Se nao houver jazigos no andar.
    int l = 0, r = tam_vet - 1;
    while(l <= r){
        int m = (r + l) / 2;
        if(vetor[m] == valor) return m;
        else{
            if(valor < abs(vetor[m])) r = m - 1;
            else l = m + 1;
        }
    }
    if(comando == 'I') return abs(vetor[l]) > valor ? l: l + 1;
    return -1;
}

// Tratando string:
int chave(char ch[], int tam_string){
    int index_chave = 4, a = 0;
    char str_aux[TAM];
    while(index_chave < tam_string){
        str_aux[a] = ch[index_chave];
        index_chave++;
        a++;
    }
    str_aux[a] = '\0';
    return atoi(str_aux);
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

void mover_a_direita(Cemiterio **c, int index, int intervalo){
    for(int i = (*c)[index].jazigos_ocupados; i > intervalo; i--){
        (*c)[index].jazigos[i] = (*c)[index].jazigos[i - 1];
    }
}

void inserir(Cemiterio **c, int index, int *index_jazigo, int chave){
    if((*c)[index].jazigos_ocupados > 0){
        if((*c)[index].jazigos[(*c)[index].jazigos_ocupados - 1] < chave){ // Se o valor a inserir for o maior numero da tabela, inserimos diretamente no final do vetor.
            (*c)[index].jazigos[(*c)[index].jazigos_ocupados] = chave;
            (*index_jazigo) = (*c)[index].jazigos_ocupados;
        }
        else{
            int jazigo_a_inserir = busca_binaria((*c)[index].jazigos, (*c)[index].jazigos_ocupados, chave, 'I');
            mover_a_direita(c, index, jazigo_a_inserir);
            (*c)[index].jazigos[jazigo_a_inserir] = chave;
            (*index_jazigo) = jazigo_a_inserir;
        }
    }
    else{
        (*c)[index].jazigos[0] = chave;
        (*index_jazigo) = 0;
    }
    (*c)[index].jazigos_ocupados++;
}

void realocar(Cemiterio *cemi_antigo, int qtd_a, Cemiterio **cemi_atualizado){
    for(int i = 0; i < qtd_a; i++){
        for(int j = 0; j < cemi_antigo[i].jazigos_ocupados; j++){
            if(cemi_antigo[i].jazigos[j] > 0){
                int index = andar_a_inserir(*cemi_atualizado, cemi_antigo[i].jazigos[j], ((qtd_a * 2) + 1));
                if(index != -1) inserir(cemi_atualizado, index, 0, cemi_antigo[i].jazigos[j]);
            }
        }
    }
}

Cemiterio *novo_cemiterio(Cemiterio *c, int *qtd_andares){
    Cemiterio *novo = inicializar_cemi(c->q_jazigos, (((*qtd_andares) * 2) + 1)); // Criando um novo cemiterio com (2 * M) + 1 andares.
    realocar(c, (*qtd_andares), &novo);
    (*qtd_andares) = ((*qtd_andares) * 2) + 1; // Atualizando a quantidade de andares.
    return novo;
}

int procurar_pessoa(int num_pessoa, int qtd_andares, int *andar, Cemiterio *c){ // Retorna o jazigo e o andar que a pessoa se encontra.
    int andares_visitados = 0; // Andares visitados serve tanto como "numero" de tentativas da funcao hash, quanto como um contador para verificar se ja percorremos todo o cemiterio.
    int andar_p;
    while(andares_visitados < qtd_andares){
        andar_p = funcao_hash(num_pessoa, qtd_andares, andares_visitados);
        // printf("andar = %d\n", andar_p);
        int index_pessoa = busca_binaria(c[andar_p].jazigos, c[andar_p].jazigos_ocupados, num_pessoa, 'P'); // Procurando a pessoa com busca binaria.
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