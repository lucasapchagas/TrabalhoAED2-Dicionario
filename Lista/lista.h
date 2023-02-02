typedef struct lista TListaSE;

typedef void (*TImprimirLSE) (void*);
typedef int (*TCompararLSE) (void*,void*);
TListaSE* criarLSE(TImprimirLSE imprimir,TCompararLSE comparar);

// Operações baseadas em posição

void inserirInicioLSE(TListaSE* lse, void* carga);
void inserirFinalLSE(TListaSE* lse, void* carga);
void* acessarLSE(TListaSE *l, int pos);
void* removerInicioLSE(TListaSE *l);
void* removerPosicaoLSE(TListaSE *l, int pos);
void* removerFinalLSE(TListaSE *l);

// Operações baseadas em conteúdo

void imprimirLSE(TListaSE *l);
void* buscarConteudoLSE(TListaSE* l, void *chaveBusca);
void* removerConteudoLSE(TListaSE* l, void *chaveBusca);
void inserirConteudoLSE(TListaSE *l, void* carga);
void destruirLSE(TListaSE* *rl);
int tamanhoLSE(TListaSE *l);