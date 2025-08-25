#ifndef _CADASTRO_H
#define _CADASTRO_H

#include "sistema.h"

/// @brief Processa o comando de Cadastro de Atores (CAT).
///        Ele verifica duplicatas e, se for válido, cria e adiciona o ator ao sistema.
/// @param sistema O ponteiro para o sistema principal.
void realizaCadastroAtor(tSistema* sistema);

/// @brief Processa o comando de Cadastro de Conteúdo (CAC).
///        Ele verifica se o distribuidor existe e se o conteúdo é novo antes de
///        criar e adicionar o conteúdo ao sistema e ao distribuidor.
/// @param sistema O ponteiro para o sistema principal.
void realizaCadastroConteudo(tSistema* sistema);

#endif