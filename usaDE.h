#include "destatico.h"
typedef char TStopWord;

TStopWord* criar_sw(char palavra[]);
void imprimir_sw(void *p);
int comparar_sw(void* sw1, void* sw2);
int tamanho_arquivo(char nomeArquivo[]);
TDEstatico* carregarStopWords(char nomeArquivo[]);




