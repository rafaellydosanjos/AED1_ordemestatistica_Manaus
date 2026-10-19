#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id_sensor;
    char data[15];
    float temperatura_c;
    int umidade_porcentagem;
    float nivel_pm25;
} Medicao;

// 1. SUA PRIMEIRA FUNÇÃO (Que lê o arquivo)
Medicao* ler_dados_csv(const char* nome_arquivo, int* total_lido) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) 
    return NULL;

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

// 2. A NOVA FUNÇÃO (Abordagem A - Bubble Sort)
void bubble_sort_pm25(Medicao* vetor, int n, long long* comparacoes) {
    *comparacoes = 0;
    int i, j;
    Medicao temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++; // Isso aqui é o que sua dupla precisa para o relatório!
            if (vetor[j].nivel_pm25 > vetor[j+1].nivel_pm25) {
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

// 3. O CHEFE (A função main que executa tudo)
int main() {
    int total_registros = 0;
    
    // Manda ler o arquivo
    Medicao* dados = ler_dados_csv("dados_clima_manaus.csv", &total_registros);

    if (dados != NULL) {
        long long comparacoes_A = 0;
        
        printf("Arquivo lido. Total de registros: %d\n", total_registros);
        printf("Iniciando a ordenacao da Abordagem A (Isso pode demorar alguns segundos)...\n");
        
        // Manda executar a Abordagem A
        bubble_sort_pm25(dados, total_registros, &comparacoes_A);
        
        printf("\n--- RESULTADO PARA A SUA DUPLA ---\n");
        printf("Para N = %d, a Abordagem A fez %lld comparacoes.\n", total_registros, comparacoes_A);
        
        free(dados); 
    }
    return 0;
}