#ifndef FUNCOESSTRUCTS_H_INCLUDED
#define FUNCOESSTRUCTS_H_INCLUDED

#include "funcoesAuxiliares.h"
#include "constantes.h"
#include "menus.h"
#include "funcoesAulas.h"
#include "Estruturas.h"
#include "funcoesAlunos.h"

void listarUCSDiurnas (tipoUC vetorUCS[MAXUCS], int quantUCs,int *UCSdiurno);

void listarAulas (tipoAula *vetorAulas, int quantUCs,int quantAulas);

void RankingUCS(tipoUC vetorUCS[], int quantUCs);

void leFicheiroBinarioUCS (tipoUC vetorUCS[], int *quantUCs);

void gravaFicheiroBinarioUCS (tipoUC vetorUCS[], int quantUCs);

int lerQuantidadeUCs(void);

tipoUC LerDadosUC(int *UCSdiurno);

int procuraUC (tipoUC vetorUCS[], int quantUCs, int codigoUC);

int acrescentaUC(tipoUC vetorUCS[], int quantUCs,int *UCSdiurno);

void editarUC(tipoUC vetorUCS[MAXUCS], int quantUCs);

void listarRankingUCS (tipoUC vetorUCS[MAXUCS], int quantUCs);

void listarUCS (tipoUC vetorUCS[MAXUCS], int quantUCs);

#endif // FUNCOESSTRUCTS_H_INCLUDED
