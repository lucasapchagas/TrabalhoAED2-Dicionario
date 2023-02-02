#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Dicts/ddinamico.h"
#include "ddPalavras.h"
#include "Lista/lista.h"

//gcc .\Dicts\ddinamico.c .\Lista\lista.c .\ddPalavras.c .\indiceRemissivo.c -o indiceRemissivo (WINDOWS)
//gcc Dicts/ddinamico.c Lista/lista.c ddPalavras.c indiceRemissivo.c -o indiceRemissivo (LINUX)

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("Auxiliares/livroPreProcessado.txt","r+");

    TDDinamico* palavras = criar_DD(5,1000);
    TDados* dados = criarDados(compararPalavra);
    leituraPalavras(palavras,fp,dados);
    
    //printf("Quantidade de colisões: %d\n",colisoes(palavras));
    printf("Quantidade de palavras no dicionario dinamico: %d\n",qtdElementos(palavras));
    
    //Para testar a busca de uma palavra no dicionario dinamico

    for(int i = 0; i < 5; i++){
        char palavra[47];
        scanf("%s",palavra);
        int chave = gerarChave(palavra);
        TListaSE* listaPags = buscar_DD(palavras,chave);

        if(listaPags!=NULL){
            printf("A palavra (%s) esta no dicionario e ela ocorre em:\n",palavra);
            infoPalavra(listaPags);
        }else{
            printf("A palavra (%s) nao existe no dicionario!\n",palavra);
        }
    }

    //Para testar a ordem alfabetica das palavras na lista:

    ordemAlfabeticaPalavras(dados, palavras);

    //printf("Quantidade de colisões: %d\n",colisoes(palavras));

    return 0;
}
