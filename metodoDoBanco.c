#include <stdio.h>

int main()
{
    int comps = 0; 
    int trocas = 0;
    int arr[] = {1, 4, 2, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i, temp, j;

    printf("\nArray desordenado: ");
    for ( i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    
    for (i = 1; i < n; i++) {
        temp = arr[i];
        j = i - 1;
        comps ++;

        while (j >= 0 && arr[j] > temp) {     
            arr[j + 1] = arr[j];            
            j = j - 1;
            trocas ++;
            comps ++;
        }
        arr[j + 1] = temp;
    }

    printf("\nArray ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nNumero de comparacoes: %d \nNumero de trocas: %d", comps, trocas );

    return 0;
}