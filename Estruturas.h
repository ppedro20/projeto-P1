#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

typedef struct
{
    int dia, mes, ano;
} tipoData;

typedef struct
{
    int hour, minuto;
} tipoHora;

typedef struct
{
    int numEstudante;
    char tipoAcesso[MAXSTRING];

} tipoAluno;

typedef struct
{
    int codigo;
    char nomeUC[MAXSTRING];
    char tipoUC[MAXSTRING];
    int semestre;
    char regime[MAXSTRING_REGIME];
    int quantAulasT;
    int quantAulasTP;
    int quantAulasPL;
    tipoHora duracaoAula;
    int totalAulas;
    int quantAcessos;
    int numAulasGravadas;

} tipoUC;

typedef struct
{
    int posicao;
    char designacao[MAXSTRING];
    int codigoUC;
    char tipoAula[MAXSTRING_tipoAULA];
    char nomeDocente[MAXSTRING];
    tipoData Data;
    tipoHora HoraInicio;
    tipoHora HoraFim;
    char estadoAula[MAXSTRING_estadoAULA];
    char opGravacao[MAXSTRING_opGRAVACAO];
    int quantAlunosPresentes;
    int quantAcessosGravacao;
    int quantAcessos;
    tipoAluno AcessoAluno;

} tipoAula;

#endif // ESTRUTURAS_H_INCLUDED
