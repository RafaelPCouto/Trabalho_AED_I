
/*
 * Módulo: Estadia
 * Objetivo: Cadastrar e listar estadias do hotel.
 * Observação importante:
 */

#include <stdio.h>

/* ====== struct Estadia ====== */
struct Estadia
{
    int codigoEstadia;
    int codigoCliente;
    int numeroQuarto;
    int diaEntrada, mesEntrada, anoEntrada;
    int diaSaida, mesSaida, anoSaida;
    float totalPagar;
};

/* --------- Auxiliares internas --------- */

/* Consome o restante da linha no stdin (inclusive '\n') */
static void limpaLinhaEstadia(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

/* Converte data para número aproximado (dia + mes*30 + ano*365) */
static long dataParaNumero(int d, int m, int a)
{
    return (long)d + (long)m * 30L + (long)a * 365L;
}

/* Calcula "noites" aproximadas a partir das datas (mínimo 1) */
static int calcularNoites(int dE, int mE, int aE, int dS, int mS, int aS)
{
    long ent = dataParaNumero(dE, mE, aE);
    long sai = dataParaNumero(dS, mS, aS);
    long diff = sai - ent;
    if (diff < 1)
        return 1;
    return (int)diff;
}

/* Verifica se dois intervalos [E..S] se sobrepõem */
static int datasColidem(
    int dA1, int mA1, int aA1, int dA2, int mA2, int aA2,
    int dB1, int mB1, int aB1, int dB2, int mB2, int aB2)
{
    long inicioA = dataParaNumero(dA1, mA1, aA1);
    long fimA = dataParaNumero(dA2, mA2, aA2);
    long inicioB = dataParaNumero(dB1, mB1, aB1);
    long fimB = dataParaNumero(dB2, mB2, aB2);

    if (fimA < inicioB)
        return 0; /* A termina antes de B começar */
    if (fimB < inicioA)
        return 0; /* B termina antes de A começar */
    return 1;     /* sobreposição */
}

/*
 * Função: cadastrarEstadia
 * Parâmetros:
 *   - estadias, totalE: vetor e contador de estadias
 *   - clientes, totalC: vetor e contador de clientes (definidos em cliente.h)
 *   - quartos,  totalQ: vetor e contador de quartos  (definidos em quarto.h)
 * Regras:
 *   - Cliente e Quarto precisam existir
 *   - Quarto deve estar desocupado
 *   - Não pode haver sobreposição de períodos no mesmo quarto
 *   - Calcular total = diaria * noites (noites >= 1)
 *   - Marcar quarto como ocupado após registrar
 */
void cadastrarEstadia(
    struct Estadia estadias[], int *totalE,
    struct Cliente clientes[], int totalC,
    struct Quarto quartos[], int totalQ)
{
    int cod;
    printf("\n--- CADASTRO DE ESTADIA ---\nCodigo da estadia: ");
    if (scanf(" %d", &cod) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }

    /* Verificar código de estadia duplicado */
    for (int i = 0; i < *totalE; i++)
    {
        if (estadias[i].codigoEstadia == cod)
        {
            printf("ERRO: Ja existe uma estadia com este codigo!\n");
            return;
        }
    }

    int codCliente;
    printf("Codigo do cliente: ");
    if (scanf(" %d", &codCliente) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }

    /* Validar existência do cliente */
    int clienteExiste = 0;
    for (int i = 0; i < totalC; i++)
    {
        if (clientes[i].codigo == codCliente)
        {
            clienteExiste = 1;
            break;
        }
    }
    if (!clienteExiste)
    {
        printf("ERRO: Cliente nao encontrado!\n");
        return;
    }

    int numQuarto;
    printf("Numero do quarto: ");
    if (scanf(" %d", &numQuarto) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }

    /* Localizar quarto */
    int indiceQuarto = -1;
    for (int i = 0; i < totalQ; i++)
    {
        if (quartos[i].numero == numQuarto)
        {
            indiceQuarto = i;
            break;
        }
    }
    if (indiceQuarto == -1)
    {
        printf("ERRO: Quarto nao encontrado!\n");
        return;
    }

    /* Validar status do quarto */
    if (quartos[indiceQuarto].ocupado)
    {
        printf("ERRO: Quarto ja esta ocupado!\n");
        return;
    }

    /* Datas */
    int dE, mE, aE, dS, mS, aS;

    printf("\n--- Data de Entrada ---\n");
    printf("Dia: ");
    if (scanf(" %d", &dE) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }
    printf("Mes: ");
    if (scanf(" %d", &mE) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }
    printf("Ano: ");
    if (scanf(" %d", &aE) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }

    printf("\n--- Data de Saida ---\n");
    printf("Dia: ");
    if (scanf(" %d", &dS) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }
    printf("Mes: ");
    if (scanf(" %d", &mS) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }
    printf("Ano: ");
    if (scanf(" %d", &aS) != 1)
    {
        printf("Entrada invalida.\n");
        limpaLinhaEstadia();
        return;
    }

    /* Validar ordem das datas: saida >= entrada */
    long entNum = dataParaNumero(dE, mE, aE);
    long saiNum = dataParaNumero(dS, mS, aS);
    if (saiNum < entNum)
    {
        printf("ERRO: A data de saida eh anterior a data de entrada!\n");
        return;
    }

    /* Verificar conflitos com estadias existentes no mesmo quarto */
    for (int i = 0; i < *totalE; i++)
    {
        if (estadias[i].numeroQuarto == numQuarto)
        {
            if (datasColidem(
                    dE, mE, aE, dS, mS, aS,
                    estadias[i].diaEntrada, estadias[i].mesEntrada, estadias[i].anoEntrada,
                    estadias[i].diaSaida, estadias[i].mesSaida, estadias[i].anoSaida))
            {
                printf("ERRO: Conflito de datas! Ja existe uma estadia nesse periodo.\n");
                return;
            }
        }
    }

    /* Calcular total a pagar */
    int noites = calcularNoites(dE, mE, aE, dS, mS, aS);
    float diaria = quartos[indiceQuarto].diaria;
    float total = diaria * (float)noites;

    /* Registrar estadia */
    struct Estadia e;
    e.codigoEstadia = cod;
    e.codigoCliente = codCliente;
    e.numeroQuarto = numQuarto;
    e.diaEntrada = dE;
    e.mesEntrada = mE;
    e.anoEntrada = aE;
    e.diaSaida = dS;
    e.mesSaida = mS;
    e.anoSaida = aS;
    e.totalPagar = total;

    estadias[*totalE] = e;
    (*totalE)++;

    /* Marcar quarto como ocupado */
    quartos[indiceQuarto].ocupado = 1;

    printf("\nEstadia registrada com sucesso!\n");
    printf("Noites: %d | Diaria: R$ %.2f | Total: R$ %.2f\n", noites, diaria, total);
}

/*
 * Função: listarEstadias
 * Parâmetros:
 *   - estadias: vetor de estadias
 *   - total:    quantidade atual cadastrada
 */
void listarEstadias(struct Estadia estadias[], int total)
{
    printf("\n========== LISTA DE ESTADIAS ==========\n");
    if (total == 0)
    {
        printf("Nenhuma estadia registrada.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        struct Estadia *e = &estadias[i];
        printf("\nCodigo: %d | Cliente: %d | Quarto: %d\n",
               e->codigoEstadia, e->codigoCliente, e->numeroQuarto);
        printf("Entrada: %02d/%02d/%04d as 14:00\n",
               e->diaEntrada, e->mesEntrada, e->anoEntrada);
        printf("Saida:   %02d/%02d/%04d as 12:00\n",
               e->diaSaida, e->mesSaida, e->anoSaida);
        printf("Total a pagar: R$ %.2f\n", e->totalPagar);
    }
}
