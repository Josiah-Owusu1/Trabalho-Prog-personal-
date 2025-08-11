#ifndef _JOGO_H
#define _JOGO_H

#include "util.h"

// Forward declaration para o TAD opaco
typedef struct Jogo tJogo;

/// @brief Cria uma variável do tipo tJogo a partir de uma linha de dados.
/// @param linhaJogo A string lida do teclado com as informações de um jogo (sem o 'J').
/// @return Um ponteiro para o objeto tJogo* criado.
tJogo* criaJogo(char *linhaJogo);

/// @brief Libera a memória alocada dinamicamente para um jogo.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tJogo* e liberado.
void liberaJogo(void *dado);

/// @brief Imprime as informações de um jogo no formato especificado.
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tJogo*.
void printaJogo(void *dado);

// --- Funções "get" para os callbacks do TAD Conteudo ---

char getTipoJogo();
int getAnoLancamentoJogo(void *dado);
char* getCodConteudoJogo(void *dado);
char* getTituloJogo(void *dado);
int getDuracaoJogo(void *dado);
float getNotaMediaJogo(void *dado);
TipoAssinatura getRestricaoAssinaturaJogo(void *dado);
TipoUsuario getRestricaoIdadeJogo(void *dado);

#endif