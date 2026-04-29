#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000000

int getMax(int *arr, int n)
{
  int max = arr[0];
  
  for(int i = 1; i < n; i++)
  {
    if(arr[i] > max)
    {
      max = arr[i];
    }
  }

  return(max);
}

void countingSort(int *arr, int n, int exp)
{
  int *output = (int*)malloc(n * sizeof(int));
  int count[10] = {0};

  // Contagem de recorrencia
  for(int i = 0; i < n; i++)
  {
    count[(arr[i] / exp) % 10]++;
  }

  // Soma acumulada
  for(int i = 1; i < 10; i++)
  {
    count[i] += count[i - 1];
  }

  // Construção do array ordenado de trás pra frente
  for(int i = n - 1; i >= 0; i--)
  {
    int digit = (arr[i] / exp) % 10;
    output[count[digit] - 1] = arr[i];
    count[digit]--;
  }

  for(int i = 0; i < n; i++)
  {
    arr[i] = output[i];
  }
  
  free(output);
}

void radixSort(int *arr, int n)
{
  int max = getMax(arr, n);

  for (int exp = 1; max / exp > 0; exp *= 10)
  {
    countingSort(arr, n, exp);
  }

  return;
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

int
main()
{
  clock_t start, end;
  double tempo;
  int *arr = (int*)malloc(MAX * sizeof(int));
  
  srand(time(NULL));
  for (int i = 0; i < MAX; i++)
  {
    arr[i] = rand() % MAX;
  }

  // puts("\nVetor desordenado:");
  // printArray(arr, MAX);

  start = clock();

  radixSort(arr, MAX);

  end = clock();

  tempo = (double)(end - start) / CLOCKS_PER_SEC;

  // puts("\nVetor ordenado:");
  // printArray(arr, MAX);

  printf("\n Tempo: %f segundos\n", tempo);

  start = clock();

  radixSort(arr, MAX);

  end = clock();

  tempo = (double)(end - start) / CLOCKS_PER_SEC;

  printf("\n Tempo: %f segundos para ordear o vetor ordenado\n", tempo);


  free(arr);

  return(0);
}
