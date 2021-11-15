#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

#include "constantes.h"
#include "Estruturas.h"

tipoHora lerHoracLIM(char mensagem[],int minimo, int maximo);

int lerInteiro(char mensagem[], int minimo, int maximo);

int lerInteiroSlim(char mensagem[]);

float lerFloat(char mensagem[], float minimo, float maximo);

void lerString(char mensagem[], char vetorCaracteres[], int maximoCaracteres);

void limpaBufferStdin(void);

tipoData lerData(char mensagem[]);

void escreverData (tipoData data);

tipoHora lerHora(char mensagem[]);

void escreverHora (tipoHora hora);

#endif // FUNCOESAUXILIARES_H_INCLUDED
