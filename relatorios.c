#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "relatorios.h"
#include "sistema.h"
#include "usuario.h"
#include "conteudo.h"
#include "avaliacao.h"
#include "util.h"

void imprimeDadosBasicosUsuario(tUsuario* usuario);
void imprimeDadosEspecificosUsuario(tUsuario* usuario, tSistema* sistema);
void imprimeListaConsumidosUsuario(tUsuario* usuario);



/// @brief Processa o comando MLR (Mostrar Lista de Reprodução).
/// @param sistema O sistema principal.
void geraRelatorioListaReproducao(tSistema* sistema){
     char cpf[15];
    scanf("%s", cpf);

    tUsuario* usuario = buscaUsuarioSistema(sistema, cpf);
    if (!usuario) {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }
    
    // A função imprimeListaReproducaoUsuario já formata a saída corretamente
    imprimeListaReproducaoUsuario(usuario);
}

/// @brief Processa o comando GRU (Gerar Relatório do Usuário).
/// @param sistema O sistema principal.
void geraRelatorioUsuario(tSistema* sistema){
    char cpf[15], senha[21];
    scanf("%s", cpf);
    
    tUsuario* usuario = buscaUsuarioSistema(sistema, cpf);
    if (!usuario) {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }
    
    scanf("%s", senha);
    if (!verificaSenhaUsuario(usuario, senha)) {
        printf("SENHA INCORRETA! OPERACAO NAO PERMITIDA!\n");
        return;
    }

     printf("RELATORIO USUARIO DE CPF %s\n", cpf);
    imprimeDadosBasicosUsuario(usuario);
    imprimeDadosEspecificosUsuario(usuario, sistema);
    imprimeListaReproducaoUsuario(usuario);
    imprimeListaConsumidosUsuario(usuario);
}

/// @brief Processa o comando RGC (Relatório Geral de Conteúdo).
/// @param sistema O sistema principal.
void geraRelatorioGeralDeConteudo(tSistema* sistema){
     printf("RELATORIO GERAL DE CONTEUDO\n");
    // Esta função precisaria ser expandida para considerar o usuário que a chamou
    // e filtrar por assinatura e idade, conforme a especificação.
    // Por enquanto, uma versão simplificada que lista tudo:

    int totalConteudos = getTotalConteudos(sistema);
    if (totalConteudos == 0) {
        printf("NENHUM CONTEUDO ENCONTRADO!\n");
        return;
    }
    
    for (int i = 0; i < totalConteudos; i++) {
        tConteudo* c = getConteudoPeloIndice(sistema, i);
        printf("%d-", i + 1);
        printaConteudo(c);
    }
}

/// @brief Processa o comando GRAC (Gerar Relatório de Avaliações de Conteúdo).
/// @param sistema O sistema principal.
void geraRelatorioAvaliacoes(tSistema* sistema){
    char cpf[15], idConteudo[10];
    scanf("%s %s", cpf, idConteudo);

    if (!buscaUsuarioSistema(sistema, cpf)) {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }
    
    tConteudo* conteudo = buscaConteudoSistema(sistema, idConteudo);
    if (!conteudo) {
        printf("NENHUM CONTEUDO ENCONTRADO!\n");
        return;
    }
    
    // Lógica para verificar permissão de acesso ao conteúdo
    // (Falta implementar essa verificação)
    
    printf("LISTA DE AVALIACOES DO CONTEUDO %s %s - NOTA MEDIA: %.1f\n",
           idConteudo, getTituloConteudo(conteudo), getNotaMediaConteudo(conteudo));
           
    int qtdAvaliacoes = getQtdAvaliacoes(conteudo);
    for (int i = 0; i < qtdAvaliacoes; i++) {
        tAvaliacao* a = getAvaliacaoPosicao(conteudo, i);
        char* cpfAvaliador = getCpfAvaliacao(a);
        tUsuario* avaliador = buscaUsuarioSistema(sistema, cpfAvaliador);
        
        printf("%d- %s - %d\n",
               i + 1,
               getNomeUsuario(avaliador), // Precisaremos adicionar getNomeUsuario em usuario.c
               getNotaAvaliacao(a));
    }
}

void imprimeDadosBasicosUsuario(tUsuario* usuario) {
    // Adicionar getNomeCompleto, getTelefone, etc. em usuario.c
    printf("NOME: %s\n", getNomeCompleto(usuario));
    printf("TELEFONE: %s\n", getTelefone(usuario));
    printf("ENDERECO: %s\n", getEndereco(usuario));
    printf("NOME DE USUARIO: %s\n", getLogin(usuario));
    
    // Imprime asteriscos para a senha
    printf("SENHA: ");
    for (int i = 0; i < strlen(getSenha(usuario)); i++) {
        printf("*");
    }
    printf("\n");
    
    printf("E-MAIL: %s\n", getEmail(usuario));
    printf("DATA NASCIMENTO: %s\n", getDataNascimento(usuario));
    printf("NUM. CONTEUDOS CONSUMIDOS: %d\n", getNumConsumidos(usuario));
    
    int horas, minutos;
    converteMinutos(getTotalMinutosConsumidos(usuario), &horas, &minutos);
    printf("TOTAL HORAS CONSUMIDAS: %d:%02d\n", horas, minutos);
    printf("NUM. AVALIACOES REALIZADAS: %d\n", getNumAvaliacoes(usuario));
}

void imprimeDadosEspecificosUsuario(tUsuario* usuario, tSistema* sistema) {
    if (getTipoUsuario(usuario) == ADULTO) {
        const char* tipoAssinatura = getAssinaturaUsuario(usuario, sistema) == PREMIUM ? "PREMIUM" : "PADRAO";
        printf("USUARIO 18+ %s\n", tipoAssinatura);
        printf("CARTAO NUM.: %s\n", getCartao(usuario));
    } else {
        // A assinatura de um infantil é a mesma do responsável
        tUsuario* responsavel = buscaUsuarioSistema(sistema, getCpfResponsavel(usuario));
        const char* tipoAssinatura = getAssinaturaUsuario(responsavel, sistema) == PREMIUM ? "PREMIUM" : "PADRAO";
        printf("USUARIO INFANTIL %s\n", tipoAssinatura);
        printf("CPF RESPONSAVEL: %s\n", getCpfResponsavel(usuario));
    }
}

void imprimeListaConsumidosUsuario(tUsuario* usuario) {
    printf("LISTA DE CONTEUDOS CONSUMIDOS:\n");
    int qtdConsumidos = getNumConsumidos(usuario);
    if (qtdConsumidos == 0) {
        // A especificação não mostra uma mensagem de lista vazia aqui,
        // então não imprimimos nada a mais.
    }

    int totalMinutos = 0;
    for (int i = 0; i < qtdConsumidos; i++) {
        tConteudo* c = getConteudoConsumidoPeloIndice(usuario, i);
        // Formato GRU para consumidos: NUM-NOME_DO_CONTEUDO
        printf("%d-%s\n", i + 1, getTituloConteudo(c));
        totalMinutos += getDuracaoConteudo(c);
    }
    
    int horas, minutos;
    converteMinutos(totalMinutos, &horas, &minutos);
    printf("(TOTAL %02d:%02d horas)\n", horas, minutos);