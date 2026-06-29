#include <stdio.h>
#include <time.h>
#include "data.h"

int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int anoBissexto(int ano)
{
    if (ano % 400 == 0)
        return 1;
    if (ano % 100 == 0)
        return 0;
    if (ano % 4 == 0)
        return 1;

    return 0;
}

int pegarDiasDoMes(int mes, int ano)
{
    if (mes == 2 && anoBissexto(ano) == 1)
        return 29;

    return diasPorMes[mes - 1];
}

Data pegarDataAtual()
{
    time_t agora = time(NULL);
    struct tm dataAtual;
    localtime_s(&dataAtual, &agora);

    Data data;

    data.dia = dataAtual.tm_mday;
    data.mes = dataAtual.tm_mon + 1;
    data.ano = dataAtual.tm_year + 1900;

    return data;
}

Data somarDataPorDia(Data base, int dias)
{
    Data resultado = base;

    while (dias > 0)
    {
        resultado.dia++;

        if (resultado.dia > pegarDiasDoMes(resultado.mes, resultado.ano))
        {
            resultado.dia = 1;
            resultado.mes++;

            if (resultado.mes > 12)
            {
                resultado.mes = 1;
                resultado.ano++;
            }
        }

        dias--;
    }

    while (dias < 0)
    {
        resultado.dia--;

        if (resultado.dia < 1)
        {
            resultado.mes--;

            if (resultado.mes < 1)
            {
                resultado.mes = 12;
                resultado.ano--;
            }

            resultado.dia = pegarDiasDoMes(resultado.mes, resultado.ano);
        }

        dias++;
    }

    return resultado;
}

int converterDataParaDias(Data data)
{
    int total = 0;

    for (int ano = 1; ano < data.ano; ano++)
    {
        if (anoBissexto(ano) == 1)
            total += 366;
        else
            total += 365;
    }

    for (int mes = 1; mes < data.mes; mes++)
    {
        total += pegarDiasDoMes(mes, data.ano);
    }

    total += data.dia;

    return total;
}

int obterDistanciaEntreDatas(Data um, Data dois)
{
    return converterDataParaDias(dois) - converterDataParaDias(um);
}
