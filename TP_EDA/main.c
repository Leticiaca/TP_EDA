#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//Definir a estrutura da lista ligada
typedef struct _lista {
    int valor;
    struct _lista* next;
} lista;

//Criar uma lista ligada vazia
lista* cria_lista() {
    lista* novo = (lista*)malloc(sizeof(lista));
    novo->next = NULL;
    return novo;
}

//inserir no inicio da lista ligada
void inserir_inicio(lista** estrutura, int inteiro) {
    lista* novo = (lista*)malloc(sizeof(lista));
    novo->valor = inteiro;
    novo->next = *estrutura;
    *estrutura = novo;
}



//Contar o número de linhas e colunas do ficheiro
void contar_linhas_colunas(int* linhas, int* colunas) {
    FILE* ficheiro;
    int caractere;
    int num_linhas = 0;
    int num_colunas = 0;
    int valores_na_linha = 0;
    int primeira_linha = 1;
    contar_linhas_colunas(&linhas, &colunas);

    ficheiro = fopen("matriz.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o arquivo %s\n", "matriz.txt");
        return;
    }

    while ((caractere = fgetc(ficheiro)) != EOF) {
        if (caractere == ';') {
            if (primeira_linha) {
                num_colunas++;
            }
            valores_na_linha++;
        }
        if (caractere == '\n') {
            num_linhas++;
            if (primeira_linha) {
                primeira_linha = 0;
            }
            else if (valores_na_linha != num_colunas) {
                printf("Erro: numero de colunas nao e consistente em todas as linhas");
                fclose(ficheiro);
                return;
            }
            valores_na_linha = 0;
        }
    }
    if (valores_na_linha > 0) {
        num_linhas++;
    }

    *linhas = num_linhas;
    *colunas = num_colunas + 1;

    fclose(ficheiro);
}

//Imprimir a matriz
void printMatriz()
{
    FILE* matriz;
    int i;
    int Linha[100];
    char* resultado;

    matriz = fopen("matriz.txt", "r");

    if (matriz == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    i = 1;
    while (!feof(matriz))
    {
        // Lê uma linha (inclusive com o '\n')
        resultado = fgets(Linha, 100, matriz);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        if (resultado)  // Se foi possível ler
            printf("Linha %d : %s", i, Linha);
        i++;
    }
    fclose(matriz);

}

//Ponto1: inserir linha de inteiros na lista ligada

void inserir_inicio(lista** estrutura, int inteiro) {
    lista* novo = (lista*)malloc(sizeof(lista));
    novo->valor = inteiro;
    novo->next = *estrutura;
    *estrutura = novo;
}

void addLinha(int colunas, lista* estrutura)
{
    FILE* matriz;
    matriz = fopen("matriz.txt", "a");

    int numero;
    for (int i = 0; i < colunas; i++) {
        scanf("%d", &numero);
        inserir_inicio(&estrutura, numero);
        if (i == 0)
            fprintf(matriz, "\n%d;", numero);
        else if (i == colunas - 1)
            fprintf(matriz, "%d;", numero);
        else
            fprintf(matriz, "%d;", numero);
    }
    fclose(matriz);
    main();
}

//Ponto2: remover linha de inteiros da lista ligada

lista* removerRegisto(lista* inicio)
{
    int linha;
    scanf("%d", &linha);

    if (inicio == NULL) return(NULL);
    else if (linha == 1) {
        lista* aux = inicio->next;
        free(inicio);
        return(aux);
    }
    else {
        inicio->next = removerRegisto(inicio->next, linha - 1);
        return(inicio);
    }
}

void eliminar(lista** original, int inteiro) {
    lista* aux = *original;
    lista* anterior = NULL;

    while (aux != NULL && aux->valor != inteiro) {
        anterior = aux;
        aux = aux->next;
    }

    if (aux != NULL) {
        if (anterior == NULL) {
            *original = aux->next;
        }
        else {
            anterior->next = aux->next;
        }
        free(aux);
        printf("Valor removido\n");
    }
    else {
        printf("O Valor não pode ser removido pois não se encontra na lista\n");
    }
}

//Ponto3: inserir coluna de inteiros na lista ligada
void inserir_inicio(lista** estrutura, int inteiro) {
    lista* novo = (lista*)malloc(sizeof(lista));
    novo->valor = inteiro;
    novo->next = *estrutura;
    *estrutura = novo;
}

void addColuna(int linhas, lista* estrutura)
{
    FILE* matriz;
    matriz = fopen("matriz.txt", "a");

    int numero;
    for (int i = 0; i < linhas; i++) {
        scanf("%d", &numero);
        inserir_inicio(&estrutura, numero);
        if (i == 0)
            fprintf(matriz, "\n%d;", numero);
        else if (i == linhas - 1)
            fprintf(matriz, "%d;", numero);
        else
            fprintf(matriz, "%d;", numero);
    }
    fclose(matriz);
    main();
}

//Ponto4: remover coluna de inteiros da lista ligada

//Ponto5: listar lista ligada

void listar(lista* original) {
    lista* aux = original;
    if (aux == NULL) {
        printf("A lista está vazia\n");
    }
    while (aux != NULL)
    {
        printf("%d ", aux->valor); // (*aux).valor
        aux = aux->next;
    }
    printf("\n");
}

//Ponto6: realizar o cálculo da soma maior

//Ler a matriz do ficheiro e guardar os valores numa lista ligada
lista* ler_matriz() {
    FILE* matriz;
    int valor;
    lista* lista_valores = cria_lista();

    matriz = fopen("matriz.txt", "r");
    if (matriz == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return NULL;
    }

    while (fscanf(matriz, "%d;", &valor) == 1) {
        inserir_inicio(&lista_valores, valor);
    }

    fclose(matriz);
    return lista_valores;
}


// Remoção de um registo dada a sua posição passada por parâmetro

int main() {
    lista* estrutura = NULL;
    int opcao, numero, linhas, colunas;
    estrutura = cria_lista();


    printf("Matriz atual:\n\n");
    printMatriz();

    contar_linhas_colunas(&linhas, &colunas);

    printf("\n\nA matriz e constituida por: %d linha(s) e %d coluna(s).\n", linhas, colunas);

    do {
        printf("\n\n*** Funcionamento de Listas de Inteiros ***\n");
        printf("Seleccione uma operacao: \n");
        printf("1 - Inserir uma linha de inteiros na lista ligada \n");
        printf("2 - Remover uma linha de inteiros da lista ligada \n");
        printf("3 - Inserir uma coluna de inteiros na lista ligada \n");
        printf("4 - Remover uma coluna de inteiros da lista ligada \n");
        printf("5 - Listar lista ligada \n");
        printf("6 - Realizar o calculo da soma maior\n");
        printf("7 - Sair\n");

        while (1) {
            printf("\nIndique o número da operacao: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                printf("Para enserir uma linha na matriz tera de inserir %d valores\n", colunas);
                printf("Introduza os valores que pretende enserir: \n");

                addLinha(colunas, estrutura);

                break;

            case 2:
                printf("Para remover uma linha na matriz tera de inserir o numero da linha a remover \n");
                printf("Introduza o valor da linha que pretende remover: \n");

                removerRegisto(estrutura);

                break;

            case 3:
                printf("Para inserir uma coluna na matriz tera que inserir %d valores\n");
                printf("Introduza os valores que pretende inserir:\n");

                addColuna(linhas, estrutura);

                break;

            case 4:
                printf("Para remover uma coluna na matriz tera que inserir o numero da coluna a remover\n");
                printf("Introduza o valor da coluna que pretende remover:\n");

                removerRegisto(estrutura);

                break;

            case 5:

                break;

            case 6:

                break;

            case 7:

                break;

            default:
                printf("Opção Inválida\n");
                main();
                break;
            }
        }

        return 0;
    }
}

