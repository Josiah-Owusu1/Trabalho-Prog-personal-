#ifndef _SISTEMA_H
#define _SISTEMA_H

#include "usuario.h"
#include "distribuidor.h"
#include "conteudo.h"

// O TAD principal que armazena todos os dados do sistema
typedef struct Sistema tSistema;

/// @brief Cria e inicializa o sistema.
/// @return Um ponteiro para o sistema criado.
tSistema* criaSistema();

/// @brief Libera toda a memória alocada pelo sistema, incluindo todos os
/// usuários, distribuidores e conteúdos.
/// @param sistema O sistema a ser liberado.
void liberaSistema(tSistema* sistema);


// --- Funções de Gerenciamento de USUÁRIOS ---

/// @brief Adiciona um usuário à lista de usuários do sistema.
/// @param sistema O sistema.
/// @param usuario O usuário a ser adicionado.
void adicionaUsuarioSistema(tSistema* sistema, tUsuario* usuario);

/// @brief Busca um usuário no sistema pelo seu CPF.
/// @param sistema O sistema.
/// @param cpf O CPF a ser buscado.
/// @return Um ponteiro para o tUsuario se encontrado, caso contrário NULL.
tUsuario* buscaUsuarioSistema(tSistema* sistema, const char* cpf);


// --- Funções de Gerenciamento de DISTRIBUIDORES ---

/// @brief Adiciona um distribuidor à lista de distribuidores do sistema.
/// @param sistema O sistema.
/// @param distribuidor O distribuidor a ser adicionado.
void adicionaDistribuidorSistema(tSistema* sistema, tDistribuidor* distribuidor);

/// @brief Busca um distribuidor no sistema pelo seu CNPJ.
/// @param sistema O sistema.
/// @param cnpj O CNPJ a ser buscado.
/// @return Um ponteiro para o tDistribuidor se encontrado, caso contrário NULL.
tDistribuidor* buscaDistribuidorSistema(tSistema* sistema, const char* cnpj);


// --- Funções de Gerenciamento de CONTEÚDOS ---

/// @brief Adiciona um conteúdo ao catálogo geral do sistema.
/// @param sistema O sistema.
/// @param conteudo O conteúdo a ser adicionado.
void adicionaConteudoSistema(tSistema* sistema, tConteudo* conteudo);

/// @brief Busca um conteúdo no sistema pelo seu ID único.
/// @param sistema O sistema.
/// @param id O ID do conteúdo a ser buscado.
/// @return Um ponteiro para o tConteudo se encontrado, caso contrário NULL.
tConteudo* buscaConteudoSistema(tSistema* sistema, const char* id);

int getTotalConteudos(tSistema* sistema);
tConteudo* getConteudoPeloIndice(tSistema* sistema, int indice);

#endif