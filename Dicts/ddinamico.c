#include "stdio.h"
#include "assert.h"
#include "stdlib.h"
#include "../Lista/lista.h"
#include "ddinamico.h"

struct ddinamico{
  // dados
  int tamanho;
  int nro_elementos;
  int fc;

  TListaSE* *entradas;
  // estatistica


  int nro_remocao;
  int nro_busca;
  int nro_insercao;
  long int nro_cmps_por_rmc;
  long int nro_cmps_por_bsc;
};

struct entrada{
  int chave;
  void* info;
};

typedef struct entrada TEntradaDD;

TEntradaDD* criar_entrada_DD(int chave, void* info){
  TEntradaDD* entrada = malloc(sizeof(TEntradaDD));

  entrada->chave = chave;
  entrada->info = info;

  return entrada;
}

static int hashing(TDDinamico* dd, int chave){
  return (chave % dd->tamanho);
}

static int primo_proximo(int num){
  short encontrou = 0;
  while(!encontrou){
    int i=2;
    while( (i<num) && ( (num%i) != 0) ){
      i++;
    }
    if (i==num){
      encontrou=1;
    }else{
      num+=1;
    }
  }
  return num;
}

int compararEntradaDD(void* e1, void* e2){
  TEntradaDD* ee1 = e1;
  TEntradaDD* ee2 = e2;

  return (ee1->chave - ee2->chave);
}

TDDinamico* criar_DD(int fator_carga, int tamanho){
    TDDinamico* dd = malloc(sizeof(TDDinamico));
    dd->fc = fator_carga;

    dd->tamanho = primo_proximo(tamanho);
    dd->nro_elementos = 0;
    dd->entradas = malloc(sizeof(TListaSE*)*dd->tamanho);

    for(int i=0;i<dd->tamanho;i++){
      dd->entradas[i] = criarLSE(NULL,compararEntradaDD);
    }
    dd->nro_busca = dd->nro_remocao = dd->nro_insercao = 0;
    dd->nro_cmps_por_bsc = dd->nro_cmps_por_rmc = 0;

    return dd;

}

void inserir_DD(TDDinamico *dd, int chave, void* info){
  int k = hashing(dd,chave);
  TListaSE* lista =  dd->entradas[k];
  inserirInicioLSE(lista, criar_entrada_DD(chave,info));

  dd->nro_elementos++;
  dd->nro_insercao++;
}

int qtdElementos(TDDinamico* dd){
  return dd->nro_elementos;
}

void* buscar_DD(TDDinamico *dd, int chave){
  int k = hashing(dd,chave);
  TListaSE* lista =  dd->entradas[k];

  TEntradaDD* entrada = buscarConteudoLSE(lista, &chave);

  dd->nro_busca++;
  dd->nro_cmps_por_bsc += tamanhoLSE(lista); //assume que toda busca a gente faz o numero máximo de comparações (tamanho da lista)

  return (entrada?entrada->info:entrada);
}

void* buscarIndexDD(TDDinamico* dd, int index){
  if(index <= dd->tamanho){
    return dd->entradas[index];
  }else{
    return NULL;
  }
}

int tamanhoDD(TDDinamico* dd){
  return dd->tamanho;
}

void* remover_DD(TDDinamico *dd, int chave){
  int k = hashing(dd,chave);
  TListaSE* lista =  dd->entradas[k];

  TEntradaDD* entrada = removerConteudoLSE(lista, &chave);
  void* info = NULL;

  if(entrada!=NULL){
    info = entrada->info;
    free(entrada);
  }

  dd->nro_remocao++;
  dd->nro_cmps_por_rmc += tamanhoLSE(lista);

  return info;
}

int colisoes(TDDinamico *dicionario){
  int c = 0;
  
  for(int i = 0; i < dicionario->tamanho;i++){
    TListaSE* l = dicionario->entradas[i];
    int tam_l = tamanhoLSE(l);
    if(tam_l > 1){
      c += 1;
    }
  }

  return c;
}

TDDinamico* re_hashingDD(TDDinamico *atual){
    TDDinamico *novo;


    int fator_carga = atual->fc;
    int tamanho = atual->tamanho + 1;
    novo = criar_DD(fator_carga, tamanho);
    
    for(int i=0;i<atual->tamanho;i++){
      TListaSE *lse = atual->entradas[i];

      TEntradaDD *e = removerInicioLSE(lse);
      while(e!=NULL){
        inserir_DD(novo, e->chave, e->info);
        free(e);
        e = removerInicioLSE(lse);
      }

    }
    destruirDD(atual);
    return novo;
}

TDDinamico* faz_rehashing(TDDinamico *dd){

  int s_x=0, n = 0;
  for(int x, i=0; i < dd->tamanho; i++){
    TListaSE* lse = dd->entradas[i];
     x = tamanhoLSE(lse);
     s_x += x*x;
     n += x;
  }
  double C = (double)s_x/(double)n - dd->fc;

  if (C > 1.0){
    return re_hashingDD(dd);
  }else{
    return dd;
  }
}

void destruirDD(TDDinamico *dd){
  for(int i=0; i<dd->tamanho;i++){
    destruirLSE(&(dd->entradas[i]));
  }
  free(dd->entradas);
  free(dd);
}