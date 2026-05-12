#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

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

  return max;
}

void waitEnter()
{
  printf("\n");
  getchar();
}

void printStep(int *arr, int n, int exp, int finished)
{
  printf("\n========================================================\n\n");

  for(int i = 0; i < n; i++)
  {
    int numero = arr[i];

    int centenas = (numero / 100) % 10;
    int dezenas  = (numero / 10) % 10;
    int unidades = numero % 10;

    // CENTENAS
    if(exp > 100)
    {
      printf(GREEN "%d" RESET, centenas);
    }
    else if(exp == 100)
    {
      if(finished)
      {
        printf(GREEN "%d" RESET, centenas);
      }
      else
      {
        printf(YELLOW "%d" RESET, centenas);
      }
    }

    else
    {
      printf(RED "%d" RESET, centenas);
    }

    // DEZENAS
    if(exp > 10)
    {
      printf(GREEN "%d" RESET, dezenas);
    }
    else if(exp == 10)
    {
      if(finished)
      {
        printf(GREEN "%d" RESET, dezenas);
      }
      else
      {
        printf(YELLOW "%d" RESET, dezenas);
      }
    }
    else
    {
      printf(RED "%d" RESET, dezenas);
    }

    // UNIDADES
    if(exp > 1)
    {
      printf(GREEN "%d" RESET, unidades);
    }

    else if(exp == 1)
    {
      if(finished)
      {
        printf(GREEN "%d" RESET, unidades);
      }
      else
      {
        printf(YELLOW "%d" RESET, unidades);
      }
    }
    else
    {
      printf(RED "%d" RESET, unidades);
    }

    printf("  ");
  }

  printf("\n\n========================================================\n");
}

void countingSort(int *arr, int n, int exp)
{
  int *output = (int*)malloc(n * sizeof(int));
  int count[10] = {0};

  printf("\nContando ocorrencias dos digitos:\n");

  for(int i = 0; i < n; i++)
  {
    int digit = (arr[i] / exp) % 10;
    count[digit]++;

    printf("Numero %d -> digito %d\n", arr[i], digit);
  }

  waitEnter();

  printf("\nVetor count:\n");
  for(int i = 0; i < 10; i++)
  {
    printf("count[%d] = %d\n", i, count[i]);
  }

  for(int i = 1; i < 10; i++)
  {
    count[i] += count[i - 1];
  }

  printf("\nVetor count acumulado:\n");
  for(int i = 0; i < 10; i++)
  {
    printf("count[%d] = %d\n", i, count[i]);
  }

  waitEnter();

  for(int i = n - 1; i >= 0; i--)
  {
    int digit = (arr[i] / exp) % 10;

    output[count[digit] - 1] = arr[i];

    //printf("Colocando %d na posicao %d\n", arr[i], count[digit] - 1);

    count[digit]--;

  }

  // printf("\nVetor apos esta etapa:\n");

  // for(int i = 0; i < n; i++)
  // {
  //   arr[i] = output[i];
  //   printf("%d ", arr[i]);
  // }

  // printf("\n");

  free(output);
}

void radixSort(int *arr, int n)
{
  int max = getMax(arr, n);

  for(int exp = 1; max / exp > 0; exp *= 10)
  {
    printStep(arr, n, exp, 0);

    waitEnter();

    countingSort(arr, n, exp);

    printStep(arr, n, exp, 1);

    waitEnter();
  }
}

void printArray(int *arr, int n)
{
  for(int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }

  printf("\n");
}

int main()
{
  srand(time(NULL));

  int *arr = (int*)malloc(MAX * sizeof(int));

  for(int i = 0; i < MAX; i++)
  {
    arr[i] = rand() % 1000;
  }

  printf("Vetor original:\n");
  printArray(arr, MAX);

  waitEnter();

  radixSort(arr, MAX);

  printf("\n========================================\n");
  printf("VETOR FINAL ORDENADO:\n");
  printArray(arr, MAX);
  printf("========================================\n");

  free(arr);

  return 0;
}