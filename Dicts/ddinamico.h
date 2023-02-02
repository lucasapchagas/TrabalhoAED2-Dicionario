typedef struct ddinamico TDDinamico;

TDDinamico* criar_DD(int fator_carga, int tamanho);

void inserir_DD(TDDinamico *dd, int chave, void* info);
void* buscar_DD(TDDinamico *dd, int chave);
void* remover_DD(TDDinamico *dd, int chave);


int qtdElementos(TDDinamico* dd);
void* buscarIndexDD(TDDinamico* dd, int index);
int tamanhoDD(TDDinamico* dd);
int colisoes(TDDinamico *dicionario);
TDDinamico* re_hashingDD(TDDinamico *atual);
TDDinamico* faz_rehashing(TDDinamico *dd);
void destruirDD(TDDinamico *dd);