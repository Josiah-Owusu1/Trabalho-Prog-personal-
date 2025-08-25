#include <stdio.h>
#include <string.h>

#include "interacoes.h"
#include "sistema.h"
#include "usuario.h"
#include "conteudo.h"
#include "avaliacao.h"

/// @brief Processa o comando ACL (Adicionar Conteúdo à Lista).
/// @param sistema O sistema principal.
void realizaAdicionarConteudoNaLista(tSistema* sistema){
    char cpf[15], idConteudo[10];
    scanf("%s %s", cpf, idConteudo);

    tUsuario* usuario = buscaUsuarioSistema(sistema, cpf);
    if (!usuario) {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }

    tConteudo* conteudo = buscaConteudoSistema(sistema, idConteudo);
    if (!conteudo) {
        printf("O CONTEUDO %s NAO ESTA CADASTRADO!\n", idConteudo);
        imprimeListaReproducaoUsuario(usuario);
        return;
    }

    if (buscaConteudoListaReproducao(usuario, idConteudo)) {
        // Conteúdo já está na lista, não faz nada.
        imprimeListaReproducaoUsuario(usuario);
        return;
    }
    
    if (getTipoUsuario(usuario) == INFANTIL && getRestricaoIdade(conteudo) == ADULTO) {
        printf("NAO EH POSSIVEL ADICIONAR O CONTEUDO %s A CONTA INFANTIL DO CPF %s!\n", idConteudo, cpf);
        imprimeListaReproducaoUsuario(usuario);
        return;
    }
    
    if (getAssinaturaUsuario(usuario, sistema) == PADRAO && getRestricaoConteudo(conteudo) == PREMIUM) {
        printf("NAO EH POSSIVEL ADICIONAR O CONTEUDO PREMIUM %s A CONTA PADRAO DO CPF %s!\n", idConteudo, cpf);
        imprimeListaReproducaoUsuario(usuario);
        return;
    }

    adicionaConteudoListaReproducao(usuario, conteudo);
    imprimeListaReproducaoUsuario(usuario);
}


/// @brief Processa o comando RCL (Remover Conteúdo da Lista).
/// @param sistema O sistema principal.
void realizaRemoverConteudoDaLista(tSistema* sistema){
     char cpf[15], idConteudo[10];
    scanf("%s %s", cpf, idConteudo);

    tUsuario* usuario = buscaUsuarioSistema(sistema, cpf);
    if (!usuario) {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }

    if (!buscaConteudoSistema(sistema, idConteudo)) {
        printf("O CONTEUDO %s NAO ESTA CADASTRADO!\n", idConteudo);
        imprimeListaReproducaoUsuario(usuario);
        return;
    }

    if (!buscaConteudoListaReproducao(usuario, idConteudo)) {
        printf("O CONTEUDO %s NAO ESTA PRESENTE NA LISTA DE REPRODUCAO DO USUARIO %s!\n", idConteudo, cpf);
    } else {
        removeConteudoListaReproducao(usuario, idConteudo);
        printf("O CONTEUDO %s FOI REMOVIDO DA LISTA DE REPRODUCAO DO USUARIO %s!\n", idConteudo, cpf);
    }
    
    imprimeListaReproducaoUsuario(usuario);
}

/// @brief Processa o comando CPCLR (Consumir Primeiro Conteúdo da Lista de Reprodução).
/// @param sistema O sistema principal.
void realizaConsumirPrimeiroDaLista(tSistema* sistema){
    char cpf[15];
    scanf("%s", cpf);

    tUsuario* usuario = buscaUsuarioSistema(sistema, cpf);
    if (!usuario) {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }

    tConteudo* consumido = consomePrimeiroDaLista(usuario);

    if (!consumido) {
        printf("LISTA DO USUARIO %s ESTA VAZIA! OPERACAO NAO PERMITIDA!\n", cpf);
        return;
    }
    
    printf("CONTEUDO %s FOI CONSUMIDO PELO USUARIO %s!\n", getTituloConteudo(consumido), cpf);

    if (getTipoUsuario(usuario) == ADULTO) {
        printf("DIGITE UMA NOTA ENTRE 1 E 5\n");
        int nota;
        scanf("%d", &nota);

        if (nota >= 1 && nota <= 5) {
            tAvaliacao* avaliacao = criaAvaliacao(cpf, nota);
            inserirAvaliacaoConteudo(consumido, avaliacao);
            // Aqui deveríamos incrementar o `numAvaliacoesRealizadas` do usuário.
            // (Falta adicionar um "setter" ou função para isso em usuario.c)
            printf("CONTEUDO %s AVALIADO COM NOTA %d!\n", getTituloConteudo(consumido), nota);
        }
   
}

