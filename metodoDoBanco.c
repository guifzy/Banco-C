#include <stdio.h>

int main ()
{
    int lista [5] = {1, 5, 3, 2, 4};
    int tamanho = sizeof(lista) / sizeof(lista[0]);
    int i, j, temp;

    printf("\nLista desordenada: ");
    for ( i = 0; i < tamanho; i++)
    {
        printf("%d ", lista[i]);
    }

    for (i = 0; i < (tamanho - 1); i++)
    {
        if (lista[i] > lista[i + 1])
        {
            temp = lista[i + 1];
            lista[i + 1] = lista[i];
            lista[i] = temp; 

            j = i -1;
        }
        while (j >= 0)
        {
            if (temp < lista[j])
            {
                lista[j + 1] = lista [j];
                lista[j] = temp;
            } else
            {
                break;
            }
            j--;
        }
        
    }

    printf("\nLista ordenada: ");
    for ( i = 0; i < tamanho; i++)
    {
        printf("%d ", lista[i]);
    }

    return 0;
}