#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id_sensor;
    char data[15];
    float temperatura_c;
    int umidade_porcentagem;
    float nivel_pm25;
} Medicao;

// 1. LÊ O ARQUIVO GIGANTE
Medicao* ler_dados_csv(const char* nome_arquivo, int* total_lido) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) return NULL;

    int capacidade = 1000;
    Medicao* vetor = (Medicao*) malloc(capacidade * sizeof(Medicao));
    *total_lido = 0;
    char linha[200];
    
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (*total_lido >= capacidade) {
            capacidade *= 2;
            vetor = (Medicao*) realloc(vetor, capacidade * sizeof(Medicao));
        }
        sscanf(linha, "%d,%[^,],%f,%d,%f", 
            &vetor[*total_lido].id_sensor, vetor[*total_lido].data,
            &vetor[*total_lido].temperatura_c, &vetor[*total_lido].umidade_porcentagem,
            &vetor[*total_lido].nivel_pm25);
        (*total_lido)++;
    }
    fclose(arquivo);
    return vetor;
}

// --- ABORDAGEM A: BUBBLE SORT ---
void bubble_sort_pm25(Medicao* vetor, int n, long long* comparacoes) {
    *comparacoes = 0;
    int i, j;
    Medicao temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++; 
            if (vetor[j].nivel_pm25 > vetor[j+1].nivel_pm25) {
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

// --- ABORDAGEM B: PARTICIONAMENTO COM PIVÔ ALEATÓRIO ---
void trocar(Medicao* a, Medicao* b) {
    Medicao temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Medicao* vetor, int inicio, int fim, long long* comparacoes) {
    int indice_pivo = inicio + rand() % (fim - inicio + 1);
    trocar(&vetor[indice_pivo], &vetor[fim]); 
    float pivo = vetor[fim].nivel_pm25;
    int i = (inicio - 1);
    for (int j = inicio; j <= fim - 1; j++) {
        (*comparacoes)++;
        if (vetor[j].nivel_pm25 <= pivo) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[i + 1], &vetor[fim]);
    return (i + 1);
}

Medicao quickselect_pm25(Medicao* vetor, int inicio, int fim, int k, long long* comparacoes) {
    if (inicio <= fim) {
        int indice_particao = particionar(vetor, inicio, fim, comparacoes);
        if (indice_particao == k) return vetor[indice_particao];
        else if (indice_particao > k) return quickselect_pm25(vetor, inicio, indice_particao - 1, k, comparacoes);
        else return quickselect_pm25(vetor, indice_particao + 1, fim, k, comparacoes);
    }
    return vetor[inicio];
}

// --- ABORDAGEM C: CONTAGEM COMPARATIVA SEQUENCIAL ---
Medicao contagem_sequencial_pm25(Medicao* vetor, int n, int k, long long* comparacoes) {
    *comparacoes = 0;
    
    for (int i = 0; i < n; i++) {
        float candidato = vetor[i].nivel_pm25;
        int menores = 0;
        int iguais = 0;
        
        // Varre o vetor contando quantos são menores e quantos são iguais ao candidato
        for (int j = 0; j < n; j++) {
            (*comparacoes)++;
            if (vetor[j].nivel_pm25 < candidato) {
                menores++;
            } else if (vetor[j].nivel_pm25 == candidato) {
                iguais++;
            }
        }
        
        // Lógica contra empates (Questão 2 do relatório)
        if (k >= menores && k < (menores + iguais)) {
            return vetor[i];
        }
    }
    return vetor[0];
}

// FUNÇÃO AUXILIAR
void copiar_vetor(Medicao* origem, Medicao* destino, int n) {
    for(int i = 0; i < n; i++) destino[i] = origem[i];
}

// O CHEFE QUE CONTROLA OS TESTES
int main() {
    int total_registros = 0;
    srand(time(NULL)); 
    
    Medicao* dados_originais = ler_dados_csv("dados_clima_manaus.csv", &total_registros);

    if (dados_originais != NULL && total_registros >= 10000) {
        int tamanhos[] = {1000, 5000, 10000};
        
        printf("=== TESTES DE DESEMPENHO (ABORDAGENS A, B e C) ===\n\n");

        for (int i = 0; i < 3; i++) {
            int n = tamanhos[i];
            printf(">>> TESTANDO PARA N = %d <<<\n", n);
            
            Medicao* dados_teste = (Medicao*) malloc(n * sizeof(Medicao));

            // Teste da Abordagem A
            copiar_vetor(dados_originais, dados_teste, n);
            long long comp_A = 0;
            bubble_sort_pm25(dados_teste, n, &comp_A);
            printf("Abordagem A (Bubble Sort)   : %lld comparacoes\n", comp_A);

            // Teste da Abordagem B
            copiar_vetor(dados_originais, dados_teste, n);
            long long comp_B = 0;
            quickselect_pm25(dados_teste, 0, n - 1, n / 2, &comp_B);
            printf("Abordagem B (Quickselect)   : %lld comparacoes\n", comp_B);

            // Teste da Abordagem C (Buscando a mediana k = N/2)
            copiar_vetor(dados_originais, dados_teste, n);
            long long comp_C = 0;
            contagem_sequencial_pm25(dados_teste, n, n / 2, &comp_C);
            printf("Abordagem C (Contagem seq.) : %lld comparacoes\n\n", comp_C);

            free(dados_teste);
        }
        free(dados_originais); 
    }
    return 0;
}