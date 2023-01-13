#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "destatico.h"
#include "locale.h"
#include "usaDE.h"

typedef char TStopWord;

TStopWord* criar_sw(char palavra[]){
    TStopWord* sw = malloc(sizeof(char)*47); // maior palavra da língua portuguesa = 47 letras.
    strcpy(sw, palavra);

    return sw;
}

void imprimir_sw(void *p){
    TStopWord *pp = p;
    printf("Palavra: %s\n", pp);
}

int comparar_sw(void* sw1, void* sw2){
    TStopWord *ssw1 = sw1;
    TStopWord *ssw2 = sw2;

    return strcmp(ssw1, ssw2);
}

int tamanho_arquivo(char nomeArquivo[]){

  FILE *fdStopWords;
  TStopWord palavra[47];
  int tam = 0;
  fdStopWords = fopen(nomeArquivo,"r");

  while (fscanf(fdStopWords, "%[^\n]%*c",palavra) == 1){
    tam++;
  }
  fclose(fdStopWords);
  return tam;
}

TDEstatico* carregarStopWords(char nomeArquivo[]){

  TDEstatico* dic = criar_DE(tamanho_arquivo(nomeArquivo), imprimir_sw, comparar_sw);
  FILE *fdStopWords;
  void* palavra = malloc(sizeof(TStopWord)*47);
  setlocale(LC_ALL,"");
  fdStopWords = fopen(nomeArquivo,"r");
  if (fdStopWords == NULL){
    printf("Erro ao Abrir o Arquivo\n");
    exit(1);
  } 
  while (fscanf(fdStopWords, "%[^\n]%*c",  palavra) == 1){ 
    TStopWord *p = criar_sw(palavra);
    //printf("%s\n", p);
    carga_DE(dic, p);
    palavra = malloc(sizeof(TStopWord)*47);
  }

  fclose(fdStopWords);


  return dic;
}

int main(){
    TDEstatico *stopwords = carregarStopWords("stopwords_br.txt");
    //imprime_DE(stopwords);
    char palavra[47];
    scanf("%[^\n]%*c", palavra);
    while(strcmp(palavra, "FIM") != 0){
        if (buscar_DE(stopwords, palavra) == NULL){
          printf("Nao stopword!\n");
        }
        else{
          printf("Sim stopword!\n");
        }
        scanf("%[^\n]%*c", palavra);

    }
}