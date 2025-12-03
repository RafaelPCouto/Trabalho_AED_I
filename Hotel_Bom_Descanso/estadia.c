/* estadia.c
   Implementação do módulo estadia (C, sem .h).
   Depende de Cliente e Quarto estarem definidos (ex.: incluindo cliente.c e quarto.c antes).
*/

#include <stdio.h>

/* Estrutura da estadia (compatível com main.c fornecido) */
typedef struct
{
    int codigoEstadia;
    int codigoCliente;
    int numeroQuarto;
    int diaEntrada, mesEntrada, anoEntrada;
    int diaSaida, mesSaida, anoSaida;
    float totalPagar;
} Estadia;

/* converte data para número (aproximação: dia + mes*30 + ano*365) */
static long dataParaNumero(int d, int m, int a)
{
    return (long)d + (long)m * 30L + (long)a * 365L;
}

/* calcula número de noites (usando aproximação acima) */
static int calcularNoites(int dE, int mE, int aE, int dS, int mS, int aS)
{
    long ent = dataParaNumero(dE, mE, aE);
    long sai = dataParaNumero(dS, mS, aS);
    long diff = sai - ent;
    if (diff < 1)
        return 1; /* ao menos 1 noite */
    return (int)diff;
}

/* verifica se dois intervalos [entradaA,saidaA] e [entradaB,saidaB] se sobrepõem */
static int datasColidem(int dA1, int mA1, int aA1, int dA2, int mA2, int aA2,
                        int dB1, int mB1, int aB1, int dB2, int mB2, int aB2)
{
    long inicioA = dataParaNumero(dA1, mA1, aA1);
    long fimA = dataParaNumero(dA2, mA2, aA2);
    long inicioB = dataParaNumero(dB1, mB1, aB1);
    long fimB = dataParaNumero(dB2, mB2, aB2);

    if (fimA < inicioB)
        return 0; /* A termina antes de B começar => sem conflito */
    if (fimB < inicioA)
        return 0; /* B termina antes de A começar => sem conflito */
    return 1;     /* sobreposição */
}

/* Função pública: cadastra uma estadia.
   Recebe arrays e totais para validar existência e conflitos.
   Faz I/O internamente (lê do stdin).
*/
void cadastrarEstadia(
    Estadia estadias[], int *totalE,
    /* tipos Cliente e Quarto devem estar definidos por inclusão prévia */
    /* usamos 'void*' apenas para compilar independente no módulo, sem protótipos:
       mas main inclui cliente.c e quarto.c; aqui assumimos que Cliente e Quarto existem.
    */
    void *clientes_void, int totalC,
    void *quartos_void, int totalQ)
{
    /* convertendo void* para os tipos reais (eles existem no projeto) */
    /* os nomes reais devem ser: typedef struct { int codigo; ... } Cliente; */
    typedef struct
    {
        int codigo;
        char nome[50];
        char endereco[100];
        char telefone[20];
    } ClienteLocal;
    typedef struct
    {
        int numero;
        int capacidade;
        float diaria;
        int ocupado;
    } QuartoLocal;

    ClienteLocal *clientes = (ClienteLocal *)clientes_void;
    QuartoLocal *quartos = (QuartoLocal *)quartos_void;

    int cod;
    printf("\n--- CADASTRO DE ESTADIA ---\nCodigo da estadia: ");
    if (scanf("%d", &cod) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }

    /* verificar código de estadia duplicado */
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
    if (scanf("%d", &codCliente) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }

    /* validar existência do cliente */
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
    if (scanf("%d", &numQuarto) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }

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

    if (quartos[indiceQuarto].ocupado)
    {
        printf("ERRO: Quarto ja esta ocupado!\n");
        return;
    }

    int dE, mE, aE, dS, mS, aS;
    printf("\n--- Data de Entrada ---\n");
    printf("Dia: ");
    if (scanf("%d", &dE) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }
    printf("Mes:  ");
    if (scanf("%d", &mE) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }
    printf("Ano:  ");
    if (scanf("%d", &aE) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }

    printf("\n--- Data de Saida ---\n");
    printf("Dia: ");
    if (scanf("%d", &dS) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }
    printf("Mes:  ");
    if (scanf("%d", &mS) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }
    printf("Ano:  ");
    if (scanf("%d", &aS) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Entrada invalida.\n");
        return;
    }

    /* validar ordem das datas */
    long entNum = dataParaNumero(dE, mE, aE);
    long saiNum = dataParaNumero(dS, mS, aS);
    if (saiNum < entNum)
    {
        printf("ERRO: A data de saida eh anterior a data de entrada!\n");
        return;
    }

    /* verificar conflitos com estadias existentes no mesmo quarto */
    for (int i = 0; i < *totalE; i++)
    {
        if (estadias[i].numeroQuarto == numQuarto)
        {
            if (datasColidem(dE, mE, aE, dS, mS, aS,
                             estadias[i].diaEntrada, estadias[i].mesEntrada, estadias[i].anoEntrada,
                             estadias[i].diaSaida, estadias[i].mesSaida, estadias[i].anoSaida))
            {
                printf("ERRO: Conflito de datas! Ja existe uma estadia nesse periodo.\n");
                return;
            }
        }
    }

    /* calcular total a pagar a partir da diária do quarto e número de noites */
    int noites = calcularNoites(dE, mE, aE, dS, mS, aS);
    float diaria = quartos[indiceQuarto].diaria;
    float total = diaria * (float)noites;

    /* preencher a nova estadia */
    Estadia e;
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

    /* salvar */
    estadias[*totalE] = e;
    (*totalE)++;

    /* marcar quarto como ocupado */
    quartos[indiceQuarto].ocupado = 1;

    printf("\nEstadia registrada com sucesso!\n");
    printf("Noites: %d | Diaria: R$ %.2f | Total: R$ %.2f\n", noites, diaria, total);
}

/* lista estadias */
void listarEstadias(Estadia estadias[], int total)
{
    printf("\n========== LISTA DE ESTADIAS ==========\n");
    if (total == 0)
    {
        printf("Nenhuma estadia registrada.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        Estadia *e = &estadias[i];
        printf("\nCodigo: %d | Cliente: %d | Quarto: %d\n", e->codigoEstadia, e->codigoCliente, e->numeroQuarto);
        printf("Entrada: %02d/%02d/%04d às 14:00\n", e->diaEntrada, e->mesEntrada, e->anoEntrada);
        printf("Saida:   %02d/%02d/%04d às 12:00\n", e->diaSaida, e->mesSaida, e->anoSaida);
        printf("Total a pagar: R$ %.2f\n", e->totalPagar);
    }
}
