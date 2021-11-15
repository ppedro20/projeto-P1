#ifndef FUNCOESAULAS_H_INCLUDED
#define FUNCOESAULAS_H_INCLUDED

#include "funcoesAuxiliares.h"
#include "constantes.h"
#include "menus.h"
#include "funcoesUCS.h"
#include "Estruturas.h"
#include "funcoesAlunos.h"

void FinalizarTodasAsAulasTipoPL(tipoAula vetorAulas[], int *quantAulas,int quantUCs,tipoUC vetorUCS[],int *quantAulasPL,int *quantAulasAgendadas,int *quantAulasRealizadas);

void MostrarAulasGravadasdeUCsolicitada(tipoAula vetorAulas[], int *quantAulas,int quantUCs,tipoUC vetorUCS[]);

void leFicheiroBinarioAulas (tipoAula vetorAulas[], int *quantAulas);

void gravaFicheiroBinarioAulas (tipoAula vetorAulas[], int quantAulas);

void MostrarAulaSolicitada(tipoAula vetorAulas[], int *quantAulas,int quantUCs);

void FinalizarAula(tipoAula vetorAulas[], int *quantAulas,int quantUCs,int *quantAulasAgendadas,int *quantAulasRealizadas);

void IniciarAula(tipoAula vetorAulas[], int *quantAulas,int quantUCs);

void AlterarAgendamento(tipoAula vetorAulas[], int *quantAulas,int quantUCs);

int procuraAula (tipoAula vetorAulas[], int quantAulas, char designacaoAula[]);

tipoAula* eliminarAula (tipoAula vetorAulas[], int *quantAulas, tipoUC vetorUCS[]);

void listarAulas (tipoAula *vetorAulas, int quantUCs,int quantAulas);

void escreverDadosAula (tipoAula aula);

tipoAula* AgendarAula(int *quantAulasPL,tipoAula *vetorAulas,int *quantAulas,tipoUC vetorUCS[],int quantUCs,int *quantAulasAgendadas,int *aulasGravadas,float *percentagemAulasGravadas);

#endif // FUNCOESAULAS_H_INCLUDED
