typedef struct entrada TEntradaDic;
typedef struct destatico TDEstatico;
typedef struct estatistica TEstatistica;

typedef void (*TImprimirDE)(void*);
typedef int (*TCompararDE)(void*, void*);

TEntradaDic criar_entrada(int chave, void* info);

TDEstatico* criar_DE(int tam, TImprimirDE imprimir, TCompararDE comparar); 
void carga_DE(TDEstatico* de, void* info);
void imprime_DE(TDEstatico *de);
void* buscar_DE(TDEstatico* de, void* chave);
int ocupacao_DE(TDEstatico* de);
void dashboard_DE(TDEstatico *de);