#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Dicts/ddinamico.h"
#include "ddPalavras.h"
#include "Lista/lista.h"
#include "preProcessamento.h"

//gcc .\Dicts\ddinamico.c .\Lista\lista.c .\ddPalavras.c .\indiceRemissivo.c -o indiceRemissivo -lm (WINDOWS)
//gcc Dicts/ddinamico.c Lista/lista.c ddPalavras.c indiceRemissivo.c preProcessamento.c Dicts/destatico.c -o indiceRemissivo -lm (LINUX)

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("Auxiliares/livroPreProcessado.txt","r+");

    TDDinamico* palavras = criar_DD(2,2);
    TDados* dados = criarDados(compararPalavra);
    leituraPalavras(palavras,fp,dados);
    gerarIndiceRemissivo(dados, palavras);
    
    //printf("Quantidade de colisões: %d\n",colisoes(palavras));
    printf("Quantidade de palavras no indice remissivo: %d\n",qtdElementos(palavras));
    
    //Para testar a busca de uma palavra no dicionario dinamico

    for(int i = 0; i < 5; i++){
        char palavra[47];
        scanf("%s",palavra);
        lowerString(palavra);
        int chave = gerarChave(palavra);
        TListaSE* listaPags = buscar_DD(palavras,chave);

        if(listaPags!=NULL){
            printf("A palavra (%s) esta no dicionario e ela ocorre em:\n",palavra);
            infoPalavra(listaPags);
        }else{
            printf("A palavra (%s) nao existe no dicionario!\n",palavra);
        }
    }

    //printf("Quantidade de colisões: %d\n",colisoes(palavras));

    return 0;
}
