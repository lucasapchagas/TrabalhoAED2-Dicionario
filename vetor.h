#ifndef VETOR_H
#define VETOR_H

// Estrutura de um vetor dinâmico genérico
typedef struct {
    void** dados;
    int tamanho;
    int capacidade;
} Vetor;

// Inicializa um novo vetor com capacidade para armazenar 'capacity' elementos
Vetor* inicializar_vetor(int capacidade);

// Libera a memória alocada para o vetor
void liberar_vetor(Vetor* v);

// Aumenta a capacidade do vetor para o dobro do tamanho atual
void redimensionar_vetor(Vetor* v);

// Adiciona um elemento no índice especificado
void adicionar_vetor_indice(Vetor* v, void* elemento, int indice);

#endif // VETOR_H