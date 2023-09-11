#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct banco {// Registro(struct) para armazenar os dados dos clientes do banco.
    char nome[50];
    int num;
    float saldo;
} banco;

void cadastro(banco contas[], int maxContas, int *numContas, FILE *arquivo) {/*Funcao para cadastrar novos clientes, usando como parametro, tendo como parametros o array de structs 
"contas[]",a quantidade maxima de contas, o ponteiro do numero de contas e o buffer do arquivo que vai armazenar as informacoes*/
    banco novaConta; //struct vazio para armazenar novas contas

    printf("\nDigite o numero da conta(max 5 numeros): ");
    scanf("%d", &novaConta.num);//Atribuicao do numero da nova conta.
    getchar();

    for (int i = 0; i < *numContas; i++) {//laco for para percorrer todas as contas existentes, verificando o numero das contas ja existentes, impossibilitando duas contas com mesmo numero
        if (novaConta.num == contas[i].num) {//condicao para verificacao do numero da nova conta com o numero das conta ja existentes
            printf("\n   Conta ja existente!\n");
            return;
        }
    }

    printf("\nDigite o nome do titular: ");
    fgets(novaConta.nome, 49, stdin);//Atribuicao do nome do novo cliente

    printf("\nDigite o saldo da conta: ");
    scanf("%f", &novaConta.saldo);// Atribuicao do saldo do novo cliente

    fwrite(&novaConta, sizeof(banco), 1, arquivo);//Escrita dos dados da nova conta no arquivo
    printf("\nArquivo salvo.\n");

    contas[*numContas] = novaConta;//Define que a conta na posicao que esta sendo apontada e igual a nova conta cadastrada
    (*numContas)++;//passa para a proxima posicao no array
    printf("\nConta registrada com sucesso!");
}

void visualizarContas(banco contas[], int numContas) {//Funcao para visualizar contas
    printf("\n|------------------------|");
    printf("\n|   Contas Registradas:  |");
    printf("\n|------------------------|\n");

    for (int i = 0; i < numContas; i++) {//laco for para percorrer todas contas existentes, e mostrar os dados de cada uma
        printf("Conta %d:\n", i + 1);
        printf("Nome do Titular: %s", contas[i].nome);
        printf("Numero da Conta: %d\n", contas[i].num);
        printf("Saldo: %.2f\n", contas[i].saldo);
        printf("------------------------\n");
    }
    system("pause");
}

void selectionSort(int numContas, FILE *arquivo)//Funcao para ordenacao por meio de selecao
{
    banco contas[numContas];   
    banco temp;//struct temporario para organizacao do arquivo
    int comps = 0;//variavel tipo inteiro para mostrar as comparacoes feitas
    int trocas = 0;//variavel tipo inteiro para mostrar as trocas feitas
    int  min, i, j;//variaveis inteiras de indices.

    fread(contas, sizeof(banco), numContas, arquivo);//Funcao de leitura do arquivo

    clock_t tempInicial = clock();//variavel que recebe o valor de qual giro do clock a ordenacao iniciou. 
    for (i = 0; i < numContas; i++)//laco for para percorrer todas contas existentes
    {
        min = i;// atribui o valor de i na variavel min.
        for (j = i + 1; j < numContas; j++)//laco for para percorrer todas contas existentes, e fazer a busca do menor elemento
        {
            comps++;// a cada passagem do for, aumenta a contagem de comparacoes feitas.
            if (contas[j].saldo < contas[min].saldo)//condicao if para comparar o menor saldo das contas existentes
            {
                min = j;// se houver alguma conta com menor saldo, a conta na posicao j vai ser atribuida como a conta no indice minimo
            }
        }
        if (min != i)//condicao if para verificar se o indice min é diferente do indice i
        {
            //Essa operacao realiza a troca do menor elemento com a primeira posicao do vetor, do segundo menor com a segunda posicao e assim por diante
            temp = contas[i];
            contas[i] = contas[min];//troca do valor do array na posicao i com o valor do array na posicao min
            contas[min] = temp;
            trocas++;//aumenta a contagem da variavel trocas, para mostrar quantas trocas foram feitas.
        }
    }

    clock_t tempFinal = clock();//variavel que recebe o valor de qual giro do clock a ordenacao terminou. 
    
    double tempoGasto = ((double)(tempFinal - tempInicial)) / CLOCKS_PER_SEC;//contagem de giros do clock durante a ordenacao, e calculo para demonstrar o tempo gasto em segundos.

    printf("\nContas ordenadas por saldo:\n");
    for (int i = 0; i < numContas; i++) {//laco for para percorrer todas contas existentes, e mostrar os dados de cada uma apos a ordenacao.
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

void insertionSort(int numContas, FILE *arquivo)//funcao para ordenacao por meio de insercao
{
    banco contas[numContas];//struct das contas
    banco temp;//struct temporario 
    int comps = 0; //variavel tipo inteiro para mostrar as comparacoes feitas
    int trocas = 0;//variavel tipo inteiro para mostrar as trocas feitas
    int  min, i, j;//variaveis inteiras de indices.

    fread(contas, sizeof(banco), numContas, arquivo);//Funcao de leitura do arquivo

    clock_t tempInicial = clock();//variavel que recebe o valor de qual giro do clock a ordenacao iniciou. 
    for (i = 1; i < numContas; i++) {//laco for para percorrer todas contas existentes, e fazer a ordenacao das contas
        temp = contas[i];//atribuicao da conta no vetor i([1]) no vetor temporario.
        j = i - 1;//indice j recebe o valor do indice i - 1, ou seja [0]
        comps ++;// a cada passagem do for, aumenta a contagem de comparacoes feitas.

        while (j >= 0 && contas[j].saldo > temp.saldo) {//laco while para realizar a ordenacao
            //Essa operacao, ao ter temp na posicao [i], faz a passagem com o indice j para comparar se a conta na posicao j é maior que temp[i]
            contas[j + 1] = contas[j];// se a conta na posicao [j] for maior que a conta na posicao temp[i], entao a conta na posicao [j], passa para a posicao [j+1]            
            j = j - 1;
            trocas ++;// a cada passagem do while, aumenta a contagem de trocas feitas.
            comps ++;// a cada passagem do while, aumenta a contagem de comparacoes feitas.
        }
        contas[j + 1] = temp;//E a conta que passou de posicao é a proxima a ser comparada
    }

    clock_t tempFinal = clock();//variavel que recebe o valor de qual giro do clock a ordenacao terminou. 
    
    double tempoGasto = ((double)(tempFinal - tempInicial)) / CLOCKS_PER_SEC;//contagem de giros do clock durante a ordenacao, e calculo para demonstrar o tempo gasto em segundos.

    printf("\nContas ordenadas por saldo:\n");
    for (int i = 0; i < numContas; i++) {//laco for para percorrer todas contas existentes, e mostrar os dados de cada uma apos a ordenacao.
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

int main() {//funcao main/principal
    int maxContas;//variavel inteira de maximo de contas
    int numContas = 0;//variavel inteira de numero de contas, tendo o valor 0 atribuido 
    int opcao;//variavel inteira de opcao
    FILE *dadosBanco;//buffer de arquivo
    FILE *abrirArqv;//buffer de arquivo
    dadosBanco = fopen("DadosBancarios.txt", "w");//criacao/abertura do arquivo no formato de escrita
    if (dadosBanco == NULL)//condicao if para verificar se, no caso de nao criar/abrir o arquivo, gerar erro
    {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    printf("\n|-----------------------------|");
    printf("\n|     BEM VINDO AO BANCO!     |");
    printf("\n|-----------------------------|\n");
    printf("\nDigite o maximo de contas que serao cadastradas: ");
    scanf("%d", &maxContas);//definicao do maximo de contas pelo usuario
    banco *contas = (banco *)malloc(maxContas * sizeof(banco));//alocacao de memoria

    if (contas == NULL) {//condicao if para verificar se houve erro na alocacao de memoria
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    do {//laco do while sendo iniciado
        printf("\n|------------------------------------|");
        printf("\n|  1- Cadastrar nova conta           |");
        printf("\n|  2- Visualizar contas              |");
        printf("\n|  3- Ordenar por saldo (selecao)    |");
        printf("\n|  4- Ordenar por saldo (Insercao)   |");
        printf("\n|  5- Sair do programa               |");
        printf("\n|------------------------------------|\n");
        printf("\nInsira o numero correspondente a uma das opcoes acima: ");
        scanf("%d", &opcao);//escolha de qual opcao/funcao pelo usuario

        switch (opcao) {
            case 1:               
                if (numContas >= maxContas )//condicao if para verificar se o maximo de contas ja foi atingido
                {
                    printf("\n   Maximo de contas atingidas!");                    
                }else
                {
                    cadastro(contas, maxContas, &numContas, dadosBanco);//chamada da funcao cadastro
                }
                break;

            case 2:
                if (numContas <= 0) {//condicao if para verificar se ha conta(s) registrada(s)
                    printf("\n  Nenhuma conta registrada.\n");
                } else 
                {
                    visualizarContas(contas, numContas); //chamada da funcao visualizar contas
                }
                break;

            case 3:
                if (numContas <= 0) {//condicao if para verificar se ha conta(s) registrada(s)
                    printf("\n  Nenhuma conta registrada.\n");
                } else
                {
                    fclose(dadosBanco);//fechamento do arquivo no formato de escrita
                    abrirArqv = fopen("DadosBancarios.txt", "r");//abertura do arquivo no formato de leitura
                    selectionSort(numContas, abrirArqv);//chamada da funcao de ordenamento selection sort
                    fclose(abrirArqv);//fechamento do arquivo no formato de leitura
                }
                break;

            case 4:
                if (numContas <= 0) {//condicao if para verificar se ha conta(s) registrada(s)
                    printf("\n  Nenhuma conta registrada.\n");
                } else
                {
                    fclose(dadosBanco);//fechamento do arquivo no formato de escrita
                    abrirArqv = fopen("DadosBancarios.txt", "r");//abertura do arquivo no formato de leitura
                    insertionSort(numContas, abrirArqv);//chamada da funcao de ordenamento insertion sort
                    fclose(abrirArqv);//fechamento do arquivo no formato de leitura
                }
                break;

            case 5://Opcao de sair do programa                
                printf("\n   Programa encerrado.");
                opcao = 5;
                break;

            default:
                printf("\n|-----------------------------|");
                printf("\n|       OPCAO INVALIDA!       |");
                printf("\n|-----------------------------|");
                break;
        }
    } while (opcao != 5);//laco do while sendo encerrado com saida sendo a opcao 5.

    free(contas);//liberacao de memoria alocada dinamicamente

    return 0;//return 0 para encerrar o programa
}
