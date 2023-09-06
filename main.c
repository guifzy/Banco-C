#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct banco {
    char nome[50];
    int num;
    float saldo;
} banco;

void cadastro(banco contas[], int maxContas, int *numContas, FILE *arquivo) {
    banco novaConta;

    printf("\nDigite o numero da conta (max 5 numeros): ");
    scanf("%d", &novaConta.num);
    getchar();

    for (int i = 0; i < *numContas; i++) {
        if (novaConta.num == contas[i].num) {
            printf("\n   Conta ja existente!\n");
            return;
        }
    }

    printf("\nDigite o nome do titular: ");
    fgets(novaConta.nome, 49, stdin);

    printf("\nDigite o saldo da conta: ");
    scanf("%f", &novaConta.saldo);

    fwrite(&novaConta, sizeof(banco), 1, arquivo);
    printf("\nArquivo salvo.\n");

    contas[*numContas] = novaConta;
    (*numContas)++;
    printf("\nConta registrada com sucesso!");
}

void visualizarContas(banco contas[], int numContas) {
    printf("\n|------------------------|");
    printf("\n|   Contas Registradas:  |");
    printf("\n|------------------------|\n");

    for (int i = 0; i < numContas; i++) {
        printf("Conta %d:\n", i + 1);
        printf("Nome do Titular: %s", contas[i].nome);
        printf("Numero da Conta: %d\n", contas[i].num);
        printf("Saldo: %.2f\n", contas[i].saldo);
        printf("------------------------\n");
    }
}

void selectionSort()
{

}

void insertionSort()
{

}

int main() {   
    int maxContas;
    int numContas = 0;
    int opcao;
    FILE *dadosBanco;
    dadosBanco = fopen("DadosBancarios.txt", "w");
    if (dadosBanco == NULL)
    {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    printf("\n|-----------------------------|");
    printf("\n|     BEM VINDO AO BANCO!     |");
    printf("\n|-----------------------------|\n");
    printf("\nDigite o maximo de contas que serao cadastradas: ");
    scanf("%d", &maxContas);
    banco *contas = (banco *)malloc(maxContas * sizeof(banco));

    if (contas == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    do {
        printf("\n|------------------------------------|");
        printf("\n|  1- Cadastrar nova conta           |");
        printf("\n|  2- Visualizar contas              |");
        printf("\n|  3- Ordenar por saldo (Insercao)   |");
        printf("\n|  4- Ordenar por saldo (Selecao)    |");
        printf("\n|  5- Sair do programa               |");
        printf("\n|------------------------------------|\n");
        printf("\nInsira o numero correspondente a uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:               
                if (numContas >= maxContas )
                {
                    printf("\n   Maximo de contas atingidas!");                    
                }else
                {
                    cadastro(contas, maxContas, &numContas, dadosBanco);
                }
                break;

            case 2:
                if (numContas <= 0) {
                    printf("\n  Nenhuma conta registrada.\n");
                } else {
                    visualizarContas(contas, numContas);
                }
                break;

            case 3:
                fclose(dadosBanco);

                break;

            case 4:
                fclose(dadosBanco);

                break;

            case 5:
                
                printf("\n   Programa encerrado.");
                opcao = 5;
                break;

            default:
                printf("\n|-----------------------------|");
                printf("\n|       OPCAO INVALIDA!       |");
                printf("\n|-----------------------------|");
                break;
        }
    } while (opcao != 5);

    free(contas);

    return 0;
}
