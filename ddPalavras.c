#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "Dicts/ddinamico.h"
#include "Lista/lista.h"
#include "ddPalavras.h"

struct palavra{
    char palavra[47];
    int chave;
};

struct pagina{
    int pag;
    int ocorrencias;
    double tf;
};

struct dados{
    int palavras;
    int paginas;
    TListaSE* listaPalavras;
    TListaSE* listaLinhas;
};

int n_containing(int chave, TDDinamico* dicionario) {
    return tamanhoLSE(buscar_DD(dicionario, chave));
}

// qnt_ocorrencias = quantidade de vezes que uma palavra ocorre em um documento
// qnt_palavras = quantidade total de palavras no documento
double tf(int qnt_ocorrencias, int qnt_palavras) {
  return (double)qnt_ocorrencias / (double)qnt_palavras;
}

// qnt_documentos = quantidade de documentos na coleção (qnt paginas)
// qnt_documento_ocorrem = quantidade de documentos que contêm a palavra
double idf(int qnt_paginas, int qnt_paginas_ocorrem) {
  return log((double) qnt_paginas / (double) (qnt_paginas_ocorrem + 1));
}

double tf_idf(double tf, double idf) {
  return tf * idf;
}

void calcula_tf(TDDinamico* dicionario, TDados* dados) {
    for (int i = 1; i <= tamanhoLSE(dados->listaPalavras); i++) {
        TPalavra* p = acessarLSE(dados->listaPalavras, i);
        TListaSE* listaPags = buscar_DD(dicionario, p->chave);
        int qnt_paginas = tamanhoLSE(listaPags);
        for (int j = 1; j <= qnt_paginas; j++) {
            TPagina* pag = acessarLSE(listaPags, j);
            pag->tf = tf(pag->ocorrencias, (int) acessarLSE(dados->listaLinhas, pag->pag));
        }
    }
}

double calcula_idf(TPalavra* p, TDDinamico* dicionario, TDados* dados) {
    return idf(dados->paginas, n_containing(p->chave, dicionario));
}

TPalavra* criarPalavra(char* palavra, int chave){
    TPalavra* p = malloc(sizeof(TPalavra));

    strcpy(p-> palavra, palavra);
    p->chave = chave;
    return p;
}

TPagina* criarPag(int pag){
    TPagina* pagina = malloc(sizeof(TPagina));

    pagina->pag = pag;
    pagina->ocorrencias = 1;

    return pagina;
}

TDados* criarDados(TComparar comparar){
    TDados* dados = malloc(sizeof(TDados));

    dados->listaLinhas = criarLSE(NULL, NULL);
    dados->listaPalavras = criarLSE(NULL,comparar);
    dados->palavras = 0;
    dados->paginas = 0;

    return dados;
}

int gerarChave(char* palavra){
    int chave = 0;
    int g = 31;
    int tam = strlen(palavra);

    for(int i=0; i < tam; i++){
        chave = g * chave + (int) palavra[i];
    }
    
    if(chave < 0){
        return (chave * -1) + strlen(palavra);
    }else{
        return chave + strlen(palavra);
    }
}

static int verificaPrimeiraLetra(char* p){
    if(((p[0] > 64) && (p[0] <91)) || ((p[0] > 96) && (p[0] <123))){
        return 1;
    }else{
        return 0;
    }
}

void leituraPalavras(TDDinamico* palavras, FILE* arquivo, TDados* dados){
    FILE *aux = fopen("Auxiliares/palavras_e_chaves.txt","w");
    char frase[255];
    char* palavra = NULL;
    int chave = 0;

    int palavras_linha = 0;
    while(fgets(frase, sizeof(frase),arquivo) != NULL){
        palavra = strtok(frase," ");

        while(palavra != NULL){

            palavra[strcspn(palavra, "\r\n")] = 0;

            if(strcmp(palavra,"pa") != 0 && strlen(palavra) >= 3 && verificaPrimeiraLetra(palavra) == 1){
                chave = gerarChave(palavra);
                dados->palavras++;
                palavras_linha++;

                if(buscar_DD(palavras,chave) == NULL){
                    TPalavra* p = criarPalavra(palavra,chave);
                    inserirConteudoLSE(dados->listaPalavras,p);
                    TListaSE* listaPags = criarLSE(NULL,NULL); //cria a lista que ira conter as paginas que a palavra ocorre
                    TPagina* pag = criarPag(dados->paginas); //cria a primeira pag que a palavra ocorre
                    inserirInicioLSE(listaPags,pag); //adiciona essa pagina na lista de paginas
                    inserir_DD(palavras,chave,listaPags); //faz a inserção da palavra (chave) e da lista de pags no dicionario dinamico
                    // palavras = faz_rehashing(palavras);
                }else{
                    TListaSE* listaPags = buscar_DD(palavras,chave);
                    TPagina* pag = acessarLSE(listaPags,1);

                    if(pag->pag == dados->paginas){
                        pag->ocorrencias++;
                    }else{
                        pag = criarPag(dados->paginas); //cria uma nova pag que a palavra ocorre
                        inserirInicioLSE(listaPags,pag); //adiciona a nova pagina na lista de paginas
                    }
                }
                fprintf(aux, "%s %d\n",palavra,chave); //guarda as chaves num arquivo auxiliar
            } else if(strcmp(palavra,"pa") == 0) {
                dados->paginas++;
                if (palavras_linha > 0)
                    inserirFinalLSE(dados->listaLinhas, palavras_linha);
            }
            palavra = strtok(NULL," ");
        }
    }
    inserirFinalLSE(dados->listaLinhas, palavras_linha);

    // Calcular o tf para cada pagina
    calcula_tf(palavras, dados);

    printf("Total de palavras: %d\n",dados->palavras);
    printf("Total de páginas: %d\n",dados->paginas);
}


//Imprime uma página
void imprimirPagina(TPagina* pag){
    if(pag->ocorrencias > 1){
        printf("Página %d, %d vezes\n",pag->pag,pag->ocorrencias);
    }else{
        printf("Página %d, %d vez\n",pag->pag,pag->ocorrencias);
    }
}

//Mostra todas as paginas e as ocorrencias de uma palavra
void infoPalavra(TListaSE* lista){
    int pos = tamanhoLSE(lista);
    TPagina* pag;

    while(pos > 0){
        pag = acessarLSE(lista,pos);
        imprimirPagina(pag);
        pos--;
    }
}

int compararPalavra(void *palavra1, void *palavra2){
    TPalavra *p1 = palavra1;
    TPalavra *p2 = palavra2;

    if(strcmp(p1->palavra,p2->palavra) < 0){
        if(p2->palavra[0] > p1->palavra[0]){
            return 1;
        }else if(p2->palavra[0] == p1->palavra[0]){
            return 0;
        }else{
            return -1;
        }
    }else if(strcmp(p1->palavra,p2->palavra) > 0){
        if(p1->palavra[0] > p2->palavra[0]){
            return -1;
        }else if(p1->palavra[0] == p2->palavra[0]){
            return 0;
        }
        else{
            return 1;
        }
    }else{
        return 0;
    }
}

void ordemAlfabeticaPalavras(TDados* dados, TDDinamico* dinamico){
    FILE *aux = fopen("Auxiliares/indiceRemissivo.txt","w");
    TListaSE* listaPalavras = dados->listaPalavras;
    int pos = 1;
    while(pos <= tamanhoLSE(listaPalavras)){
        TPalavra* p = acessarLSE(listaPalavras,pos);

        double idf = calcula_idf(p, dinamico, dados);
        fprintf(aux, "%s ",p->palavra);
        
        TListaSE* listaPags = buscar_DD(dinamico, p->chave);
        int qnt_paginas = tamanhoLSE(listaPags);
        for (int j = 1; j <= qnt_paginas; j++) {
            TPagina* pag = acessarLSE(listaPags, j);
            double tfidf = tf_idf(pag->tf, idf);
            fprintf(aux, "Pagina %d, %d vezes, tf-idf: %.11lf ", pag->pag, pag->ocorrencias, tfidf);
        }
        fprintf(aux, "\n");
        pos++;
    }
}