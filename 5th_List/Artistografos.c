#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int **arr_quadras;
    int num_Quadras;
} Quadras;

int *visitados;
Quadras *q;

void deleta_Quadras(); // Basicamente destroi o grafo.
Quadras *criar_Quadras(int num_Quadras); // Cria o grafo de quadras.
void conecta_quadras(int a, int b, int distancia); // Cria as arestas (ruas) entre as quadras.
int origem(char string[], int *index); // A
int destino(char string[], int *index); // B
void verifica_evento(char comando[]); // Trata a string para saber se deve criar mais uma rua ou verificar o menor caminho de A para B.

int main(void){
    int qtd_quadras, qtd_ruas, qtd_eventos;
    int a, b, distancia; // A = quadra1, B = quadra2 e a distancia entre as duas.
    char *evento = (char *) malloc(sizeof(char));

    printf("Quantidade de quadras, ruas e eventos: ");
    scanf("%d %d %d", &qtd_quadras, &qtd_ruas, &qtd_eventos);

    q = criar_Quadras(qtd_quadras);

    for(int i = 0; i < qtd_ruas; i++){
        printf("A, B e distancia(A, B): ");
        scanf("%d %d %d", &a, &b, &distancia);
        conecta_quadras(a, b, distancia); // Conectando as quadras.
    }

    for(int i = 0; i < qtd_eventos; i++){
        printf("Evento %d: ", i);
        scanf(" %[^\n]", evento);
        
    }

    deleta_Quadras(q);
    return 0;
}

void deleta_Quadras(){
    if(q->arr_quadras == NULL) return; // Verifying if the graph really exists.
    for(int i = 0; i < q->num_Quadras; i++){
        if(q->arr_quadras[i]) free(q->arr_quadras[i]); // Releasing memory.
    }
    q->num_Quadras = 0;
    free(q->arr_quadras);
}

Quadras *criar_Quadras(int num_Quadras){
    Quadras *q = (Quadras *) malloc(sizeof(Quadras));
    if(!q){
        printf("Houve um erro ao criar as Quadras.\n");
        free(q);
        exit(1);
    }

    q->arr_quadras = (int **) calloc(sizeof(int *), num_Quadras);
    for(int i = 0; i < num_Quadras; i++){
        q->arr_quadras[i] = (int *) calloc(sizeof(int), num_Quadras);
        if(!q->arr_quadras[i]){
            printf("There was an error at matrix's creating.\n");
            destroy_graph(q);
            return NULL;
        }
    }
    q->num_Quadras = num_Quadras;
    return q;
}

void conecta_quadras(int a, int b, int distancia){
    if((a < q->num_Quadras && b < q->num_Quadras) && (a >= 0 && b >= 0)){ // Checking if the index is greater than 0 and less than vertices amount.
        if(q->arr_quadras){
            q->arr_quadras[a][b] = distancia;
            q->arr_quadras[b][a] = distancia;
        }
        else printf("Nao ha sequer uma rua no grafo.\n");
    }
    else printf("Os pontos de origem/destino estao fora do limite do grafo de Quadras.\n");
}

int origem(char string[], int *index){
    char *str_aux = (char *) malloc(sizeof(char));
    int i = 0;
    while(string[(*index)] != ' '){
        str_aux[i] = string[(*index)];
        i++;
        (*index)++;
    }
    str_aux[i] = '\0';
    (*index)++; // Pulando o ' '.
    return atoi(str_aux);
}

int destino(char string[], int *index){
    char *str_aux = (char *) malloc(sizeof(char));
    int i = 0;
    int tam_string = strlen(string);

    while(string[(*index)] != ' ' && (*index) < tam_string){ // Se for ' ', entao e o comando 1. Se o index for >= tam_string, entao e o comando 2.
        str_aux[i] = string[(*index)];
        i++;
        (*index)++;
    }
    str_aux[i] = '\0';
    (*index)++; // Pulando o ' '.
    return atoi(str_aux);
}

int nova_dist(char string[], int *index){
    int i = 0;
    int tam_s = strlen(string);
    char *str = (char *) malloc(sizeof(char));

    while((*index) < tam_s){
        str[i] = string[(*index)];
        i++;
        (*index)++;
    }
    str[i] = '\0';
    return atoi(str);
}

void verifica_evento(char comando[]){
    int index_str = 2;
    int x = origem(comando, &index_str);
    int y = destino(comando, &index_str);

    if(comando[0] == '1'){
        int dist_x_y = nova_dist(comando, &index_str);
        conecta_quadras(x, y, dist_x_y);
    }
    else{
        
    }
}