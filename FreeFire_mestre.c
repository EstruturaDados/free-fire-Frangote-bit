#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_COMPONENTES 20

// =======================================
// STRUCT DOS COMPONENTES
// =======================================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// =======================================
// VARIÁVEIS GLOBAIS
// =======================================
int totalComponentes = 0;

// Contadores de comparações
int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;
int comparacoesBusca = 0;

// Controle da ordenação
bool ordenadoPorNome = false;

// =======================================
// FUNÇÃO PARA LIMPAR BUFFER
// =======================================
void limparBuffer() {
    while (getchar() != '\n');
}

// =======================================
// CADASTRAR COMPONENTES
// =======================================
void cadastrarComponentes(Componente vetor[], int *tamanho) {

    if (*tamanho >= MAX_COMPONENTES) {
        printf("\nLimite maximo atingido!\n");
        return;
    }

    printf("\nDigite o nome do componente: ");
    fgets(vetor[*tamanho].nome, 30, stdin);
    vetor[*tamanho].nome[strcspn(vetor[*tamanho].nome, "\n")] = '\0';

    printf("Digite o tipo do componente: ");
    fgets(vetor[*tamanho].tipo, 20, stdin);
    vetor[*tamanho].tipo[strcspn(vetor[*tamanho].tipo, "\n")] = '\0';

    printf("Digite a prioridade (1 a 10): ");
    scanf("%d", &vetor[*tamanho].prioridade);

    limparBuffer();

    (*tamanho)++;

    ordenadoPorNome = false;

    printf("\nComponente cadastrado com sucesso!\n");
}

// =======================================
// MOSTRAR COMPONENTES
// =======================================
void mostrarComponentes(Componente vetor[], int tamanho) {

    int i;

    printf("\n========= COMPONENTES =========\n");

    if (tamanho == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    printf("%-25s %-20s %-10s\n",
           "NOME",
           "TIPO",
           "PRIORIDADE");

    printf("----------------------------------------------------------\n");

    for (i = 0; i < tamanho; i++) {

        printf("%-25s %-20s %-10d\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].prioridade);
    }
}

// =======================================
// BUBBLE SORT POR NOME
// =======================================
void bubbleSortNome(Componente vetor[], int tamanho) {

    int i, j;
    Componente temp;

    comparacoesBubble = 0;

    for (i = 0; i < tamanho - 1; i++) {

        for (j = 0; j < tamanho - i - 1; j++) {

            comparacoesBubble++;

            if (strcmp(vetor[j].nome,
                       vetor[j + 1].nome) > 0) {

                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    ordenadoPorNome = true;
}

// =======================================
// INSERTION SORT POR TIPO
// =======================================
void insertionSortTipo(Componente vetor[], int tamanho) {

    int i, j;

    Componente chave;

    comparacoesInsertion = 0;

    for (i = 1; i < tamanho; i++) {

        chave = vetor[i];
        j = i - 1;

        while (j >= 0 &&
               strcmp(vetor[j].tipo, chave.tipo) > 0) {

            comparacoesInsertion++;

            vetor[j + 1] = vetor[j];
            j--;
        }

        comparacoesInsertion++;

        vetor[j + 1] = chave;
    }

    ordenadoPorNome = false;
}

// =======================================
// SELECTION SORT POR PRIORIDADE
// =======================================
void selectionSortPrioridade(Componente vetor[], int tamanho) {

    int i, j, menor;
    Componente temp;

    comparacoesSelection = 0;

    for (i = 0; i < tamanho - 1; i++) {

        menor = i;

        for (j = i + 1; j < tamanho; j++) {

            comparacoesSelection++;

            if (vetor[j].prioridade <
                vetor[menor].prioridade) {

                menor = j;
            }
        }

        temp = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = temp;
    }

    ordenadoPorNome = false;
}

// =======================================
// BUSCA BINÁRIA POR NOME
// =======================================
int buscaBinariaPorNome(Componente vetor[],
                        int tamanho,
                        char nomeBusca[]) {

    int inicio = 0;
    int fim = tamanho - 1;
    int meio;
    int resultado;

    comparacoesBusca = 0;

    while (inicio <= fim) {

        comparacoesBusca++;

        meio = (inicio + fim) / 2;

        resultado = strcmp(vetor[meio].nome,
                           nomeBusca);

        if (resultado == 0) {
            return meio;
        }

        if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

// =======================================
// MEDIR TEMPO DE EXECUÇÃO
// =======================================
void medirTempo(void (*algoritmo)(Componente[], int),
                Componente vetor[],
                int tamanho) {

    clock_t inicio, fim;

    double tempo;

    inicio = clock();

    algoritmo(vetor, tamanho);

    fim = clock();

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao: %.6f segundos\n",
           tempo);
}

// =======================================
// MENU PRINCIPAL
// =======================================
int main() {

    Componente componentes[MAX_COMPONENTES];

    int opcao;

    char nomeBusca[30];

    int resultadoBusca;

    do {

        printf("\n====================================\n");
        printf("   FREE FIRE - NIVEL MESTRE\n");
        printf("====================================\n");

        printf("1 - Cadastrar componente\n");
        printf("2 - Mostrar componentes\n");
        printf("3 - Ordenar por NOME (Bubble Sort)\n");
        printf("4 - Ordenar por TIPO (Insertion Sort)\n");
        printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6 - Busca Binaria por nome\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        limparBuffer();

        switch (opcao) {

            case 1:

                cadastrarComponentes(componentes,
                                     &totalComponentes);

                break;

            case 2:

                mostrarComponentes(componentes,
                                   totalComponentes);

                break;

            case 3:

                medirTempo(bubbleSortNome,
                           componentes,
                           totalComponentes);

                printf("\nComponentes ordenados por nome!\n");
                printf("Comparacoes: %d\n",
                       comparacoesBubble);

                mostrarComponentes(componentes,
                                   totalComponentes);

                break;

            case 4:

                medirTempo(insertionSortTipo,
                           componentes,
                           totalComponentes);

                printf("\nComponentes ordenados por tipo!\n");
                printf("Comparacoes: %d\n",
                       comparacoesInsertion);

                mostrarComponentes(componentes,
                                   totalComponentes);

                break;

            case 5:

                medirTempo(selectionSortPrioridade,
                           componentes,
                           totalComponentes);

                printf("\nComponentes ordenados por prioridade!\n");
                printf("Comparacoes: %d\n",
                       comparacoesSelection);

                mostrarComponentes(componentes,
                                   totalComponentes);

                break;

            case 6:

                if (!ordenadoPorNome) {

                    printf("\nERRO: o vetor precisa estar ");
                    printf("ordenado por NOME ");
                    printf("antes da busca binaria.\n");

                    break;
                }

                printf("\nDigite o nome do componente: ");

                fgets(nomeBusca, 30, stdin);

                nomeBusca[strcspn(nomeBusca,
                                  "\n")] = '\0';

                resultadoBusca =
                    buscaBinariaPorNome(componentes,
                                        totalComponentes,
                                        nomeBusca);

                if (resultadoBusca != -1) {

                    printf("\n===== COMPONENTE ENCONTRADO =====\n");

                    printf("Nome: %s\n",
                           componentes[resultadoBusca].nome);

                    printf("Tipo: %s\n",
                           componentes[resultadoBusca].tipo);

                    printf("Prioridade: %d\n",
                           componentes[resultadoBusca].prioridade);

                    printf("Comparacoes: %d\n",
                           comparacoesBusca);

                } else {

                    printf("\nComponente nao encontrado.\n");

                    printf("Comparacoes: %d\n",
                           comparacoesBusca);
                }

                break;

            case 0:

                printf("\nEncerrando sistema...\n");

                break;

            default:

                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}