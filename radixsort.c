#include <stdio.h>        // c1
#include <stdlib.h>       // c2
#include <time.h>         // c3

#define MAX 1000000000    // c4

int getMax(int *arr, int n)
{
  int max = arr[0];                 // c5
  
  for(int i = 1; i < n; i++)        // c6 + c7*(n) + c8*(n-1)
  {
    if(arr[i] > max)                // c9*(n-1)
    {
      max = arr[i];                 // c10 (até n-1 vezes)
    }
  }

  return(max);                      // c11
}

void countingSort(int *arr, int n, int exp)
{
  int *output = (int*)malloc(n * sizeof(int)); // c12
  int count[10] = {0};                         // c13

  for(int i = 0; i < n; i++)       // c14 + c15*(n) + c16*(n-1)
  {
    count[(arr[i] / exp) % 10]++;  // c17*(n)
  }

  for(int i = 1; i < 10; i++)      // c18 + c19*(10) + c20*(9)
  {
    count[i] += count[i - 1];      // c21*(9)
  }

  for(int i = n - 1; i >= 0; i--)  // c22 + c23*(n) + c24*(n-1)
  {
    int digit = (arr[i] / exp) % 10; // c25*(n)
    output[count[digit] - 1] = arr[i]; // c26*(n)
    count[digit]--;                    // c27*(n)
  }

  for(int i = 0; i < n; i++)       // c28 + c29*(n) + c30*(n-1)
  {
    arr[i] = output[i];            // c31*(n)
  }
  
  free(output);                    // c32
}

void radixSort(int *arr, int n)
{
  int max = getMax(arr, n);        // T1(n)

  for (int exp = 1; max / exp > 0; exp *= 10) // c33 + c34*(d) + c35*(d)
  {
    countingSort(arr, n, exp);     // T2(n)
  }

  return;                          // c36
}

void printArray(int *arr, int n)
{
  for(int i = 0; i < n; i++)       // c37*(n)
  {
    printf("%d ", arr[i]);         // c38*(n)
  }
  printf("\n");                    // c39

  return;                          // c40
}

int main()
{
  clock_t start, end;              // c41
  double tempo;                    // c42
  int *arr = (int*)malloc(MAX * sizeof(int)); // c43
  
  srand(time(NULL));               // c44
  for (int i = 0; i < MAX; i++)    // c45 + c46*(MAX) + c47*(MAX-1)
  {
    arr[i] = rand() % MAX;         // c48*(MAX)
  }

  start = clock();                 // c49

  radixSort(arr, MAX);             // T(n)

  end = clock();                   // c50

  tempo = (double)(end - start) / CLOCKS_PER_SEC; // c51

  printf("\n Tempo: %f segundos\n", tempo); // c52

  start = clock();                 // c53

  radixSort(arr, MAX);             // T(n)

  end = clock();                   // c54

  tempo = (double)(end - start) / CLOCKS_PER_SEC; // c55

  printf("\n Tempo: %f segundos para ordear o vetor ordenado\n", tempo); // c56

  free(arr);                       // c57

  return(0);                       // c58
}


/*
========================================
FUNÇÕES DE CUSTO 
========================================

1) getMax:

T1(n) =
c5
+ c6
+ c7*(n)
+ c8*(n-1)
+ c9*(n-1)
+ c10*(n-1)
+ c11

T1(n) = a*n + b
=> O(n)


----------------------------------------

2) countingSort:

T2(n) =
c12 + c13
+ (c14 + c15*n + c16*(n-1))
+ c17*n
+ (c18 + c19*10 + c20*9)
+ c21*9
+ (c22 + c23*n + c24*(n-1))
+ c25*n + c26*n + c27*n
+ (c28 + c29*n + c30*(n-1))
+ c31*n
+ c32

Simplificando:

T2(n) = a*n + b
=> O(n)


----------------------------------------

3) radixSort:

T3(n) =
T1(n)
+ d * T2(n)

T3(n) =
O(n) + d * O(n)

=> T3(n) = O(n*d)


----------------------------------------

4) main:

Inicialização:
O(MAX)

Ordenação:
O(n*d)

----------------------------------------

COMPLEXIDADE FINAL:

T(n) = O(n*d)

Se d constante:
=> O(n)


----------------------------------------

CASOS:

Melhor caso:  Ω(n*d)
Caso médio:   Θ(n*d)
Pior caso:    O(n*d)

========================================
*/
