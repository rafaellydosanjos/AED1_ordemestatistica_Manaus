#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Autora: Rafaelly dos Anjos
// Disciplina: Algoritmos e Estruturas de Dados I

typedef struct {
    int id_sensor;
    char data[15];
    float temperatura_c;
    int umidade_porcentagem;
    float nivel_pm25;
} Medicao;

// 1. FUNÇÃO DE LEITURA
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

// 2. FUNÇÃO DA ABORDAGEM A (Bubble Sort)
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

// 3. NOVA FUNÇÃO: Ajuda a copiar os dados para cada teste ser justo
void copiar_vetor(Medicao* origem, Medicao* destino, int n) {
    for(int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

// 4. O CHEFE (Testando a Abordagem A para 1k, 5k e 10k)
int main() {
    int total_registros = 0;
    
    // Lê a base de dados
    Medicao* dados_originais = ler_dados_csv("dados_clima_manaus.csv", &total_registros);

    if (dados_originais != NULL) {
        printf("Arquivo lido. Total de registros: %d\n\n", total_registros);

        // Trava de segurança: Verifica se o arquivo tem pelo menos 10.000 linhas
        if (total_registros < 10000) {
            printf("AVISO: O seu arquivo tem apenas %d linhas!\n", total_registros);
            printf("Para testar 10.000, voce precisa colocar o arquivo CSV original completo na pasta.\n");
            free(dados_originais);
            return 1;
        }

        int tamanhos[] = {1000, 5000, 10000};
        
        printf("=== TESTES DA ABORDAGEM A (Bubble Sort) ===\n");

        for (int i = 0; i < 3; i++) {
            int n = tamanhos[i];
            
            // Separa uma fatia exata (1000, 5000 ou 10000)
            Medicao* dados_teste = (Medicao*) malloc(n * sizeof(Medicao));
            copiar_vetor(dados_originais, dados_teste, n);

            long long comp_A = 0;
            printf("Ordenando N = %d (Aguarde, isso pode demorar)...\n", n);
            bubble_sort_pm25(dados_teste, n, &comp_A);
            
            // Imprime o resultado final para você copiar para o README
            printf("-> RESULTADO: %lld comparacoes\n\n", comp_A);

            free(dados_teste);
        }

        free(dados_originais); 
    }
    return 0;
}