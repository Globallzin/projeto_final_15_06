#pragma once

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

Data somarDataPorDia(Data base, int dias);
Data pegarDataAtual();
int obterDistanciaEntreDatas(Data um, Data dois);