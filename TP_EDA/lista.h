#pragma once
#ifndef LISTA_H
#define LISTA_H

typedef struct _lista {
	int valor;
	struct _lista* next;
}lista;

lista* cria_lista();
void inserir_final(lista** estrutura, int inteiro);
void inserirNovaLinha(lista** estrutura, int colunas);
lista* removerLinha(lista* estrutura, int linhaParaRemover);
void eliminar(lista** original, int inteiro);
void listar(lista* estrutura);
lista* ler_matriz(const char* nomeArquivo, int* linhas, int* colunas);
void contar_linhas_colunas(int* linhas, int* colunas);
void printMatriz();
void escreverMatrizNoArquivo(lista* estrutura, const char* nomeArquivo);
void removerColuna(lista** estrutura, int linhas, int colunas, int indiceColunaRemover);
void adicionarColuna(lista** estrutura, int linhas, int colunas, int valorColunaNova);
#endif // LISTA_H

