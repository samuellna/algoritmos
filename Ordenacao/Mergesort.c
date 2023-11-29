#include <stdio.h>
#define TAM 50

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

int main(void){
    int vetor[TAM];
    
    for(int i = 0; i < 50; i++){ 
        scanf("%d", &vetor[i]);
    }
    mergesort(vetor);

    for(int i = 0; i < 50; i++){
        printf("%d ", vetor[i]);
    }
    return 0;
}