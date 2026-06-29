#pragma once

#include "cadastro.h"
#include "verificadores.h"
#include "data.h"

typedef struct
{
    int idVenda;
    Cliente cliente;
    float valorTotalVenda;
    int formaPagamento;
    int qtdeParcelas;
    Data dataVenda;
    char observacao[50];
} Venda;

typedef struct
{
    int idParcela;
    int idVenda;
    int numeroDaParcela;
    float valorDaParcela;
    Data dataVencimento;
    Data dataRecebimento;
    char situacaoDaParcela[30];
} Parcela;

void inicializarVendas(void);
void registrarVenda(void);
void mostrarTodasParcelas(void);
void gerarParcelas(Venda venda);
void consultarVendas(void);
void quitarParcelas(Venda venda);
void liquidarParcelas(Venda venda);
void pagarParcela(void);
void visualizarParcelasVencidas(void);
void visualizarClientesComDebitosPendentes(void);
void visualizarFaturamentoTotal(void);
