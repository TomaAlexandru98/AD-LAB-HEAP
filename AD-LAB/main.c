#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2


typedef struct node_t {
    int data ;
} node_t ;


typedef struct MinHeap {
    int size_heap ;
    node_t *element ;
} MinHeap ;

//Functie care initializeaza MinHeap-ul cu dimensiunea 0
MinHeap InitMinHeap(int size_heap) {
    MinHeap heap ;
    heap.size_heap = 0 ;
    return heap ;
}

//Functie care schimba datele din doua noduri folosing pointeri
void swap(node_t *n1, node_t *n2) {
    node_t temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}
//Functie care asigura ca propietatea heap-ului nu este incalcata in cazul in care este adaugat un nod sau este format un MinHeap dintr-un vector
void HeapProperty( MinHeap *heap, int iterator ) {
    int smallest = ( LCHILD( iterator ) < heap->size_heap && heap->element[LCHILD( iterator )].data < heap->element[iterator].data ) ? LCHILD(iterator) : iterator ;
    if( RCHILD( iterator ) < heap->size_heap && heap->element[RCHILD(iterator)].data < heap->element[smallest].data ) {
        smallest = RCHILD(iterator) ;
    }
    if( smallest != iterator ) {
        swap (&( heap->element[iterator] ) , &( heap->element[smallest] )) ;
        HeapProperty( heap , smallest ) ;
    }
}


//Functie care realizeaza un MinHeap folosing un vector de numere
void BuildMinHeap( MinHeap *heap, int *array, int size_heap ) {
    int iterator ;
    for( iterator = 0 ; iterator < size_heap ; iterator++ ) {
        if( heap->size_heap ) {
              heap->element = realloc( heap->element , ( heap->size_heap + 1 ) * sizeof( node_t )) ;
        }   else {
              heap->element = malloc( sizeof ( node_t )) ;
        }
              node_t nd ;
              nd.data = array[iterator] ;
              heap->element[( heap->size_heap )++] = nd ;
    }
    for( iterator = ( heap->size_heap - 1) / 2 ; iterator >= 0 ; iterator-- ) {
        HeapProperty( heap , iterator ) ;
    }
}

//Functie care parcurge MinHeap-ul si il afiseaza
void PreorderTraversal( MinHeap *heap, int iterator) {
    if( LCHILD( iterator ) < heap->size_heap ) {
        PreorderTraversal( heap , LCHILD( iterator )) ;
    }
    if( RCHILD( iterator ) < heap->size_heap ) {
        PreorderTraversal( heap , RCHILD( iterator )) ;
    }
    printf("%d ", heap->element[iterator].data) ;
}

//Functie care verifica daca un numar dat exista in MinHeap
void CheckNumberExist( MinHeap *heap , int iterator , int check_number ){
    if( LCHILD( iterator ) < heap->size_heap ) {
        PreorderTraversal( heap , LCHILD( iterator )) ;
    }
    if( RCHILD( iterator ) < heap->size_heap ) {
        PreorderTraversal( heap , RCHILD( iterator )) ;
    }
    if( heap->element[iterator].data == check_number ){
         printf( "YES" );
    }      else{
        printf( "NO" );
    }

}

//Functie care sterge un numar dat din MinHeap
void DeleteNumber( MinHeap *heap , int iterator , int delete_number ){
  if( LCHILD( iterator ) < heap->size_heap ) {
        PreorderTraversal( heap , LCHILD( iterator )) ;
    }
    if( RCHILD( iterator ) < heap->size_heap ) {
        PreorderTraversal( heap , RCHILD( iterator )) ;
    }
    if( heap->element[iterator].data != delete_number ){
         printf( "Number doesn't exist!" );
    }      else{
         if( heap->size_heap ) {
           heap->element[iterator] = heap->element[--( heap->size_heap )] ;
           heap->element = realloc( heap->element , heap->size_heap * sizeof( node_t )) ;
           HeapProperty( heap , 0 );
         }
    }

}


int main(){
  int array[1200] , iterator , check_number , delete_number , size_array , size_heap   ;
  MinHeap *heap;
printf( "Dimensiunea vectorului este : " );
scanf( "%d" , &size_array );
printf( "Dati elementele : " );
for( iterator = 0 ; iterator < size_array ; iterator++ ){
    scanf( "%d" , &array[size_array] );
}
printf( "Numarul a carui prezenta in MinHeap trebuie verificata : " );
scanf( "%d" , &check_number );
printf( "Numarul pe care doriti sa il stergeti din MinHeap : " );
scanf( "%d" , &delete_number );
InitMinHeap( size_heap );
BuildMinHeap( heap , array , size_heap );
PreorderTraversal( heap , iterator );
CheckNumberExist( heap , iterator , check_number );
DeleteNumber( heap , iterator , delete_number );
return 0;
}
