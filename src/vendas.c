#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vendas.h"
#include "utilidades.h"
#include "verificadores.h"
#include "cadastro.h"
#include "data.h"

int qtdeVendasAtuais = 0;
Venda vendasAtuais[100];

int qtdeParcelasAtuais = 0;
Parcela parcelasAtuais[100][10];
// primeiro indice = id da venda
// segundo indice = id da parcela

// Parcela 2 da venda 3 -> parcelasAtuais[2][1]

int parcelaEstaEmAberto(Parcela parcela)
{
    return strcmp(parcela.situacaoDaParcela, "Em aberto") == 0;
}

int vendaTemParcelaEmAberto(int idVenda)
{
    Venda venda = vendasAtuais[idVenda];

    for (int i = 0; i < venda.qtdeParcelas; i++)
    {
        if (parcelaEstaEmAberto(parcelasAtuais[idVenda][i]) == 1)
            return 1;
    }

    return 0;
}

int clienteJaFoiListadoComDebito(char cpf[], int indiceVendaAtual)
{
    for (int i = 0; i < indiceVendaAtual; i++)
    {
        if (strcmp(vendasAtuais[i].cliente.cpf, cpf) == 0 && vendaTemParcelaEmAberto(i) == 1)
            return 1;
    }

    return 0;
}

Venda gerarNovaVenda()
{
    Venda novaVenda = {0};

    novaVenda.idVenda = qtdeVendasAtuais;

    qtdeVendasAtuais++;

    return novaVenda;
}

// Venda venda1 = {
//     .idVenda = 0,
//     .qtdeParcelas = 5,
//     .formaPagamento = 4,
// };

// Venda venda2 = {
//     .idVenda = 1,
//     .qtdeParcelas = 1,
//     .formaPagamento = 1,
// };

void inicializarVendas()
{
}

void registrarVenda()
{
    limparConsole();

    if (qtdeVendasAtuais >= 100)
    {
        printf("Limite de vendas atingido!\n");
        return;
    }

    Venda novaVenda = gerarNovaVenda();
    novaVenda.dataVenda = pegarDataAtual();
    strcpy(novaVenda.observacao, "Sem observacao");

    while (1)
    {
        char cpf[20];
        printf("Digite o CPF do cliente: ");
        scanf("%s", cpf);

        Cliente clienteEncontrado = buscarClientePorCPF(cpf);

        if (clienteEncontrado.cpf[0] == '\0')
        {
            printf("Cliente nao encontrado! Tente novamente.\n");
        }
        else
        {
            novaVenda.cliente = clienteEncontrado;
            break;
        }
    }

    while (1)
    {
        printf("Qual o valor da venda? ");
        scanf("%f", &novaVenda.valorTotalVenda);

        if (novaVenda.valorTotalVenda > 0)
            break;

        printf("Valor invalido, tente novamente.\n");
    }

    while (1)
    {
        printf("\
        Qual a forma de pagamento?\n\
        1 - Dinheiro\n\
        2 - Pix\n\
        3 - Cartao a vista\n\
        4 - Cartao Parcelado\n");
        scanf("%d", &novaVenda.formaPagamento);

        if (novaVenda.formaPagamento >= 1 && novaVenda.formaPagamento <= 4)
            break;

        printf("Forma de pagamento invalida, tente novamente.\n");
    }

    if (novaVenda.formaPagamento == 4)
    {
        int qtdeParcelas;
        printf("Deseja dividir em quantas parcelas? (2-10) ");
        scanf("%d", &qtdeParcelas);
        novaVenda.qtdeParcelas = clamp(qtdeParcelas, 2, 10);
    }
    else
    {
        novaVenda.qtdeParcelas = 1;
    }

    for (int i = 0; i < novaVenda.qtdeParcelas; i++)
    {
        float valorDessaParcela = novaVenda.valorTotalVenda / novaVenda.qtdeParcelas;
        float acrescimo = pow(1.01, i);
        Parcela parcela = {0};

        parcela.idParcela = qtdeParcelasAtuais;
        parcela.idVenda = novaVenda.idVenda;
        parcela.numeroDaParcela = i;
        parcela.valorDaParcela = valorDessaParcela * acrescimo;
        parcela.dataVencimento = novaVenda.dataVenda;
        parcela.dataRecebimento = novaVenda.dataVenda;

        if (novaVenda.formaPagamento == 4)
        {
            parcela.dataVencimento = somarDataPorDia(novaVenda.dataVenda, 30 * (i + 1));
            parcela.dataRecebimento.dia = 1;
            parcela.dataRecebimento.mes = 1;
            parcela.dataRecebimento.ano = 1900;
            strcpy(parcela.situacaoDaParcela, "Em aberto");
        }
        else
        {
            strcpy(parcela.situacaoDaParcela, "Paga");
        }

        parcelasAtuais[novaVenda.idVenda][i] = parcela;
        qtdeParcelasAtuais++;
    }

    vendasAtuais[novaVenda.idVenda] = novaVenda;

    limparConsole();

    printf("Nova venda feita! Valor total %.2f (%d parcelas)\n\n", novaVenda.valorTotalVenda, novaVenda.qtdeParcelas);
}

void mostrarTodasParcelas()
{
    limparConsole();

    if (qtdeParcelasAtuais <= 0)
    {
        printf("Nenhuma parcela/venda encontrada!\n");
        return;
    }

    for (int i = 0; i < qtdeVendasAtuais; i++)
    {
        Venda vendaAtual = vendasAtuais[i];

        printf("\n\033[36m--------------------\033[0m\n\n");
        printf("\033[36mInformacoes da venda\033[0m\n");
        printf("ID DA VENDA: %d\n", i + 1);
        printf("Data da venda: ");
        printarDataFormatada(vendaAtual.dataVenda);
        printf("\n");
        printf("Observacao: %s\n", vendaAtual.observacao);
        printf("Valor total da venda: %.2f\n", vendaAtual.valorTotalVenda);
        printf("\n");

        printf("\033[36mInformacoes do cliente\033[0m\n");
        mostrarInformacoesCliente(vendaAtual.cliente);
        printf("\n");

        printf("\033[36mParcelas:\033[0m\n\n");

        for (int j = 0; j < vendaAtual.qtdeParcelas; j++)
        {
            Parcela parcelaAtual = parcelasAtuais[i][j];
            printf("ID da parcela: %d\n", parcelaAtual.idParcela + 1);
            printf("Parcela de numero: %d\n", parcelaAtual.numeroDaParcela + 1);
            printf("Valor da parcela: %.2f\n", parcelaAtual.valorDaParcela);
            printf("Data de vencimento: ");
            printarDataFormatada(parcelaAtual.dataVencimento);
            printf("\n");
            printf("Data de recebimento: ");
            if (parcelaEstaEmAberto(parcelaAtual) == 1)
                printf("Ainda nao recebida");
            else
                printarDataFormatada(parcelaAtual.dataRecebimento);
            printf("\n");
            printf("Situacao da parcela: %s\n\n", parcelaAtual.situacaoDaParcela);
        }
        printf("\033[36m--------------------\033[0m\n");
    }
}

void pagarParcela()
{
    int idVenda = -1;
    int idParcela = -1;
    char escolha;
    int encontrouParcelaEmAberto = 0;

    limparConsole();

    if (qtdeParcelasAtuais <= 0)
    {
        printf("Nenhuma parcela/venda encontrada!\n");
        return;
    }

    printf("\033[36mParcelas em aberto:\033[0m\n\n");

    for (int i = 0; i < qtdeVendasAtuais; i++)
    {
        Venda venda = vendasAtuais[i];

        for (int j = 0; j < venda.qtdeParcelas; j++)
        {
            Parcela parcela = parcelasAtuais[i][j];

            if (parcelaEstaEmAberto(parcela) == 1)
            {
                encontrouParcelaEmAberto = 1;
                printf("ID da venda: %d\n", i + 1);
                printf("Cliente: %s\n", venda.cliente.nome);
                printf("Parcela: %d\n", parcela.numeroDaParcela + 1);
                printf("Valor: %.2f\n", parcela.valorDaParcela);
                printf("Vencimento: ");
                printarDataFormatada(parcela.dataVencimento);
                printf("\n\n");
            }
        }
    }

    if (encontrouParcelaEmAberto == 0)
    {
        printf("Nao existem parcelas em aberto!\n");
        return;
    }

    while (1)
    {
        printf("Digite o ID da venda: ");
        scanf(" %d", &idVenda);

        idVenda -= 1;

        if (idVenda < 0 || idVenda >= qtdeVendasAtuais)
        {
            printf("Id de venda invalido!\n");
        }
        else if (vendaTemParcelaEmAberto(idVenda) == 0)
        {
            printf("Essa venda nao tem parcelas em aberto!\n");
        }
        else
        {
            break;
        }
    }

    Venda venda = vendasAtuais[idVenda];
    // parcelas estao em parcelasAtuais[idVenda][0 a 9]

    for (int i = 0; i < venda.qtdeParcelas; i++)
    {
        Parcela parcela = parcelasAtuais[idVenda][i];
        if (strcmp(parcela.situacaoDaParcela, "Em aberto") == 0)
        {
            idParcela = i;
            break;
        }
    }

    Parcela parcela = parcelasAtuais[idVenda][idParcela];

    printf("Deseja quitar a parcela %d no valor de %.2f? (S/N)\n", idParcela + 1, parcela.valorDaParcela);

    scanf(" %c", &escolha);

    if (escolha == 'S' || escolha == 's')
    {
        strcpy(parcelasAtuais[idVenda][idParcela].situacaoDaParcela, "Paga");
        parcelasAtuais[idVenda][idParcela].dataRecebimento = pegarDataAtual();

        limparConsole();
        printf("Parcela paga com sucesso!\n");
    }
    else
    {
        limparConsole();
        printf("Pagamento cancelado.\n");
    }
}

void visualizarParcelasVencidas()
{
    Data hoje = pegarDataAtual();
    int encontrou = 0;

    limparConsole();

    printf("\033[36mParcelas vencidas:\033[0m\n\n");

    for (int i = 0; i < qtdeVendasAtuais; i++)
    {
        Venda venda = vendasAtuais[i];

        for (int j = 0; j < venda.qtdeParcelas; j++)
        {
            Parcela parcela = parcelasAtuais[i][j];
            int diasVencidos = obterDistanciaEntreDatas(parcela.dataVencimento, hoje);

            if (parcelaEstaEmAberto(parcela) == 1 && diasVencidos > 0)
            {
                encontrou = 1;
                printf("ID da venda: %d\n", i + 1);
                printf("Cliente: %s\n", venda.cliente.nome);
                printf("CPF: %s\n", venda.cliente.cpf);
                printf("Parcela: %d\n", parcela.numeroDaParcela + 1);
                printf("Valor: %.2f\n", parcela.valorDaParcela);
                printf("Vencimento: ");
                printarDataFormatada(parcela.dataVencimento);
                printf(" (%d dia(s) vencida)\n\n", diasVencidos);
            }
        }
    }

    if (encontrou == 0)
    {
        printf("Nenhuma parcela vencida encontrada.\n");
    }
}

void visualizarClientesComDebitosPendentes()
{
    int encontrou = 0;

    limparConsole();

    printf("\033[36mClientes com debitos pendentes:\033[0m\n\n");

    for (int i = 0; i < qtdeVendasAtuais; i++)
    {
        Venda venda = vendasAtuais[i];

        if (vendaTemParcelaEmAberto(i) == 1 && clienteJaFoiListadoComDebito(venda.cliente.cpf, i) == 0)
        {
            encontrou = 1;
            mostrarInformacoesCliente(venda.cliente);
            printf("\n");
        }
    }

    if (encontrou == 0)
    {
        printf("Nenhum cliente com debito pendente encontrado.\n");
    }
}

void visualizarFaturamentoTotal()
{
    float totalVendido = 0;
    float totalRecebido = 0;
    float totalPendente = 0;

    limparConsole();

    for (int i = 0; i < qtdeVendasAtuais; i++)
    {
        Venda venda = vendasAtuais[i];

        for (int j = 0; j < venda.qtdeParcelas; j++)
        {
            Parcela parcela = parcelasAtuais[i][j];

            totalVendido += parcela.valorDaParcela;

            if (parcelaEstaEmAberto(parcela) == 1)
                totalPendente += parcela.valorDaParcela;
            else
                totalRecebido += parcela.valorDaParcela;
        }
    }

    printf("\033[36mFaturamento total:\033[0m\n\n");
    printf("Quantidade de vendas: %d\n", qtdeVendasAtuais);
    printf("Valor total vendido: %.2f\n", totalVendido);
    printf("Valor total recebido: %.2f\n", totalRecebido);
    printf("Valor pendente: %.2f\n", totalPendente);
}
