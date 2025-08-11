#ifndef _SERIE_H
#define _SERIE_H

#include "util.h"

// Forward declaration para o TAD opaco
typedef struct Serie tSerie;

/// @brief Cria uma variável do tipo tSerie a partir de uma linha de dados.
/// @param linhaSerie A string lida do teclado com as informações de uma série (sem o 'S').
/// @return Um ponteiro para o objeto tSerie* criado.
tSerie* criaSerie(char *linhaSerie);

/// @brief Libera a memória alocada dinamicamente para uma série.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tSerie* e liberado.
void liberaSerie(void *dado);

/// @brief Imprime as informações de uma série no formato especificado.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tSerie*.
void printaSerie(void *dado);

/// @brief Atualiza o número de episódios de uma série existente.
/// @param dado Um ponteiro para uma série.
/// @param novoTotalEpisodios O novo número total de episódios.
void atualizaEpisodiosSerie(void *dado, int novoTotalEpisodios);

// --- Funções "get" para os callbacks do TAD Conteudo ---

char getTipoSerie();
int getAnoLancamentoSerie(void *dado);
char* getCodConteudoSerie(void *dado);
char* getTituloSerie(void *dado);
int getDuracaoSerie(void *dado);
float getNotaMediaSerie(void *dado);
TipoAssinatura getRestricaoAssinaturaSerie(void *dado);
TipoUsuario getRestricaoIdadeSerie(void *dado);

#endif