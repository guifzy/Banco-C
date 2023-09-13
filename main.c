#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct banco {
    char nome[50];
    int num;
    float saldo;
} banco;

//função para cadastro
void cadastro(banco contas[], int *numContas, FILE *arquivo) {
    banco novaConta;// nova struct para armazenar os cadastros

    printf("\nDigite o numero da conta(max 5 numeros): ");
    scanf("%d", &novaConta.num);
    getchar();

//verifica se existe alguma conta no array de structs com o número igual ao do struct de cadastro
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

    //envia os dados do struct 'novaConta' para o buffer
    fwrite(&novaConta, sizeof(banco), 1, arquivo);
    printf("\nArquivo salvo.\n");

    //array de structs 'contas' recebe os valores do struct 'nova conta' no índice do apontado de 
    //numContas(também se chama numContas na função main).
    contas[*numContas] = novaConta;
    //a cada conta registrada numContas é incrementada
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
    system("pause");
}

void selectionSort(int numContas, FILE *arquivo)
{
    //novo array de structs com o tamanho relativo a quantidade de contas gravadas no arquivo
    banco contas[numContas];  

    //variavel para realizar a troca de valores
    banco temp;
    int comps = 0; 
    int trocas = 0;
    int  min, i, j;

    //lê os dados gravados no arquivo e envia os valores do buffer para o array de structs
    fread(contas, sizeof(banco), numContas, arquivo);

    clock_t tempInicial = clock();
    //algoritimo de seleção
    for (i = 0; i < numContas; i++)
    {
        //min recebe os valores de 0 até o último índice da lista
        min = i;

        //'j' recebe o valor seguinte de 'i'
        for (j = i + 1; j < numContas; j++)
        {
            comps++;
            //caso o valor seguinte da lista seja menor que o valor anterior
            if (contas[j].saldo < contas[min].saldo)
            {
                //mim passa a valer o menor valor entre o índice 'i' e 'j'
                min = j;
            }
        }
        //caso mim não seja mais o valor de 'i' a troca é realizada
        if (min != i)
        {
            temp = contas[i];
            contas[i] = contas[min];
            contas[min] = temp;
            trocas++;
        }
    }

    clock_t tempFinal = clock();
    
    double tempoGasto = ((double)(tempFinal - tempInicial)) / CLOCKS_PER_SEC;

    printf("\nContas ordenadas por saldo:\n");
    for (int i = 0; i < numContas; i++) {
        printf("Conta %d:\n", i + 1);
        printf("Nome do Titular: %s", contas[i].nome);
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

void insertionSort(int numContas, FILE *arquivo)
{
    //novo array de structs com o tamanho relativo a quantidade de contas gravadas no arquivo
    banco contas[numContas];

    //variavel para realizar a troca de valores   
    banco temp;
    int comps = 0; 
    int trocas = 0;
    int  min, i, j;

    //lê os dados gravados no arquivo e envia os valores do buffer para o array de structs
    fread(contas, sizeof(banco), numContas, arquivo);

    clock_t tempInicial = clock();
    //algoritimo de inserção
    for (i = 1; i < numContas; i++) {
        //recebe o valores do índice 1 até o último índice
        temp = contas[i];

        //recebe o índice anterior ao 'i'
        j = i - 1;
        comps ++;

        //enquanto 'j' for maior ou igual ao índice 0
        //e o saldo do índice anterior for maior que o do índice seguinte
        while (j >= 0 && contas[j].saldo > temp.saldo) {
            //troca o valor do índice seguinte o com o do índice anterior    
            contas[j + 1] = contas[j];

            //'j' é decrementado em 1 até que seu valor seja igual a -1            
            j = j - 1;
            trocas ++;
            comps ++;
        }
        //valor atual de 'j' + 1 recebe o valor de temp
        //obs:caso a condição do while seja não seja, repare que o valor de j + 1 é igual ao valor de temp
        contas[j + 1] = temp;
    }//fim da ordenação

    clock_t tempFinal = clock();
    
    double tempoGasto = ((double)(tempFinal - tempInicial)) / CLOCKS_PER_SEC;

    printf("\nContas ordenadas por saldo:\n");
    for (int i = 0; i < numContas; i++) {
        printf("Conta %d:\n", i + 1);
        printf("Nome do Titular: %s", contas[i].nome);
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
    banco contas[100];//array de structs príncipal
    int numContas = 0;
    int opcao;
    FILE *dadosBanco;
    FILE *abrirArqv;
    //cria um novo arquivo caso ele não exista e começa sua escrita do zero
    dadosBanco = fopen("DadosBancarios.txt", "w");
    if (dadosBanco == NULL)
    {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    printf("\n|-----------------------------|");
    printf("\n|     BEM VINDO AO BANCO!     |");
    printf("\n|-----------------------------|\n");
    
    do {
        printf("\n|------------------------------------|");
        printf("\n|  1- Cadastrar nova conta           |");
        printf("\n|  2- Visualizar contas              |");
        printf("\n|  3- Ordenar por saldo (selecao)    |");
        printf("\n|  4- Ordenar por saldo (Insercao)   |");
        printf("\n|  5- Sair do programa               |");
        printf("\n|------------------------------------|\n");
        printf("\nInsira o numero correspondente a uma das opcoes acima: ");
        scanf("%d", &opcao);

        switch (opcao) {
            //cadastro
            case 1:  
                //caso tenham sido registradas 100 contas            
                if (numContas >= 100 )
                {
                    printf("\n   Maximo de contas atingidas!");                    
                }else
                {
                    cadastro(contas, &numContas, dadosBanco);
                }
                break;

            //visualizar as contas registradas
            case 2:
                if (numContas <= 0) {
                    printf("\n  Nenhuma conta registrada.\n");
                } else 
                {
                    visualizarContas(contas, numContas);
                }
                break;

            //ordenação por seleção
            case 3:
                //caso não tenha nenhuma conta registrada
                if (numContas <= 0) {
                    printf("\n  Nenhuma conta registrada.\n");
                } else
                {
                    //manda as informações do buffer para o arquivo de escrita
                    fclose(dadosBanco);

                    //abre o arquivo gravado anteriormente, agora como leitura
                    abrirArqv = fopen("DadosBancarios.txt", "r");

                    //chama a função de seleção
                    selectionSort(numContas, abrirArqv);

                    //encerra o buffer e fecha o arquivo
                    fclose(abrirArqv);
                }
                break;

            //ordenação por inserção
            case 4:
                if (numContas <= 0) {
                    printf("\n  Nenhuma conta registrada.\n");
                } else
                {
                    //manda as informações do buffer para o arquivo de escrita
                    fclose(dadosBanco);

                    //abre o arquivo gravado anteriormente, agora como leitura
                    abrirArqv = fopen("DadosBancarios.txt", "r");

                    //chama a função de inserção
                    insertionSort(numContas, abrirArqv);

                    //encerra o buffer e fecha o arquivo
                    fclose(abrirArqv);
                }
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

    return 0;
}
