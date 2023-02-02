#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "locale.h"
#include "Dicts/destatico.h"
#include "preProcessamento.h"
#include "ctype.h"
#include "wchar.h"
#include "wctype.h"

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
  while (fscanf(fdStopWords, "%[^\n]%*c",  (char*) palavra) == 1){ 
    TStopWord *p = criar_sw(palavra);
    carga_DE(dic, p);
    palavra = malloc(sizeof(TStopWord)*47);
  }

  fclose(fdStopWords);

  return dic;
}

void tirarPontuacaoNumero(char palavra[]){
  char palavraResult[47];
  const char pontuacao[7][2] = {",",".",";","!",":","?",")"};
  const char numbers[10][2] = {"0","1","2","3","4","5","6","7","8","9"};
  char* token;

  if (strlen(palavra) <= 2){
    if(strcmp(palavra,"PA")!=0){
      strcpy(palavra,"");
      return;
    }
  }
  
  if (strcmp(palavra,"”") == 0){
    strcpy(palavra,"");
    return;
  }

  if (strcmp(palavra,"—") == 0){
    strcpy(palavra,"");
    return;
  }

  char stringAux[strlen(palavra)];
  if (palavra[0] == '(' || palavra[0] == '[' || palavra[0] == '=' || palavra[0] == '-'){
    for(int i = 1; i <= strlen(palavra); i++){
        stringAux[i-1] = palavra[i];
    }
    strcpy(palavra,stringAux);
    return;
  }

  
  if (palavra[0]=='.'){
    strcpy(palavra,"");
    return;
  }

  if ((strncmp(palavra,"“",3) == 0) || (strncmp(palavra,"‘",3) == 0) ){
    for (int i = 0; palavra[i]; i++){
      palavraResult[i] = palavra[3+i];
    }
    strcpy(palavra,palavraResult);
  }
  if ((strpbrk(palavra,"”")) && (strcspn(palavra,"”") > 2)){
    palavra = strtok(palavra, "”");
  }

  char *num;

  for (int i = 0; i<10; i++){
      num = strpbrk(palavra, numbers[i]);
      if (num){
        palavra = strtok(palavra, pontuacao[i]);
        strcpy(palavra,"");
        return;
      }
  }

  char *ret;
  for (int i = 0; i<7; i++){
    ret = strpbrk(palavra, pontuacao[i]);
    if (ret){
      palavra = strtok(palavra, pontuacao[i]);
      return;
    }
  }
}

void lowerString(char palavra[]){
  for(int i = 0; i < strlen(palavra); i++){
    palavra[i] = towlower(palavra[i]);
  }
  return;
}

void ProcessarLivro(char nomeArquivo[], TDEstatico* stopWords){

  FILE *fdLivroP;
  FILE *fdLivro;
  char frase[3000];
  char* p = NULL;
  int pag = 0;

  setlocale(LC_ALL,"pt_BR");
  fdLivro = fopen(nomeArquivo,"r+");
  if (fdLivro == NULL){
    printf("Erro ao Abrir o Arquivo\n");
    exit(1);
  } 

  fdLivroP = fopen("Auxiliares/livroPreProcessado.txt","w");
  if (fdLivroP == NULL){
    printf("Erro ao Criar o Arquivo\n");
    exit(1);
  } 
  
  while (fgets(frase, sizeof(frase),fdLivro) != NULL){ 

    p = strtok(frase," ");

    while(p != NULL){
      if(p[0] != '[' && p[0] != '('){
        p[strcspn(p, "”)]!:,.'|[(+\"")] = 0;
      }else{
        p[strcspn(p, "”)]!:,.'|+\"")] = 0;
      }
      
      if(strcmp(p," ") != 0 && strcmp(p,"\t") != 0){

        tirarPontuacaoNumero(p);
        lowerString(p);
        if (buscar_DE(stopWords,p) == NULL){
          if ((strcmp(p,"") != 0) && (strcmp(p," ") != 0) && (strcmp(p,"\t") != 0) && (strcmp(p,"\n") != 0) && (strcmp(p,"\b") != 0)){
            fprintf(fdLivroP," %s",p);
          }
        }
      }

      p = strtok(NULL," ");
    }
    
  }
  fclose(fdLivro);
  fclose(fdLivroP);
}