#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "funcoesAuxiliares.h"
#include "funcoesUCS.h"
#include "constantes.h"
#include "funcoesAulas.h"
#include "Estruturas.h"
#include "funcoesAlunos.h"

char menuListarUCS(void);

char menuFicheiros(void);

char menuPRINCIPAL(int quantUCS,int quantAulasAgendadas,int quantAulasRealizadas,int quantAulasGravadas);

char menuAlunos(void);

char menuAulas(void);

char menuAlterarAula(void);

char menuUCS(void);

char menuEditarUC(void);

char menuAlterarAgendamentoAulas(void);

#endif // MENUS_H_INCLUDED
