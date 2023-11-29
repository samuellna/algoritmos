#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int *arr;
    int num_elementos;
} Heap;

Heap Min_Heap;
int qtd_elementos;

void menu();
void initialize(int qtd);
void swap(int *a, int *b);
void bubble_up(int index);
void heap_insert(int value);
int heap_extract();
void bubble_down(int index);
void print_heap();

int main(void){
    printf("Numero de elementos inicialmente na min-heap: ");
    scanf("%d", &qtd_elementos);
    initialize(qtd_elementos);
    Min_Heap.num_elementos = 0;

    int opcao, valor;

    do{
        menu();
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                heap_insert(valor);
            break;
        
            case 2:
                printf("%d foi removido da min-heap.\n", heap_extract());
            break;

            case 3:
                print_heap();
            break;

            case 4:
                system("cls");
            break;

            default:
            break;
        }
    } while(opcao != 0);
    free(Min_Heap.arr);

    return 0;
}

void menu(){
    printf("1... Inserir um valor na Min-Heap\n2... Remover a raiz\n3... Printar a heap\n4... Limpar a tela\n0... Sair\nDigite uma dessas opcoes: ");
}

void initialize(int qtd){
    Min_Heap.arr = (int *) realloc(Min_Heap.arr, qtd * sizeof(int));
    if(!Min_Heap.arr) printf("SMT.\n");
}

void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

void bubble_up(int index){
    int i = index;
    while(i > 0 && Min_Heap.arr[i] <= Min_Heap.arr[(i - 1) / 2]){
        swap(&Min_Heap.arr[i], &Min_Heap.arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heap_insert(int value){
    if(Min_Heap.num_elementos == qtd_elementos){
        qtd_elementos++;
        initialize(qtd_elementos);
    }
    Min_Heap.arr[Min_Heap.num_elementos] = value;
    Min_Heap.num_elementos++;
    bubble_up(Min_Heap.num_elementos - 1);
}

void bubble_down(int index){
    int left = 2 * index + 1, right = 2 * index + 2 + 1, m = index;
    if(left < Min_Heap.num_elementos && Min_Heap.arr[left] <= Min_Heap.arr[m]) m = left;
    if(right < Min_Heap.num_elementos && Min_Heap.arr[right] <= Min_Heap.arr[m]) m = right;
    if(m != index){
        swap(&Min_Heap.arr[m], &Min_Heap.arr[index]);
        bubble_down(m);
    }
}

int heap_extract(){
    int r = Min_Heap.arr[0];
    swap(&Min_Heap.arr[0], &Min_Heap.arr[Min_Heap.num_elementos - 1]);
    Min_Heap.num_elementos -= 1;
    bubble_down(0);
    return r;
}

void print_heap(){
    printf("[");
    for(int i = 0; i < Min_Heap.num_elementos; i++){
        printf("%d", Min_Heap.arr[i]);
        if(i < Min_Heap.num_elementos - 1) printf(", ");
    }
    printf("]\n");
}