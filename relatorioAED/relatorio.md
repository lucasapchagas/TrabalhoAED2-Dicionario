# Relatório de Algoritmos e Estruturas de Dados 2

## Tabela Hash: O Índice Remissivo

**Alunos:**

Arthur Silva Matias - 22052559

Bianka Vasconcelos Maciel - 22153135

Hannah Lisboa Barreto - 22053199

Lucas Afonso Pereira Chagas - 22050316

Matheus Silva dos Santos - 22052573

### Introdução

Neste relatório, vamos apresentar o desenvolvimento de um índice remissivo com a utilização de tabelas hash. Um índice remissivo é uma lista de palavras encontradas em um texto, com referências para as páginas em que essas elas aparecem. Isso permite com que os leitores encontrem rapidamente informações específicas dentro de um texto, sem precisar lê-lo por completo. Com isso, o índice remissivo é comumente usado em livros, artigos acadêmicos e outros tipos de publicações para facilitar a pesquisa.

Nesse contexto, tabelas hash são estruturas de dados muito eficientes para realizar o mapeamento de dados para chaves pré-definidas. Para a tabela hash ser construída, é necessário uma função de hash que é responsável por realizar esse mapeamento. No caso do índice remissivo, essa função define em qual índice do vetor de entradas essa chave será associada, sendo que cada entrada do vetor contém uma lista encadeada responsável por armazenar as páginas em que a palavra ocorre.

Assim sendo, vamos explorar as etapas de implementação de uma tabela hash para índices remissivos. Além disso, examinaremos os desafios que surgem na implementação de tabelas hash e as soluções adotadas para resolvê-los.

### Objetivos
* **Objetivo Geral**:

O objetivo deste projeto é implementar um índice remissivo de um livro em formato de texto.

* **Objetivos Específicos:**

1. Identificar as palavras irrelevantes do texto, como preposições, artigos, advérbios, números, pronomes e pontuações, conhecidas como *stop words*.

2. Armazenar as palavras relevantes de um texto para serem utilizadas no processo de busca.

3. Avaliar a importância relativa de cada palavra em relação ao conjunto de dados, pelo cálculo do *TF-IDF* (*Term Frequency-Inverse Document Frequency*).

### Metodologia

Para alcançar nosso objetivo, vamos seguir as seguintes etapas:

1. Pré-processamento dos dados: retirar do texto as stop words, os acentos e os sinais de pontuação;

2. Criar a estrutura "palavra": desenvolver uma *struct* para armazenar uma string com a palavra lida e um vetor de inteiros que armazena as páginas em que a palavra aparece no arquivo;

3. Criar a estrutura "página": desenvovler uma *struct* para armazenar um vetor de ponteiros para a estrutura "palavra", o número de uma determinada página, a quantidade de palavras dessa página e o cálculo do *TD-IDF*;

4. Leitura das palavras do arquivo de texto: As palavras pré-processadas serão lidas do arquivo de texto e salvas nas estruturas desenvolvidas. As *stop words* foram salvas no dicionário estático e as palavras relevantes foram salvadas no dicionário dinâmico;

5. Desenvolvimento da tabela hash: Salvar as palavras na tabela hash;

6. Cálculo do TD-IDF: calcular o *TD-IDF* pela aplicação da fórmula;

7. Construção do índice remissivo: construir índice remissivo a partir dos dados coletados e calculados anteriormente, para a realização da busca das palavras conforme a sua taxa de relevância.

### Pré-Processamento

### Criação das Estruturas

### Armazenamento das Palavras

### Criação da Tabela Hash

### Cálculo do TF-IDF

### Índice Remissivo

### Resultados

Os resultados serão apresentados em forma de tabelas e gráficos, comparando o desempenho do índice remissivo com tabelas hash com outras estruturas de dados.

### Conclusão

Finalmente, vamos concluir o relatório com uma discussão sobre as conclusões a que chegamos e as possíveis aplicações futuras do nosso trabalho.