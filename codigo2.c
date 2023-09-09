#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct banco {
    char nome[50];
    int num;
    float saldo;
} banco;

void selectionSort(banco contas[], int numContas)
{
    banco temp;
    int comps = 0; 
    int trocas = 0;
    int  min, i, j;

    clock_t tempInicial = clock();
    for (i = 0; i < numContas; i++)
    {
        min = i;
        for (j = i + 1; j < numContas; j++)
        {
            comps++;
            if (contas[j].saldo < contas[min].saldo)
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = contas[i];
            contas[i] = contas[min];
            contas[min] = temp;
            trocas ++;
        }
    }
    clock_t tempFinal = clock();
    
    double tempoGasto = ((double)(tempFinal - tempInicial)) / CLOCKS_PER_SEC;

    printf("\nContas ordenadas por saldo:\n");
    for (int i = 0; i < numContas; i++) {
        printf("Conta %d:\n", i + 1);
        printf("Nome do Titular: %s\n", contas[i].nome);
        printf("Numero da Conta: %d\n", contas[i].num);
        printf("Saldo: %.2f\n", contas[i].saldo);
        printf("\n----------------------------\n");
    }
    printf("\nNumero de comparacoes: %d", comps);
    printf("\nNumero de trocas: %d", trocas);
    printf("\nOrdenacao feita em %f segundos", tempoGasto);
    printf("\n----------------------------\n");
    system("pause");
}

void insertionSort(banco contas[], int numContas)
{   
    banco temp;
    int comps = 0; 
    int trocas = 0;
    int  min, i, j;

    clock_t tempInicial = clock();
    for (i = 1; i < numContas; i++) {
        temp = contas[i];
        j = i - 1;
        comps ++;

        while (j >= 0 && contas[j].saldo > temp.saldo) {     
            contas[j + 1] = contas[j];            
            j = j - 1;
            trocas ++;
            comps ++;
        }
        contas[j + 1] = temp;
    }
    clock_t tempFinal = clock();
    
    double tempoGasto = ((double)(tempFinal - tempInicial)) / CLOCKS_PER_SEC;

    printf("\nContas ordenadas por saldo:\n");
    for (int i = 0; i < numContas; i++) {
        printf("Conta %d:\n", i + 1);
        printf("Nome do Titular: %s\n", contas[i].nome);
        printf("Numero da Conta: %d\n", contas[i].num);
        printf("Saldo: %.2f\n", contas[i].saldo);
        printf("\n----------------------------\n");
    }
    printf("\nNumero de comparacoes: %d", comps);
    printf("\nNumero de trocas: %d", trocas);
    printf("\nOrdenacao feita em %f segundos", tempoGasto);
    printf("\n----------------------------\n");
    system("pause");

}

int main() {   
    banco contas[100];
    int numContas = 0;
    int opcao;
    char nome[50];
    int num;
    float saldo;

    FILE *dadosBanco;
    FILE *abrirArqv;
    dadosBanco = fopen("DadosBancarios2.txt", "r");
    if (dadosBanco == NULL)
    {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    while (fscanf(dadosBanco, "%[^\n]\n%d\n%f\n", nome, &num, &saldo) != EOF) {
        strcpy(contas[numContas].nome, nome);
        contas[numContas].num = num;
        contas[numContas].saldo = saldo;
        numContas++;
    }
    fclose(dadosBanco);

    printf("\n|-----------------------------|");
    printf("\n|     BEM VINDO AO BANCO!     |");
    printf("\n|-----------------------------|\n");

    do {
        printf("\n|------------------------------------|");
        printf("\n|  1- Ordenar por saldo (selecao)    |");
        printf("\n|  2- Ordenar por saldo (Insercao)   |");
        printf("\n|  3- Sair do programa               |");
        printf("\n|------------------------------------|\n");
        printf("\nInsira o numero correspondente a uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (num == 0) {
                    printf("\n  Nenhuma conta registrada.\n");
                } else
                {                   
                    selectionSort(contas, numContas);
                }
                break;

            case 2:
                if (num == 0) {
                    printf("\n  Nenhuma conta registrada.\n");
                } else
                {
                    insertionSort(contas, numContas);
                }
                break;

            case 3:                
                printf("\n   Programa encerrado.");
                opcao = 3;
                break;

            default:
                printf("\n|-----------------------------|");
                printf("\n|       OPCAO INVALIDA!       |");
                printf("\n|-----------------------------|");
                break;
        }
    } while (opcao != 3);

    return 0;
}