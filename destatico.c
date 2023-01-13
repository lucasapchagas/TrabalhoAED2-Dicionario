#include "stdio.h"
#include "stdlib.h"
#include "destatico.h"
#include "string.h"

struct estatistica{
  int nro_cmp;
  int nro_bsc;
};

struct destatico{
    void* *entradas;
    int tamanho;
    int ocupacao;
    TEstatistica stats;
    TImprimirDE imprimir;
    TCompararDE comparar;

};


TDEstatico* criar_DE(int tam, TImprimirDE imprimir, TCompararDE comparar){ // criar dicionário

    TDEstatico *de =  malloc(sizeof(TDEstatico));
    de->entradas = malloc(sizeof(void*)*de->tamanho);
    de->tamanho = tam;
    de->imprimir = imprimir;
    de->comparar = comparar;
    de->ocupacao = 0;
    de->stats.nro_bsc = 0;
    de->stats.nro_cmp = 0;
    
    return de;
}

void carga_DE(TDEstatico* de, void* info){ // inserir stop word no dicionário
  de->entradas[de->ocupacao] = info;
  de->ocupacao++;
    
}

void* buscar_DE(TDEstatico* de, void* chave){
  (de->stats.nro_bsc)++;

  void* entrada=NULL;
  int inicio=0;
  int fim = de->ocupacao-1;
  short encontrou = 0; // falso

  while( (!encontrou) && (inicio<=fim)){
      int meio = (inicio+fim)/2;
      int status = de->comparar(de->entradas[meio], chave);
      if (status == 0){
        (de->stats.nro_cmp)+=1;
        encontrou=1; //verdade
        entrada = de->entradas[meio];
      }
      else if(status > 0){
        (de->stats.nro_cmp) += 2;
        fim = meio-1;
      }
      else{
        (de->stats.nro_cmp) += 3;
        inicio = meio+1;
      }
  }

  return entrada;
}

int ocupacao_DE(TDEstatico* de){
  return (de->ocupacao);
}

void imprime_DE(TDEstatico *de){
  
  printf("Tamanho dicionário: %d\n", de->tamanho);
  printf("Ocupação dicionário: %d\n", de->ocupacao);
  for(int i = 0; i < de->ocupacao; i++){
    de->imprimir((de->entradas[i]));
  }
}

void dashboard_DE(TDEstatico *de){
  printf("Número de buscas: %d\n", de->stats.nro_bsc);
  printf("Número de comparações: %d\n", de->stats.nro_cmp);
  printf("Média de comparações por busca: %.2f\n", (double) (de->stats.nro_cmp/de->stats.nro_bsc));
}