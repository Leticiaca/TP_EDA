#define CRT_SECURE_NO_WARNINGS
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>




//Criar uma lista ligada vazia
lista* cria_lista() {
    lista* novo = (lista*)malloc(sizeof(lista));
    novo->next = NULL;
    return novo;
}


//Contar o número de linhas e colunas do ficheiro
void contar_linhas_colunas(int* linhas, int* colunas) {
    FILE* ficheiro;
    char linha[1024];

    ficheiro = fopen("matriz.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o arquivo %s\n", "matriz.txt");
        *linhas = 0;
        *colunas = 0;
        return;
    }

    *linhas = 0;
    *colunas = -1; // Inicializa com -1 para contar a primeira linha
    while (fgets(linha, sizeof(linha), ficheiro)) {
        (*linhas)++;
        if (*colunas == -1) {
            // Contar colunas na primeira linha
            char* token = strtok(linha, " \n");
            while (token) {
                (*colunas)++;
                token = strtok(NULL, " \n");
            }
        }
    }

    fclose(ficheiro);
}


//Imprimir a matriz
void printMatriz()
{
    FILE* matriz = fopen("matriz.txt", "r");

    if (matriz == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    char linha[1024];
    int numLinha = 1;
    while (fgets(linha, sizeof(linha), matriz)) {
        printf("Linha %d: %s", numLinha++, linha);
    }
    fclose(matriz);
}

//Ponto1: inserir linha de inteiros na lista ligada

void inserir_final(lista** estrutura, int inteiro) {
    lista* novo = (lista*)malloc(sizeof(lista));
    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }
    novo->valor = inteiro;
    novo->next = NULL;

    if (*estrutura == NULL) {
        *estrutura = novo;
    }
    else {
        lista* atual = *estrutura;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }
    printf("Valor %d adicionado a lista.\n", inteiro);
}

void inserirNovaLinha(lista** estrutura, int colunas) {
    // Verifica se a estrutura está inicializada corretamente
    if (estrutura == NULL) {
        printf("A lista não foi inicializada corretamente.\n");
        return;
    }

    int valor;
    for (int i = 0; i < colunas; i++) {
        printf("Insira o valor para a coluna %d: ", i + 1);
        if (scanf("%d", &valor) == 1) { // Certifica-se que a leitura foi bem-sucedida
            inserir_final(estrutura, valor);
        }
        else {
            printf("Entrada inválida.\n");
            i--; // Permite reentrar o valor para a mesma coluna
        }
    }
    printf("Linha adicionada com sucesso.\n");
}


void adicionarLinha(lista** estrutura, int* valores, int colunas) {
    for (int i = 0; i < colunas; i++) {
        printf("adicionando valor %d na coluna %d.\n", valores[i], i + 1);
        inserir_final(estrutura, valores[i]);
    }
}

//Ponto2: remover linha de inteiros da lista ligada

lista* removerLinha(lista* estrutura, int linhaParaRemover) {
    lista* atual = estrutura;
    lista* anterior = NULL;

    for (int i = 1; atual != NULL && i < linhaParaRemover; i++) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL)return estrutura;

    if (anterior == NULL) {
        estrutura = atual->next;
    }
    else {
        anterior->next = atual->next;
    }
    free(atual);
    return estrutura;
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

void adicionarColuna(lista** estrutura, int linhas, int colunas, int valorColunaNova) {
    if (estrutura == NULL || *estrutura == NULL) {
        printf("A lista não foi inicializada corretamente.\n");
        return;
    }

    // Adiciona um novo nó ao final de cada linha.
    for (int i = 0; i < linhas; i++) {
        int posicaoParaInserir = i * colunas; // Ajustado para posicionar corretamente
        lista* atual = *estrutura;
        lista* anterior = NULL;

        // Percorre a lista até a posição desejada.
        for (int j = 0; j < posicaoParaInserir && atual != NULL; j++) {
            anterior = atual;
            atual = atual->next;
        }

        // Insere o novo nó.
        lista* novo = (lista*)malloc(sizeof(lista));
        if (novo == NULL) {
            printf("Erro ao alocar memoria para a nova coluna.\n");
            return;
        }
        novo->valor = valorColunaNova;
        novo->next = atual;

        if (anterior != NULL) {
            anterior->next = novo;
        }
        else {
            *estrutura = novo;
        }
    }
    colunas++; // Atualiza o número de colunas.
}

//Ponto4: remover coluna de inteiros da lista ligada
void removerColuna(lista** estrutura, int linhas, int colunas, int indiceColunaRemover) {
    if (estrutura == NULL || *estrutura == NULL) {
        printf("A lista nao foi inicializada corretamente.\n");
        return;
    }
    if (indiceColunaRemover < 0 || indiceColunaRemover >= colunas) {
        printf("indice de coluna invalido.\n");
        return;
    }

    for (int i = 0; i < linhas; i++) {
        int posicaoParaRemover = i * (colunas - 1) + indiceColunaRemover;
        lista* atual = *estrutura;
        lista* anterior = NULL;
        for (int j = 0; j < posicaoParaRemover; j++) {
            anterior = atual;
            atual = atual->next;
        }
        if (anterior != NULL) {
            anterior->next = atual->next;
        }
        else {
            *estrutura = atual->next;
        }
        free(atual);
    }
    colunas--;
}
//Ponto5: listar lista ligada

void listar(lista* estrutura) {
    while (estrutura != NULL) {
        printf("%d ", estrutura->valor);
        estrutura = estrutura->next;
    }
}

//Ponto6: realizar o cálculo da soma maior

//Ler a matriz do ficheiro e guardar os valores numa lista ligada
lista* ler_matriz(const char* nomeArquivo, int* linhas, int*colunas) {
    FILE* matriz = fopen("matriz.txt", "r");
    if (matriz == NULL) {
        printf("Erro ao abrir o arquivo %s\n", "matriz.txt");
        return NULL;
    }

    lista* estrutura = NULL;
    int valor;

    while (fscanf(matriz, "%d", &valor) == 1) {
        inserir_final(&estrutura, valor);
    }

    fclose(matriz);
    return estrutura;
}

void escreverMatrizNoArquivo(lista* estrutura, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita.
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    lista* atual = estrutura;
    while (atual != NULL) {
        // Escreva o valor no arquivo, seguido por um espaço ou uma nova linha.
        fprintf(arquivo, "%d ", atual->valor);
        // Isso verifica se há um próximo nó, e se não, insere uma quebra de linha.
        if (atual->next == NULL) {
            fprintf(arquivo, "\n");
        }
        atual = atual->next;
    }

    fprintf(arquivo, "\n");

    fclose(arquivo); // Fecha o arquivo após a escrita.
}


// Remoção de um registo dada a sua posição passada por parâmetro

int main() {
    lista* estrutura = NULL;
    int opcao, linhaParaRemover, linhas=0, colunas=0;

    contar_linhas_colunas(&linhas, &colunas);
    printMatriz();


    printf("\n\nA matriz e constituida por: %d linha(s) e %d coluna(s).\n", linhas, colunas);

    printf("\n\n*** Funcionamento de Listas de Inteiros ***\n");
    do {
        printf("Seleccione uma operacao: \n");
        printf("1 - Inserir uma linha de inteiros na lista ligada \n");
        printf("2 - Remover uma linha de inteiros da lista ligada \n");
        printf("3 - Inserir uma coluna de inteiros na lista ligada \n");
        printf("4 - Remover uma coluna de inteiros da lista ligada \n");
        printf("5 - Listar lista ligada \n");
        printf("6 - Realizar o cálculo da soma maior\n");
        printf("7 - Sair\n");

       
        printf("\nIndique o numero da operacao: ");
        if (scanf("%d", &opcao) != 1) { // Mude para scanf se não estiver usando o Microsoft C Runtime
            printf("Entrada invalida. Tente novamente\n");

                int c;
                while((c=getchar())!='\n' && c !=EOF){}
                continue;
           }
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            switch (opcao) {
                case 1:
                    printf("Para inserir uma linha na matriz tera de inserir %d valores\n", colunas);
                    printf("Introduza os valores que pretende inserir: \n");
                    contar_linhas_colunas(&linhas, &colunas);
                    estrutura = ler_matriz("matriz.txt", &linhas, &colunas);
                    

                    while (estrutura != NULL) {
                        lista* temp = estrutura->next;
                        free(estrutura);
                        estrutura = temp;
                    }
                    break;

                case 2:
                    printf("Introduza o valor da linha que pretende remover: \n");
                    scanf_s("%d", &linhaParaRemover);
                    contar_linhas_colunas(&linhas, &colunas);
                    estrutura = ler_matriz("matriz.txt", &linhas, &colunas);

                    
                    break;

                case 3:
                    for (int i = 0; i < linhas; i++) {
                        int valorColunaNova;
                        printf("Insira o valor para a nova coluna na linha %d: ", i + 1);
                        if (scanf_s("%d", &valorColunaNova) != 1) {
                            printf("Entrada invalida.\n");

                            while ((c = getchar()) != '\n' && c != EOF) {}
                            i--;
                            continue;
                        }
                        while ((c = getchar()) != '\n' && c != EOF) {}

                        adicionarColuna(&estrutura, linhas, &colunas, valorColunaNova);
                    }
                    contar_linhas_colunas(&linhas, &colunas);
                    estrutura = ler_matriz("matriz.txt", &linhas, &colunas);
                    
                    break;

                case 4: {
                    int indiceColunaRemover;
                    printf("Insira o índice da coluna que deseja remover: ");
                    scanf_s("%d", &indiceColunaRemover);
                    removerColuna(&estrutura, linhas, &colunas, indiceColunaRemover);
                    contar_linhas_colunas(&linhas, &colunas);
                    estrutura = ler_matriz("matriz.txt", &linhas, &colunas);
                    break;
                }
                case 5:
                    listar(estrutura);
                    break;

                case 6:

                    break;

                case 7:

                    default:
                    printf("Opcao Invalida\n");
                    break;
            }
        }while (opcao != 7);
        while (estrutura != NULL) {
            lista* temp = estrutura;
            estrutura = estrutura->next;
            free(temp);
        }
        return 0;
    }

