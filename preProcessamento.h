#include "Dicts/destatico.h"

typedef char TStopWord;

//Funções para as StopWords
TStopWord* criar_sw(char palavra[]);
void imprimir_sw(void *p);
int comparar_sw(void* sw1, void* sw2);
int tamanho_arquivo(char nomeArquivo[]);
TDEstatico* carregarStopWords(char nomeArquivo[]);

//Funções para o pré-processamento em si do livro
void tirarPontuacaoNumero(char palavra[]);
void lowerString(char palavra[]);
void ProcessarLivro(char nomeArquivo[], TDEstatico* stopWords);