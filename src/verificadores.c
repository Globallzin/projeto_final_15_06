#include <stdio.h>
#include <string.h>
#include "utilidades.h"
#include "data.h"

int regra(char c)
{
    int n = c - '0';
    n *= 2;

    if (n >= 10)
    {
        int esquerda = n / 10;
        int direita = n - 10;

        return esquerda + direita;
    }

    return n;
}

int validarCPF(char cpf[20])
{
    char cpfLimpo[20];
    int primeiroDigitoValido = 0;
    int segundoDigitoValido = 0;
    int soma1 = 0;
    int soma2 = 0;
    int todosDigitosIguais = 1;

    // limpando o CPF (sem . e -)
    int contador = 0;
    for (int i = 0; cpf[i] != '\0'; i++)
    {
        if (cpf[i] >= '0' && cpf[i] <= '9')
        {
            cpfLimpo[contador] = cpf[i];
            contador++;
        }
    }
    cpfLimpo[contador] = '\0';

    if (contador != 11)
        return 0;

    for (int i = 1; i < 11; i++)
    {
        if (cpfLimpo[i] != cpfLimpo[0])
            todosDigitosIguais = 0;
    }

    if (todosDigitosIguais == 1)
        return 0;

    // 123.456.789-01
    for (int i = 0; i < 9; i++)
    {
        int numeroAtual = cpfLimpo[i] - '0';
        soma1 += numeroAtual * (10 - i);
    }
    for (int i = 0; i < 10; i++)
    {
        int numeroAtual = cpfLimpo[i] - '0';
        soma2 += numeroAtual * (11 - i);
    }

    int primeiroDigito = (soma1 * 10) % 11;
    int segundoDigito = (soma2 * 10) % 11;

    if (primeiroDigito == 10)
        primeiroDigito = 0;
    if (segundoDigito == 10)
        segundoDigito = 0;

    if (primeiroDigito == cpfLimpo[9] - '0')
        primeiroDigitoValido = 1;
    if (segundoDigito == cpfLimpo[10] - '0')
        segundoDigitoValido = 1;

    return primeiroDigitoValido == 1 && segundoDigitoValido == 1;
}

int validarData(Data data)
{
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int mesOk = data.mes >= 1 && data.mes <= 12;
    int anoOk;
    int diaOk = 0;
    int idade;
    int usuarioMaiorDeIdade;
    Data hoje = pegarDataAtual();

    anoOk = data.ano > 0 && data.ano <= hoje.ano;

    if (anoOk == 0)
        return 0;

    if (mesOk == 0)
        return 0;

    // anos bissextos
    if (((data.ano % 400 == 0) || (data.ano % 4 == 0 && data.ano % 100 != 0)) && data.mes == 2)
    {
        diaOk = data.dia >= 1 && data.dia <= 29;
    }
    else
    {
        diaOk = data.dia >= 1 && data.dia <= diasPorMes[data.mes - 1];
    }

    idade = hoje.ano - data.ano;

    if (hoje.mes < data.mes || (hoje.mes == data.mes && hoje.dia < data.dia))
        idade--;

    usuarioMaiorDeIdade = idade >= 18;

    return usuarioMaiorDeIdade == 1 && diaOk == 1 && mesOk == 1 && anoOk == 1;
}

int validarTelefone(char telefone[15])
{
    int tamanho = strlen(telefone);

    if (telefone[0] != '0')
    {
        return 0;
    }

    if (!(tamanho == 11 || tamanho == 12))
    {
        return 0;
    }

    for (int i = 0; i < tamanho; i++)
    {
        if (!(telefone[i] >= '0' && telefone[i] <= '9'))
        {
            return 0;
        }
    }

    return 1;
}

int validarCartao(char numeroCartao[20])
{
    int soma = 0;
    int tamanho = strlen(numeroCartao);

    if (tamanho != 16)
        return 0;

    for (int i = 0; i < 16; i++)
    {
        if (!(numeroCartao[i] >= '0' && numeroCartao[i] <= '9'))
            return 0;

        // verificar se cartao[i+1] é par
        if ((i + 1) % 2 == 1)
        {
            // o valor de i é par,
            // entao vamos somar o numero da regra!

            soma += regra(numeroCartao[i]);
        }
        else
        {
            // o valor de i é ímpar
            soma += numeroCartao[i] - '0';
        }
    }

    if (soma % 10 == 0)
    {
        return 1;
    }

    return 0;
}

// atualmente ele nao diferencia muito bem arroba e ponto
// mas foi o maximo que deu p fazer sem ficar hardcodando tudo
// depois dá para melhorar.
int validarChavePix(char chavePix[30])
{
    // aabcdef@gmail.com.br

    int posicaoArroba = procurarCaractere(chavePix, '@', 0);

    int arrobaOk = (posicaoArroba) >= 2;
    int pontosOk = 1;
    int pontoPassado = posicaoArroba;

    if (procurarCaractere(chavePix, '@', posicaoArroba + 1) != -1)
    {
        return 0;
    }

    while (1)
    {
        int atual = procurarCaractere(chavePix, '.', pontoPassado + 1);

        if (atual == -1)
            break;

        if (chavePix[atual + 1] == '\0' || chavePix[atual + 2] == '\0')
            pontosOk = 0;

        pontoPassado = atual;
    }

    return pontosOk == 1 && arrobaOk == 1;
}
