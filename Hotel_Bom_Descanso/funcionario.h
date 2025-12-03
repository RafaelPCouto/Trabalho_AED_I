
/*
 * Módulo: Funcionario
 * Objetivo: Cadastrar e listar funcionários do Hotel.
 * Padrão:
 *  - Validação de telefone: entre 8 e 15 dígitos numéricos
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Estrutura do funcionário */
struct Funcionario {
    int   codigo;
    char  nome[50];      /* até 49 + '\0' */
    char  telefone[20];  /* até 19 + '\0' (permite formatação, ex.: ()- ) */
    char  cargo[30];     /* até 29 + '\0' */
    float salario;
};

/* Auxiliar simples para descartar o resto da linha (inclusive '\n') */
static void limpaLinhaFunc(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* nada */ }
}

/* Conta apenas os dígitos numéricos presentes na string (ignora espaços, '-', '(', ')', etc.) */
static int contarDigitos(const char *s) {
    int cont = 0;
    for (const char *p = s; *p; ++p) {
        if (isdigit((unsigned char)*p)) cont++;
    }
    return cont;
}

/*
 * Função: cadastrarFuncionario
 * Parâmetros:
 *   - funcionarios: vetor de funcionários
 *   - total: ponteiro para quantidade atual no vetor
 * Comportamento:
 *   - Lê os campos via scanf
 *   - Valida código duplicado
 *   - Valida telefone: entre 8 e 15 dígitos numéricos
 *   - Incrementa *total no final
 */
void cadastrarFuncionario(struct Funcionario funcionarios[], int *total)
{
    int codigo;

    printf("\n--- CADASTRO DE FUNCIONARIO ---\nCodigo: ");
    if (scanf(" %d", &codigo) != 1) {
        printf("ERRO: Codigo invalido.\n");
        limpaLinhaFunc();
        return;
    }

    /* Verificar código duplicado */
    for (int i = 0; i < *total; i++) {
        if (funcionarios[i].codigo == codigo) {
            printf("ERRO: Ja existe um funcionario com esse codigo!\n");
            return;
        }
    }

    funcionarios[*total].codigo = codigo;

    printf("Nome: ");
    if (scanf(" %49[^\n]", funcionarios[*total].nome) != 1) {
        printf("ERRO: Nome invalido.\n");
        limpaLinhaFunc();
        return;
    }

    /* Telefone com validação de quantidade de dígitos (8 a 15) */
    printf("Telefone: ");
    if (scanf(" %19[^\n]", funcionarios[*total].telefone) != 1) {
        printf("ERRO: Telefone invalido.\n");
        limpaLinhaFunc();
        return;
    }
    {
        int dig = contarDigitos(funcionarios[*total].telefone);
        if (dig < 8 || dig > 15) {
            printf("ERRO: Telefone deve conter entre 8 e 15 digitos numericos.\n");
            return;
        }
    }

    printf("Cargo: ");
    if (scanf(" %29[^\n]", funcionarios[*total].cargo) != 1) {
        printf("ERRO: Cargo invalido.\n");
        limpaLinhaFunc();
        return;
    }

    printf("Salario (R$): ");
    if (scanf(" %f", &funcionarios[*total].salario) != 1) {
        printf("ERRO: Salario invalido.\n");
        limpaLinhaFunc();
        return;
    }

    (*total)++;
    printf("Funcionario cadastrado!\n");
}

/*
 * Função: listarFuncionarios
 * Parâmetros:
 *   - funcionarios: vetor de funcionários
 *   - total: quantidade atual cadastrada
 * Comportamento:
 *   - Imprime todos os funcionários em formato simples
 */
void listarFuncionarios(struct Funcionario funcionarios[], int total)
{
    printf("\n========== LISTA DE FUNCIONARIOS ==========\n");
    if (total == 0) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nCodigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: R$ %.2f\n",
               funcionarios[i].codigo,
               funcionarios[i].nome,
               funcionarios[i].telefone,
               funcionarios[i].cargo,
               funcionarios[i].salario);
    }
}
