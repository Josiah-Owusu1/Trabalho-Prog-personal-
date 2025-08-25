
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "sistema.h"
#include "usuario.h"
#include "distribuidor.h"
#include "filme.h"
#include "serie.h"
#include "jogo.h"
#include "conteudo.h"

void lerLinha(char* buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
 
    buffer[strcspn(buffer, "\n")] = 0;
}

tConteudo* criaConteudoGenericoDeFilme(tFilme* filme) {
    return criaConteudo(filme,
                        getAnoLancamentoFilme,
                        getCodConteudoFilme,
                        getNotaMediaFilme,
                        getTituloFilme,
                        getDuracaoFilme,
                        printaFilme,
                        getRestricaoAssinaturaFilme,
                        getTipoFilme,
                        getRestricaoIdadeFilme,
                        liberaFilme);
}

/// @brief Processa o comando de Cadastro de Atores (CAT).
///        Ele verifica duplicatas e, se for válido, cria e adiciona o ator ao sistema.
/// @param sistema O ponteiro para o sistema principal.
void realizaCadastroAtor(tSistema* sistema){
        char tipoAtor[20], subtipoAtor[20];
    scanf("%s %s ", tipoAtor, subtipoAtor); // Lê "USUARIO PADRAO", por exemplo

    char linhaDados[256];
    lerLinha(linhaDados, sizeof(linhaDados));

    if (strcmp(tipoAtor, "USUARIO") == 0) {
        char cpf[15];
        sscanf(linhaDados, "%*[^;];%14[^;]", cpf); // Pula o nome e captura o CPF
        
        if (buscaUsuarioSistema(sistema, cpf)) {
            printf("CPF JA EXISTENTE! OPERACAO NAO PERMITIDA!\n");
            return;
            }

        TipoUsuario tipo = (strcmp(subtipoAtor, "INFANTIL") == 0) ? INFANTIL : ADULTO;
        tUsuario* novoUsuario = criaUsuario(tipo, subtipoAtor,linhaDados);
        adicionaUsuarioSistema(sistema, novoUsuario);
        printf("USUARIO CADASTRADO COM SUCESSO!\n");

    } else if (strcmp(tipoAtor, "DISTRIBUIDOR") == 0) {
        char cnpj[19];
        sscanf(linhaDados, "%*[^;];%18[^;]", cnpj); // Pula o nome e captura o CNPJ

        if (buscaDistribuidorSistema(sistema, cnpj)) {
            printf("CNPJ JA EXISTENTE! OPERACAO NAO PERMITIDA!\n");
            return;
        }
        
        tDistribuidor* novoDistribuidor = criaDistribuidor(linhaDados);
        adicionaDistribuidorSistema(sistema, novoDistribuidor);
        printf("DISTRIBUIDOR CADASTRADO COM SUCESSO!\n");
    }
}

/// @brief Processa o comando de Cadastro de Conteúdo (CAC).
///        Ele verifica se o distribuidor existe e se o conteúdo é novo antes de
///        criar e adicionar o conteúdo ao sistema e ao distribuidor.
/// @param sistema O ponteiro para o sistema principal.
void realizaCadastroConteudo(tSistema* sistema){
     char cnpj[19];
    scanf("%s ", cnpj); // Lê o CNPJ do distribuidor

    tDistribuidor* distribuidor = buscaDistribuidorSistema(sistema, cnpj);
    if (distribuidor == NULL) {
        printf("DISTRIBUIDOR SEM CADASTRO!\n");
        // Limpa o buffer de entrada para a próxima leitura de comando
        char buffer[256];
        lerLinha(buffer, sizeof(buffer));
        return;
    }
    
    char linhaConteudo[256];
    lerLinha(linhaConteudo, sizeof(linhaConteudo));
    
    char tipoConteudo = linhaConteudo[0];
    char* dadosConteudo = linhaConteudo + 2; // Pula o tipo e o ';' (ex: "F;")

    // Lógica para cadastro (ainda simplificada, sem update de série)
    if (tipoConteudo == 'F') {
        tFilme* novoFilme = criaFilme(dadosConteudo);
        tConteudo* novoConteudo = criaConteudoGenericoDeFilme(novoFilme);
        
        // Adiciona ao catálogo geral do sistema
        adicionaConteudoSistema(sistema, novoConteudo);
        // Adiciona à lista do distribuidor
        adicionaConteudoDistribuidor(distribuidor, novoConteudo);
        
        printf("CONTEUDO CADASTRADO COM SUCESSO!\n");
    } 
}
