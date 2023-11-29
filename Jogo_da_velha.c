#include <stdio.h>
#include <stdbool.h>

void printa_jogo(int mat[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(mat[i][j] != 0) printf("%d", mat[i][j]);
            if(j < 2) printf(" | ");
        }
        if(i < 2) printf("\n------\n");
        printf("\n");
    }
}

bool verifica_col(int jogo[3][3], int l1, int l2, int l3, int col){
    if(jogo[l1][col] == jogo[l2][col] && jogo[l2][col] == jogo[l3][col]) return true;
    return false;
}

bool verifica_diag(int jogo[3][3], int lc1, int lc2, int lc3){
    if(jogo[lc1][lc1] == jogo[lc2][lc2]  && jogo[lc2][lc2] == jogo[lc3][lc3]) return true;
    return false;
}

bool verifica_linha(int jogo[3][3], int linha, int col1, int col2, int col3){
    if(jogo[linha][col1] == jogo[linha][col2] && jogo[linha][col2] == jogo[linha][col3]) return true;
    return false;
}

int verifica_jogo(int jogo[3][3]){
    for(int i = 0; i < 3; i++){
        if(verifica_linha(jogo, i, 0, 1, 2) || verifica_col(jogo, i, i + 1, i + 2, i) || verifica_diag(jogo, i, i + 1, i + 2)){
            return jogo[i][0];
        }
    }
    return 0;
}

int main(void){
    int jogo[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int preenchidos = 0;
    int linha, col;
    int opcao;

    printf("1: x\n2: O\nDigite qual voce quer ser: ");
    scanf("%d", &opcao);
   
    int fim = 0;

    while(!fim){
        printf("Jogo atual:\n");
        printa_jogo(jogo);

        printf("Linha e coluna para inserir %d? ", opcao);
        scanf("%d %d", &linha, &col);

        jogo[linha][col] = opcao == 1 ? 1: 2;
        preenchidos++;
       
        fim = verifica_jogo(jogo) != 0 ? 1: 0;
        if(fim) printf("%d venceu porra!\n", fim);
       

        // if(opcao == 1)
        // system("cls");
    }

    return 0;
}