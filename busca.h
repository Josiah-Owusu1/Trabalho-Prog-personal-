#ifndef _BUSCA_H
#define _BUSCA_H

#include "sistema.h"

/// @brief Processa todos os comandos de busca e consulta (COF, COS, COJ, COD, etc.).
///        Ela filtra os resultados baseados no tipo de conteúdo, no termo de busca
///        e nas permissões do usuário (idade e tipo de assinatura).
/// @param sistema O sistema principal.
/// @param comando O comando de busca lido da entrada (ex: "COF", "COSP").
void realizaBusca(tSistema* sistema, const char* comando);

#endif