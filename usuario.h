#ifndef _USUARIO_H
#define _USUARIO_H

#include "util.h"
#include "conteudo.h"

// declaracao para o TAD opaco
typedef struct Usuario tUsuario;

/// @brief Cria um objeto do tipo tUsuario*.
/// @param tipo O tipo de usuário a ser criado (ADULTO ou INFANTIL).
/// @param linhaDados A string com os dados do usuário a serem cadastrados.
/// @return Um ponteiro para o objeto tUsuario* criado.
tUsuario* criaUsuario(TipoUsuario tipo, char* linhaDados);

/// @brief Libera toda a memória alocada para um usuário e suas listas.
/// @param usuario Um ponteiro para o usuário a ser liberado.
void liberaUsuario(tUsuario* usuario);

/// @brief Retorna o CPF de um usuário.
/// @param usuario Um ponteiro para o usuário.
/// @return Uma string contendo o CPF do usuário.
char* getCpfUsuario(tUsuario* usuario);

/// @brief Verifica se a senha fornecida corresponde à senha do usuário.
/// @param usuario O usuário a ser verificado.
/// @param senha A senha a ser comparada.
/// @return 1 se a senha for correta, 0 caso contrário.
int verificaSenhaUsuario(tUsuario* usuario, const char* senha);

/// @brief Adiciona um conteúdo à lista de reprodução do usuário.
/// @param usuario O usuário que receberá o conteúdo.
/// @param conteudo O conteúdo a ser adicionado.
void adicionaConteudoListaReproducao(tUsuario* usuario, tConteudo* conteudo);

/// @brief Imprime a lista de reprodução de um usuário.
/// @param usuario O usuário cuja lista será impressa.
void imprimeListaReproducaoUsuario(tUsuario* usuario);



/// @brief Busca um conteúdo na lista de reprodução do usuário pelo seu ID.
/// @param usuario O usuário.
/// @param idConteudo O ID do conteúdo a ser buscado.
/// @return Um ponteiro para o tConteudo se encontrado, caso contrário NULL.
tConteudo* buscaConteudoListaReproducao(tUsuario* usuario, const char* idConteudo);

/// @brief Remove um conteúdo da lista de reprodução do usuário.
/// @param usuario O usuário.
/// @param idConteudo O ID do conteúdo a ser removido.
void removeConteudoListaReproducao(tUsuario* usuario, const char* idConteudo);

/// @brief Retorna o tipo do usuário (ADULTO ou INFANTIL).
/// @param usuario O usuário.
/// @return O enum TipoUsuario correspondente.
TipoUsuario getTipoUsuario(tUsuario* usuario);

/// @brief Retorna o tipo de assinatura de um usuário adulto.
//         Para um usuário infantil, retorna a assinatura do seu responsável.
/// @param usuario O usuário (pode ser infantil).
/// @param sistema O sistema principal, para buscar o responsável se necessário.
/// @return O enum TipoAssinatura correspondente.
TipoAssinatura getAssinaturaUsuario(tUsuario* usuario, tSistema* sistema);

/// @brief "Consome" o primeiro item da lista de reprodução do usuário.
//         Isso envolve mover o conteúdo para a lista de "consumidos" e
//         atualizar as estatísticas do usuário.
/// @param usuario O usuário.
/// @return Um ponteiro para o conteúdo que foi consumido.
tConteudo* consomePrimeiroDaLista(tUsuario* usuario);

#endif