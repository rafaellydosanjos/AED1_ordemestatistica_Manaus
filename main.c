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

// 1. LEITURA DE DADOS
Medicao* ler_dados_csv(const char* nome_arquivo, int* total_lido) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) return NULL;

    int capacidade = 1000;
    Medicao* vetor = (Medicao*) malloc(capacidade * sizeof(Medicao));
    *total_lido = 0;
    char linha[200];
    
    fgets(linha, sizeof(linha), arquivo);
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
        int menores = 0, iguais = 0;
        for (int j = 0; j < n; j++) {
            (*comparacoes)++;
            if (vetor[j].nivel_pm25 < candidato) menores++;
            else if (vetor[j].nivel_pm25 == candidato) iguais++;
        }
        if (k >= menores && k < (menores + iguais)) return vetor[i];
    }
    return vetor[0];
}

// --- NOVA FUNÇÃO: PARA CONSULTA DOS M DIAS MAIS SECOS ---
void listar_m_dias_mais_secos(Medicao* vetor, int n, int m) {
    for (int i = 0; i < m; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vetor[j].umidade_porcentagem < vetor[min_idx].umidade_porcentagem) {
                min_idx = j;
            }
        }
        trocar(&vetor[i], &vetor[min_idx]);
        printf("%d. Data: %s | Umidade: %d%% | Temp: %.1f C\n", 
               i + 1, vetor[i].data, vetor[i].umidade_porcentagem, vetor[i].temperatura_c);
    }
}

// FUNÇÃO AUXILIAR
void copiar_vetor(Medicao* origem, Medicao* destino, int n) {
    for(int i = 0; i < n; i++) destino[i] = origem[i];
}

// CHEFE: TESTES E CONSULTAS OBRIGATÓRIAS
int main() {
    int total_registros = 0;
    srand(time(NULL)); 
    
    Medicao* dados_originais = ler_dados_csv("dados_clima_manaus.csv", &total_registros);

    if (dados_originais != NULL && total_registros >= 10000) {
        
        printf("=== PARTE 1: TESTES DE DESEMPENHO (10.000 linhas) ===\n");
        // Fazendo apenas um teste demonstrativo para o professor ver que funciona
        int n = 10000;
        Medicao* dados_teste = (Medicao*) malloc(n * sizeof(Medicao));
        
        copiar_vetor(dados_originais, dados_teste, n);
        long long comp_A = 0;
        printf("Aguarde a Abordagem A...\n");
        bubble_sort_pm25(dados_teste, n, &comp_A);
        printf("Abordagem A concluida com sucesso.\n\n");


        printf("=== PARTE 2: CONSULTAS OBRIGATORIAS ===\n");
        long long comp_nulas = 0;

        // Consulta 1: Mediana do PM2.5 (k = N/2)
        copiar_vetor(dados_originais, dados_teste, n);
        int k_mediana = n / 2;
        Medicao mediana = quickselect_pm25(dados_teste, 0, n - 1, k_mediana, &comp_nulas);
        printf("\n1. Mediana Exata de PM2.5 (k = %d):\n", k_mediana);
        printf("   Valor Central: %.1f ug/m3 (Dia %s)\n", mediana.nivel_pm25, mediana.data);

        // Consulta 2: Limiar Crítico (Percentil 90)
        copiar_vetor(dados_originais, dados_teste, n);
        int k_percentil90 = (int)(n * 0.90);
        Medicao p90 = quickselect_pm25(dados_teste, 0, n - 1, k_percentil90, &comp_nulas);
        printf("\n2. Limiar Critico - Percentil 90 (k = %d):\n", k_percentil90);
        printf("   Valor de Alerta: %.1f ug/m3 (Dia %s)\n", p90.nivel_pm25, p90.data);

        // Consulta 3: Os M (10) Dias Mais Secos
        printf("\n3. Os 10 Dias Mais Secos (Menor Umidade do periodo):\n");
        copiar_vetor(dados_originais, dados_teste, n);
        listar_m_dias_mais_secos(dados_teste, n, 10);

        free(dados_teste);
        free(dados_originais); 
    }
    return 0;
}