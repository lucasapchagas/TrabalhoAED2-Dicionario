#include <stdlib.h>

// Estrutura de um vetor dinâmico genérico
typedef struct {
    void** dados;
    int tamanho;
    int capacidade;
} Vetor;

// Inicializa um novo vetor com capacidade para armazenar 'capacity' elementos
Vetor* inicializar_vetor(int capacidade) {
    Vetor* v = malloc(sizeof(Vetor));
    v->capacidade = capacidade;
    v->tamanho = 0;
    v->dados = malloc((v->capacidade) * sizeof(void*));

    for (int i = 0; i < v->capacidade; i++)
        v->dados[i] = NULL;

    return v;
}

// Libera a memória alocada para o vetor
void liberar_vetor(Vetor* v) {
    free(v->dados);
    free(v);
}

// Aumenta a capacidade do vetor para o dobro do tamanho atual
void redimensionar_vetor(Vetor* v) {
    v->capacidade = v->capacidade * 2;
    v->dados = realloc(v->dados, v->capacidade * sizeof(void*));
}

// Adiciona um elemento ao indicie especificado
void adicionar_vetor_indice(Vetor* v, void* elemento, int indice) {
    if (v->tamanho == v->capacidade)
        redimensionar_vetor(v);

    if (v->dados[indice] == NULL)
        v->tamanho++;

    v->dados[indice] = elemento;
}