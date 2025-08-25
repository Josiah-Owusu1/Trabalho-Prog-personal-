#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "busca.h"
#include "sistema.h"
#include "usuario.h"
#include "conteudo.h"
#include "util.h"
#include "sistema.h"

// Função auxiliar para converter uma string para maiúsculas
void paraMaiusculo(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

/// @brief Processa todos os comandos de busca e consulta (COF, COS, COJ, COD, etc.).
///        Ela filtra os resultados baseados no tipo de conteúdo, no termo de busca
///        e nas permissões do usuário (idade e tipo de assinatura).
/// @param sistema O sistema principal.
/// @param comando O comando de busca lido da entrada (ex: "COF", "COSP").
void realizaBusca(tSistema* sistema, const char* comando){
    char cpf[15];
    char termoBusca[101];

    scanf("%s ", cpf);
    // Lê o resto da linha como o termo de busca
    fgets(termoBusca, sizeof(termoBusca), stdin);
    termoBusca[strcspn(termoBusca, "\n")] = 0;

    tUsuario* usuario = buscaUsuarioSistema(sistema, cpf);
    if (!usuario) {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }

    // Verifica se o comando é premium
    int buscaPremium = (strlen(comando) == 4 && comando[3] == 'P');

    if (buscaPremium && getAssinaturaUsuario(usuario, sistema) == PADRAO) {
        printf("A CONTA DE CPF %s NAO POSSUI PERMISSAO PARA EXECUTAR ESSE COMANDO!\n", cpf);
        return;
    }

    printf("#TIPO ID; NOME; DURACAO; DISP. IDIOMA; ANO; PRODUTORA\n");

    int encontrou = 0;
    char tipoConteudoBuscado = comando[2]; // F, S, J, ou D

    // Itera por todo o catálogo de conteúdos do sistema
    for (int i = 0; i < getTotalConteudos(sistema); i++) {
        tConteudo* conteudo = getConteudoPeloIndice(sistema, i);
        int corresponde = 0;

        // 1. Filtra por tipo de conteúdo (F, S, J)
        if (tipoConteudoBuscado == getTipoConteudo(conteudo)) {
            // 2. Filtra por assinatura
            if (buscaPremium || getRestricaoConteudo(conteudo) == PADRAO) {
                // 3. Filtra por idade
                if (getTipoUsuario(usuario) == ADULTO || getRestricaoIdade(conteudo) == INFANTIL) {
                    
                    // 4. Filtra pelo termo de busca (no título ou ID)
                    char tituloMaiusculo[101];
                    strcpy(tituloMaiusculo, getTituloConteudo(conteudo));
                    paraMaiusculo(tituloMaiusculo);
                    
                    char termoMaiusculo[101];
                    strcpy(termoMaiusculo, termoBusca);
                    paraMaiusculo(termoMaiusculo);

                    if (strstr(tituloMaiusculo, termoMaiusculo) != NULL || strcmp(getCodConteudo(conteudo), termoBusca) == 0) {
                        corresponde = 1;
                    }
                }
            }
        }
        
        if (corresponde) {
            if (!encontrou) {
                encontrou = 1;
            }
            // A função printaConteudo já está no formato correto que precisamos.
            // Precisamos apenas adicionar a numeração.
            printf("%d-", encontrou);
            printaConteudo(conteudo);
        }
    }

    if (!encontrou) {
        printf("NENHUM CONTEUDO ENCONTRADO!\n");
    }
}

