#include <stdio.h>
#define TAM 50

void merge(int vetor[], int l, int m, int r, int a[]);
void msort(int vetor[], int l, int r, int a[]);
void mergesort(int vetor[TAM]);
int binary_search(int vetor[], int tam_vet, int valor);

int main(void){
    int v[TAM];
    for(int i = 0; i < TAM; i++){
        scanf("%d", &v[i]);
    }
    mergesort(v);
    int p;
    printf("Procurar: ");
    scanf("%d", &p);
    int a = binary_search(v, 50, p);
    printf("%d esta em %d.\n", p, a);
    return 0;
}

void merge(int vetor[], int l, int m, int r, int a[]){
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
        else if(vetor[i] <= vetor[j]){
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

void msort(int vetor[], int l, int r, int a[]){
    if(l < r){
        int m = (l + r) / 2;
        msort(vetor, l, m, a);
        msort(vetor, m + 1, r, a);
        merge(vetor, l, m, r, a);
    }
}

void mergesort(int vetor[TAM]){
    int a[TAM];
    msort(vetor, 0, 49, a);
}

int binary_search(int vetor[], int tam_vet, int valor){
    int l = 0, r = tam_vet - 1;
    while(l <= r){
        int m = (r + l) / 2;
        if(vetor[m] == valor) return m;
        else{
            if(valor < vetor[m]) r = m - 1;
            else l = m + 1;
        }
    }
    return -1;
}