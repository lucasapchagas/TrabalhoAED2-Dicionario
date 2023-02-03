#include "Dicts/ddinamico.h"
#include "Lista/lista.h"

typedef struct palavra TPalavra;
typedef struct pagina TPagina;
typedef struct dados TDados;
typedef struct contador TContadorP;
typedef struct nota TNota;

typedef int (* TComparar)(void*, void*);

TPalavra* criarPalavra(char* palavra, int chave);
TPagina* criarPag(int pag);
TDados* criarDados(TComparar comparar);

int gerarChave(char* palavra);
void leituraPalavras(TDDinamico* palavras, FILE* arquivo, TDados* dados);
void imprimirPagina(TPagina* pag);
void infoPalavra(TListaSE* lista);
int compararPalavra(void *palavra1, void *palavra2);
void gerarIndiceRemissivo(TDados* dados, TDDinamico* palavras);