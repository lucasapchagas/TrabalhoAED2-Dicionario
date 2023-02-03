#include "stdio.h"
#include "stdlib.h"
#include "lista.h"

typedef struct elementoLSE{
  void* cargautil;
  struct elementoLSE* proximo; // sucessor
} TElementoLSE;

struct lista{
  TElementoLSE* inicio;
  int tamanho;
  TImprimirLSE imprimir;
  TCompararLSE comparar;
};

TListaSE* criarLSE(TImprimirLSE imprimir, TCompararLSE comparar){
  TListaSE* lista = malloc(sizeof(TListaSE));

  lista->inicio = NULL;
  lista->tamanho = 0;
  lista->imprimir = imprimir;
  lista->comparar = comparar;

  return lista;
}

TElementoLSE* criarElementoLSE(void*carga){
  TElementoLSE* elem = malloc(sizeof(TElementoLSE));

  elem->cargautil = carga;
  elem->proximo=NULL;

  return elem;
}

void imprimirElementoLSE(TElementoLSE* e, TListaSE* l){

    //printf("%lf %lf %d %d\n", e->lat, e->lgi, e->data, e->hora);
    //   printf("%p", e->cargautil);
    l->imprimir(e->cargautil);
}

// Operações baseadas em posição

void inserirInicioLSE(TListaSE* lse, void* carga){
  TElementoLSE *novo = criarElementoLSE(carga);

  lse->tamanho++;
  if (lse->inicio == NULL){
    lse->inicio = novo;
  }else{
    novo->proximo = lse->inicio;
    lse->inicio = novo;
  }
}

void inserirFinalLSE(TListaSE* lse, void* carga){
  TElementoLSE *novo = criarElementoLSE(carga);

  lse->tamanho++;
  if (lse->inicio == NULL){
    lse->inicio = novo;
  }else{
    TElementoLSE *cam = lse->inicio;
    while (cam->proximo!=NULL){
      cam = cam->proximo;
    }
    cam->proximo = novo;
  }
}

void* acessarLSE(TListaSE *l, int pos){
  TElementoLSE *cam = NULL;
  void* carga = NULL;
  if( (pos>=1) && (pos<=l->tamanho) ){
    int i=1;
    cam = l->inicio;
    while(i<pos){
      i++;
      cam = cam->proximo;
    }
    carga =   cam->cargautil;
  }
  return carga;
}

void* removerInicioLSE(TListaSE *l){
  TElementoLSE* elem;
  if (l->inicio == NULL){
    return NULL;
  }else{
    elem = l->inicio;
    l->inicio = elem->proximo;
    l->tamanho--;
    void* carga = elem->cargautil;
    free(elem);
    return carga;
  }
}
// void* removerInicioLSE(TListaSE *l){
//   TElementoLSE* elem;
//   if (l->inicio == NULL){
//     elem = NULL;
//   }else{
//     elem = l->inicio;
//     l->inicio = elem->proximo;
//     l->tamanho--;
//   }
//   void*carga = elem->cargautil;
//   free(elem);
//   return carga;
// }

void* removerPosicaoLSE(TListaSE *l, int pos){
    TElementoLSE* removido=NULL;

    TElementoLSE *ant=NULL;
    if( (pos<1) || (pos>l->tamanho) ){
      printf("ERRO: Fora do escopo\n");
      return NULL;
    }
    TElementoLSE *cam=l->inicio;
    int i=1;
    while(i<pos){
      ant = cam;
      cam = cam->proximo;
      i++;
    }
    if (ant==NULL){
      removido = l->inicio;
      // atualizando a descrição da lista (o novo inicio)
      l->inicio = removido->proximo;
    }else{
      removido = cam;
      ant->proximo = removido->proximo;
    }
    // atualizando a descrição da lista (reduzir o tamanho)
    l->tamanho--;

    void*carga = removido->cargautil;
    free(removido);
    return carga;
}

void*removerFinalLSE(TListaSE *l){
  return removerPosicaoLSE(l, l->tamanho);
}

// Operações baseadas em conteúdo

void imprimirLSE(TListaSE *l){

  TElementoLSE* cam = l->inicio;
  printf("inicio da impressão\n");
  while(cam!=NULL){
    // printf("%p ", cam);
    l->imprimir(cam->cargautil);
    cam = cam->proximo;
  }
  printf("\n");
}

void* buscarConteudoLSE(TListaSE* l, void *chaveBusca){
  TElementoLSE *cam = l->inicio;

  while ((cam!=NULL) && ( l->comparar(cam->cargautil, chaveBusca) !=0 ) ){
    cam = cam->proximo;
  }
  if (cam == NULL)
    return NULL;
  else
    return cam->cargautil;
}

void*removerConteudoLSE(TListaSE* l, void *chaveBusca){
  TElementoLSE *cam = l->inicio;
  TElementoLSE *ant=NULL;
  while ((cam!=NULL) && (l->comparar(cam->cargautil, chaveBusca)!=0) ){
    ant = cam;
    cam = cam->proximo;
  }

  if (cam!=NULL){  // encontrou o elemento
    if(l->inicio == cam){ // removendo o primeiro da lista (no inicio)
      l->inicio = cam->proximo;
      l->tamanho--;
    }else{ // removendo um intermediario
      ant->proximo = cam->proximo;
      l->tamanho--;
    }
    void*carga = cam->cargautil;
    free(cam);
    return carga;
  }else{
    return NULL;
  }
}

void inserirConteudoLSE(TListaSE *l, void*carga){
  TElementoLSE* cam = l->inicio;
  TElementoLSE* ant=NULL;
  TElementoLSE *novo = criarElementoLSE(carga);

  while( (cam != NULL) && (l->comparar(cam->cargautil, carga ) >= 0) ){
    ant = cam;
    cam = cam->proximo;
  }

  if (l->inicio == cam){ //
    l->inicio = novo;
    novo->proximo = cam;
    l->tamanho++;
  } else{
    novo->proximo = cam;
    ant->proximo = novo;
    l->tamanho++;
  }

}

void destruirLSE(TListaSE* *rl){

  while((*rl)->inicio != NULL){
      void* carga = removerInicioLSE(*rl);
      //free(carga);
  }
  free(*rl);
  *rl = NULL;
}

int tamanhoLSE(TListaSE *l){
  return l->tamanho;
}