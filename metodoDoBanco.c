#include <stdio.h>

int main ()
{
    int lista [9] = {4, 5, 8, 2, 9, 1, 3, 7, 6};
    int tamanho = sizeof(lista) / sizeof(lista[0]);
    int i, j, temp;
    int comps = 0; 
    int trocas = 0;

    printf("\nLista desordenada: ");
    for ( i = 0; i < tamanho; i++)
    {
        printf("%d ", lista[i]);
    }

    for (i = 0; i < (tamanho - 1); i++)
    {
        comps ++;
        if (lista[i] > lista[i + 1])
        {
            temp = lista[i + 1];
            lista[i + 1] = lista[i];
            lista[i] = temp; 

            j = i -1;
            trocas ++;
        }
        while (j >= 0)
        {
            comps ++;
            if (temp < lista[j])
            {
                lista[j + 1] = lista [j];
                lista[j] = temp;

                trocas ++;
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

    printf("\nNumero de trocas: %d \nNumero de comparacoes: %d", trocas, comps);

    return 0;
}