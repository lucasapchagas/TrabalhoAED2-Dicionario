#include "stdio.h"
#include "stdlib.h"
#include "Dicts/destatico.h"
#include "preProcessamento.h"

//gcc .\Dicts\destatico.c .\preProcessamento.c .\processarLivro.c -o processarLivro (WINDOWS)
//gcc Dicts/destatico.c preProcessamento.c processarLivro.c -o processarLivro (LINUX)

int main(int argc, char const *argv[]){
  TDEstatico *stopwords = carregarStopWords("Auxiliares/stopwords_br.txt");
  ProcessarLivro("./Livros/Aventuras.base", stopwords); //insira o nome do livro

  return 0;
}