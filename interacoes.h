#ifndef _INTERACOES_H
#define _INTERACOES_H

#include "sistema.h"

/// @brief Processa o comando ACL (Adicionar Conteúdo à Lista).
/// @param sistema O sistema principal.
void realizaAdicionarConteudoNaLista(tSistema* sistema);

/// @brief Processa o comando RCL (Remover Conteúdo da Lista).
/// @param sistema O sistema principal.
void realizaRemoverConteudoDaLista(tSistema* sistema);

/// @brief Processa o comando CPCLR (Consumir Primeiro Conteúdo da Lista de Reprodução).
/// @param sistema O sistema principal.
void realizaConsumirPrimeiroDaLista(tSistema* sistema);

#endif