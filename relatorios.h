#ifndef _RELATORIOS_H
#define _RELATORIOS_H

#include "sistema.h"

/// @brief Processa o comando MLR (Mostrar Lista de Reprodução).
/// @param sistema O sistema principal.
void geraRelatorioListaReproducao(tSistema* sistema);

/// @brief Processa o comando GRU (Gerar Relatório do Usuário).
/// @param sistema O sistema principal.
void geraRelatorioUsuario(tSistema* sistema);

/// @brief Processa o comando RGC (Relatório Geral de Conteúdo).
/// @param sistema O sistema principal.
void geraRelatorioGeralDeConteudo(tSistema* sistema);

/// @brief Processa o comando GRAC (Gerar Relatório de Avaliações de Conteúdo).
/// @param sistema O sistema principal.
void geraRelatorioAvaliacoes(tSistema* sistema);

#endif