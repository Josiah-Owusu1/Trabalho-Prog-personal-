#ifndef _DISTRIBUIDOR_H
#define _DISTRIBUIDOR_H

#include "conteudo.h"

// Forward declaration para o TAD opaco
typedef struct Distribuidor tDistribuidor;

/// @brief Cria um objeto do tipo tDistribuidor*.
/// @param linhaDados A string com os dados do distribuidor a serem cadastrados.
/// @return Um ponteiro para o objeto tDistribuidor* criado.
tDistribuidor* criaDistribuidor(char* linhaDados);

/// @brief Libera a memória alocada para um distribuidor.
/// @param distribuidor O distribuidor a ser liberado.
void liberaDistribuidor(tDistribuidor* distribuidor);

/// @brief Retorna o CNPJ de um distribuidor.
/// @param distribuidor Um ponteiro para o distribuidor.
/// @return Uma string contendo o CNPJ do distribuidor.
char* getCnpjDistribuidor(tDistribuidor* distribuidor);

/// @brief Adiciona um conteúdo à lista de conteúdos ofertados pelo distribuidor.
/// @param distribuidor O distribuidor que vai ofertar o conteúdo.
/// @param conteudo O conteúdo a ser adicionado.
void adicionaConteudoDistribuidor(tDistribuidor* distribuidor, tConteudo* conteudo);

#endif