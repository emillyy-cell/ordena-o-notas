/*
 * Ordenacao de notas da turma - Bubble Sort e Quick Sort
 *
 * Situacao: no fim do bimestre o professor tem as notas da turma
 * anotadas na ordem da chamada. Para saber quem ficou abaixo da media,
 * quem precisa de recuperacao e quem tirou as maiores notas, fica muito
 * mais facil olhar a lista ordenada da menor para a maior nota.
 *
 * O programa ordena os mesmos dados de dois jeitos diferentes
 * (Bubble Sort e Quick Sort) e mostra quantas comparacoes e trocas
 * cada um fez, para dar pra comparar os dois.
 *
 * Os nomes e as notas ficam em dois vetores separados (vetores paralelos):
 * o aluno da posicao i do vetor "nomes" tem a nota da posicao i do
 * vetor "notas". Por isso, sempre que uma nota troca de lugar, o nome
 * tambem precisa trocar, senao a nota vai parar no aluno errado.
 */

#include <stdio.h>
#include <string.h>

#define QTD_ALUNOS 12
#define TAM_NOME 30
#define MEDIA 6.0

/* contadores usados para comparar os dois algoritmos */
int comparacoes = 0;
int trocas = 0;

/* ------------------------------------------------------------------ */
/* Funcoes de apoio                                                    */
/* ------------------------------------------------------------------ */

void mostrarTurma(char nomes[][TAM_NOME], float notas[], int n) {
    printf("  %-3s %-22s %s\n", "N", "Aluno", "Nota");
    printf("  ---------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("  %-3d %-22s %5.1f", i + 1, nomes[i], notas[i]);
        if (notas[i] < MEDIA) {
            printf("  (recuperacao)");
        }
        printf("\n");
    }
}

/* copia os dados originais para nao estragar a lista da chamada */
void copiarDados(char origemNomes[][TAM_NOME], float origemNotas[],
                 char destNomes[][TAM_NOME], float destNotas[], int n) {
    for (int i = 0; i < n; i++) {
        strcpy(destNomes[i], origemNomes[i]);
        destNotas[i] = origemNotas[i];
    }
}

/*
 * Troca dois alunos de lugar.
 * A nota e trocada com uma variavel temporaria (igual vimos em aula:
 * temp = a; a = b; b = temp;). Com o nome e a mesma ideia, so que
 * como e texto precisa usar strcpy em vez do sinal de igual.
 */
void trocarAlunos(char nomes[][TAM_NOME], float notas[], int a, int b) {
    float tempNota = notas[a];
    notas[a] = notas[b];
    notas[b] = tempNota;

    char tempNome[TAM_NOME];
    strcpy(tempNome, nomes[a]);
    strcpy(nomes[a], nomes[b]);
    strcpy(nomes[b], tempNome);

    trocas++;
}

/* ------------------------------------------------------------------ */
/* BUBBLE SORT                                                         */
/* ------------------------------------------------------------------ */
/*
 * Ideia: percorrer o vetor comparando cada nota com a vizinha da direita.
 * Se a da esquerda for maior, as duas trocam de lugar.
 *
 * Ao final de cada passada a maior nota que ainda estava fora do lugar
 * "sobe" ate o final do vetor (por isso o nome bolha). Entao a cada
 * passada o for de dentro pode ir uma posicao a menos, ja que o final
 * do vetor ja esta arrumado.
 *
 * Exemplo com 7.5, 4.0, 9.0:
 *   7.5 > 4.0 -> troca -> 4.0, 7.5, 9.0
 *   7.5 > 9.0 ? nao    -> fica igual
 *   o 9.0 ja esta no final, que e o lugar dele.
 */
void bubbleSort(char nomes[][TAM_NOME], float notas[], int n) {
    for (int i = 0; i < n - 1; i++) {          /* cada volta e uma passada */
        for (int j = 0; j < n - 1 - i; j++) {  /* compara os vizinhos */
            comparacoes++;
            if (notas[j] > notas[j + 1]) {
                trocarAlunos(nomes, notas, j, j + 1);
            }
        }
    }
}

/* ------------------------------------------------------------------ */
/* QUICK SORT                                                          */
/* ------------------------------------------------------------------ */
/*
 * Usa a estrategia de dividir para conquistar:
 *   1. escolhe um pivo (aqui e sempre o ultimo elemento do trecho);
 *   2. passa as notas menores ou iguais ao pivo para a esquerda;
 *   3. coloca o pivo logo depois delas, que e a posicao certa dele;
 *   4. repete a mesma coisa no pedaco da esquerda e no da direita.
 *
 * O passo 4 e feito com recursividade: a funcao quickSort chama ela
 * mesma para os dois pedacos. Ela para quando o pedaco tem 0 ou 1
 * elemento (inicio >= fim), porque ai nao tem mais nada para ordenar.
 */

/*
 * Particionamento de Lomuto.
 * i marca onde termina a parte das notas menores que o pivo.
 * j percorre o trecho. Quando j acha uma nota <= pivo, o i anda
 * uma casa e essa nota vai para a posicao i.
 * No final o pivo vai para i + 1 e a funcao devolve essa posicao.
 */
int particionar(char nomes[][TAM_NOME], float notas[], int inicio, int fim) {
    float pivo = notas[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        comparacoes++;
        if (notas[j] <= pivo) {
            i++;
            if (i != j) {   /* se i == j a nota ja esta no lugar */
                trocarAlunos(nomes, notas, i, j);
            }
        }
    }

    /* pivo vai para a posicao definitiva */
    if (i + 1 != fim) {
        trocarAlunos(nomes, notas, i + 1, fim);
    }
    return i + 1;
}

void quickSort(char nomes[][TAM_NOME], float notas[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(nomes, notas, inicio, fim);

        quickSort(nomes, notas, inicio, p - 1);  /* lado esquerdo do pivo */
        quickSort(nomes, notas, p + 1, fim);     /* lado direito do pivo */
    }
}

/* ------------------------------------------------------------------ */
/* Programa principal                                                  */
/* ------------------------------------------------------------------ */

void executarBubble(char nomes[][TAM_NOME], float notas[]) {
    char copiaNomes[QTD_ALUNOS][TAM_NOME];
    float copiaNotas[QTD_ALUNOS];

    copiarDados(nomes, notas, copiaNomes, copiaNotas, QTD_ALUNOS);
    comparacoes = 0;
    trocas = 0;

    bubbleSort(copiaNomes, copiaNotas, QTD_ALUNOS);

    printf("\n>> Turma ordenada com BUBBLE SORT:\n\n");
    mostrarTurma(copiaNomes, copiaNotas, QTD_ALUNOS);
    printf("\n  Comparacoes: %d | Trocas: %d\n", comparacoes, trocas);
}

void executarQuick(char nomes[][TAM_NOME], float notas[]) {
    char copiaNomes[QTD_ALUNOS][TAM_NOME];
    float copiaNotas[QTD_ALUNOS];

    copiarDados(nomes, notas, copiaNomes, copiaNotas, QTD_ALUNOS);
    comparacoes = 0;
    trocas = 0;

    quickSort(copiaNomes, copiaNotas, 0, QTD_ALUNOS - 1);

    printf("\n>> Turma ordenada com QUICK SORT:\n\n");
    mostrarTurma(copiaNomes, copiaNotas, QTD_ALUNOS);
    printf("\n  Comparacoes: %d | Trocas: %d\n", comparacoes, trocas);
}

int main() {
    /* notas na ordem da chamada (fora de ordem de nota) */
    char nomes[QTD_ALUNOS][TAM_NOME] = {
        "Ana Clara", "Bruno", "Carlos Eduardo", "Daniela",
        "Eduardo", "Fernanda", "Gabriel", "Helena",
        "Igor", "Julia", "Lucas", "Mariana"
    };
    float notas[QTD_ALUNOS] = {
        7.5, 4.0, 9.0, 6.5, 3.5, 8.0,
        5.5, 10.0, 6.0, 2.5, 8.5, 7.0
    };

    int opcao;

    printf("=== ORDENACAO DE NOTAS DA TURMA ===\n\n");
    printf("Notas na ordem da chamada (antes de ordenar):\n\n");
    mostrarTurma(nomes, notas, QTD_ALUNOS);

    do {
        printf("\nEscolha o algoritmo:\n");
        printf("  1 - Bubble Sort\n");
        printf("  2 - Quick Sort\n");
        printf("  3 - Os dois (para comparar)\n");
        printf("  0 - Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            break;
        }

        switch (opcao) {
            case 1:
                executarBubble(nomes, notas);
                break;
            case 2:
                executarQuick(nomes, notas);
                break;
            case 3:
                executarBubble(nomes, notas);
                executarQuick(nomes, notas);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida, tente de novo.\n");
        }
    } while (opcao != 0);

    return 0;
}
