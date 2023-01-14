#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vetor.h"

#define TAM 61

unsigned funcao_hash(char palavra[], unsigned add) {
    unsigned chave = 0;

    for (int i = 0; i < strlen(palavra); i++) {
        chave += palavra[i] * (i + 1);
    }

    unsigned x = (chave % TAM) + add;
    return x;
}

void inserir(Vetor* t, char palavra[]) {
    unsigned add = 0;
    unsigned id = funcao_hash(palavra, add);
    
    while (t->dados[id] != NULL) {
        id = funcao_hash(palavra, add);
        add++;
    }
    adicionar_vetor_indice(t, (char*) palavra, id);
}

int busca_simples(Vetor* t, char chave[]) {
    for (int i = 0; i < t->capacidade; i++) {
        if (t->dados[i] != NULL)
            if (strcmp(t->dados[i], chave) == 0) {
                printf("\nChave: '%s' encontrada na posição: %d\n", (char*) t->dados[i], i);
                return i;
            }
    }
    return -1;
}

int busca(Vetor* t, char chave[]) {
    unsigned add = 0;
    unsigned id = funcao_hash(chave, add);
    
    while (t->dados[id] != NULL) {
        if (strcmp(t->dados[id], chave) == 0) {
            printf("\nChave: '%s' encontrada na posição: %d\n", (char*) t->dados[id], id);
            return id;
        }
        else {
            id = funcao_hash(chave, add);
            add++;
        }
    }
    return -1;
}

void imprimir_tabela(Vetor* tabela) {
    for (int i = 0; i < tabela->capacidade; i++) {
        if (tabela->dados[i] != NULL)
            printf("[%d] = %s\n", i, (char*) tabela->dados[i]);
        else
            printf("[%d] = [NULL]\n", i);
    }
}


int main() {
    int opcao, valor;
    char* hello = "hello";
    char* world = "world";
    char* lucas = "Lucas";
    char* dormir = "zzzzzzzzzzzz";
    char* rebimboca = "rebimboca";

    Vetor* tabela = inicializar_vetor(TAM); 

    inserir(tabela, hello);
    inserir(tabela, world);
    inserir(tabela, lucas);
    inserir(tabela, dormir);
    inserir(tabela, rebimboca);

    imprimir_tabela(tabela);

    clock_t start_time = clock();
    busca(tabela, rebimboca);
    clock_t end_time = clock();
    double time_elapsed = (end_time - start_time) / (double) CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", time_elapsed);

    return 0;
}