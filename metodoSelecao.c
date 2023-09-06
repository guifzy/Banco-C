#include <stdio.h>

int main()
{

    int array[] = {1, 3, 6, 4, 2, 5};
    int n = sizeof(array) / sizeof(array[0]);
    int comps = 0; 
    int trocas = 0;
    int i, temp, j, min;

    printf("\nArray desordenado: ");
    for ( i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    for ( i = 0; i < n - 1; i++)
    {
        min = i;
        for ( j = i + 1; j < n; j++)
        {
            if ( array[j] < array[min])
            {
                min = j;
            }
            
        }
        if (min != i)
        {
            temp = array[i];
            array[i] = array[min];
            array[min] = temp;

        }
        
    }

    printf("\nArray ordenado: ");
    for ( i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }


    return 0;
}