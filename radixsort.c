#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000

int getMax(int *arr, int n)
{
  int max = arr[0];                 // c1
  
  for(int i = 1; i < n; i++)        // c2 + c3*(n) + c4*(n-1)
  {
    if(arr[i] > max)                // c5*(n-1)
    {
      max = arr[i];                 // c6 (até n-1 vezes)
    }
  }

  return(max);                      // c7
}

void countingSort(int *arr, int n, int exp)
{
  int *output = (int*)malloc(n * sizeof(int)); // c8
  int count[10] = {0};                        // c9

  for(int i = 0; i < n; i++)       // c10 + c11*(n) + c12*(n-1)
  {
    count[(arr[i] / exp) % 10]++;  // c13*(n)
  }

  for(int i = 1; i < 10; i++)      // c14 + c15*(k) + c16*(k-1)
  {
    count[i] += count[i - 1];      // c17*(k-1)
  }

  for(int i = n - 1; i >= 0; i--)  // c18 + c19*(n) + c20*(n-1)
  {
    int digit = (arr[i] / exp) % 10; // c21*(n)
    output[count[digit] - 1] = arr[i]; // c22*(n)
    count[digit]--;                    // c23*(n)
  }

  for(int i = 0; i < n; i++)       // c24 + c25*(n) + c26*(n-1)
  {
    arr[i] = output[i];            // c27*(n)
  }
  
  free(output);                    // c28
}

void radixSort(int *arr, int n)
{
  int max = getMax(arr, n);        // T1(n)

  for (int exp = 1; max / exp > 0; exp *= 10) // c29 + c30*(k) + c31*(k)
  {
    countingSort(arr, n, exp);     // T2(n)
  }

  return;                          // c32
}

void printArray(int *arr, int n)
{
  for(int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  
  printf("\n");

  return;
}

int main()
{
  clock_t start, end;
  double tempo;
  int *arr = (int*)malloc(MAX * sizeof(int));
  
  srand(time(NULL));

  for (int i = 0; i < MAX; i++)
  {
    arr[i] = rand() % MAX;
  }

  start = clock();

  radixSort(arr, MAX);

  end = clock();

  tempo = (double)(end - start) / CLOCKS_PER_SEC;

  printf("\n Tempo: %f segundos para ordenar o vetor aleatorio\n", tempo);

  start = clock();

  radixSort(arr, MAX);

  end = clock();

  tempo = (double)(end - start) / CLOCKS_PER_SEC;

  printf("\n Tempo: %f segundos para ordenar o vetor ordenado\n", tempo);

  free(arr);

  return(0);
}


/*
========================================
FUNÇÕES DE CUSTO
========================================

1) getMax:

T1(n) =
c1
+ c2
+ c3*(n)
+ c4*(n-1)
+ c5*(n-1)
+ c6*(n-1)
+ c7

T1(n) = a*n + b

=> O(n)


----------------------------------------

2) countingSort:

T2(n) =
c8 + c9
+ (c10 + c11*n + c12*(n-1))
+ c13*n
+ (c14 + c15*k + c16*(k-1))
+ c17*(k-1)
+ (c18 + c19*n + c20*(n-1))
+ c21*n + c22*n + c23*n
+ (c24 + c25*n + c26*(n-1))
+ c27*n
+ c28

Simplificando:

T2(n) = a*n + b*k + c

=> O(n + k)


----------------------------------------

3) radixSort:

T3(n) =
T1(n)
+ k * (c29 + c30 + c31 + T2(n))
+ c32

Como:

T1(n) = O(n)
T2(n) = O(n + k)

Então:

T3(n) =
O(n)
+ k * O(n + k)

=> T3(n) = O(n*k)


----------------------------------------

COMPLEXIDADE FINAL:

T(n) = O(n*k)

Se k constante:
=> O(n)


----------------------------------------

CASOS:

Melhor caso:  Ω(n*k)
Caso médio:   Θ(n*k)
Pior caso:    O(n*k)

========================================
*/