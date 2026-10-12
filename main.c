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

Medicao* ler_dados_csv(const char* nome_arquivo, int* total_lido) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL; // Se o arquivo não existir, o programa para aqui
    }

    // Começamos alocando espaço para 1000 medições
    int capacidade = 1000;
    Medicao* vetor = (Medicao*) malloc(capacidade * sizeof(Medicao));
    *total_lido = 0;

    char linha[200]; // Uma string grande o suficiente para ler uma linha do CSV
    
    // Ler a primeira linha (cabeçalho) e ignorá-la (não queremos processar a palavra "Temperatura")
    fgets(linha, sizeof(linha), arquivo);

    // Ler as linhas de dados, uma por vez
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Se já lemos mais do que a capacidade atual, dobramos o espaço
        if (*total_lido >= capacidade) {
            capacidade *= 2;
            vetor = (Medicao*) realloc(vetor, capacidade * sizeof(Medicao));
        }
        
        // Quebrando a linha nas variáveis da struct. O "%[^,]" significa "leia até encontrar uma vírgula"
        sscanf(linha, "%d,%[^,],%f,%d,%f", 
            &vetor[*total_lido].id_sensor,
            vetor[*total_lido].data,
            &vetor[*total_lido].temperatura_c,
            &vetor[*total_lido].umidade_porcentagem,
            &vetor[*total_lido].nivel_pm25);
            
        (*total_lido)++; // Aumenta a contagem de registros lidos
    }

    fclose(arquivo);
    return vetor;
}

int main() {
    int total_registros = 0;
    
    // Chama a função passando o nome do arquivo que está na mesma pasta
    Medicao* dados = ler_dados_csv("dados_clima_manaus.csv", &total_registros);

    if (dados != NULL) {
        printf("Sucesso! O arquivo foi lido.\n");
        printf("Total de registros carregados na memoria: %d\n", total_registros);
        
        // Vamos imprimir os 5 primeiros só para checar se a leitura ficou certinha
        printf("\n--- Teste de Leitura (Primeiros 5 registros) ---\n");
        for(int i = 0; i < 5 && i < total_registros; i++) {
            printf("ID: %d | Data: %s | Temp: %.1f | Umid: %d | PM2.5: %.1f\n", 
                dados[i].id_sensor, dados[i].data, dados[i].temperatura_c, 
                dados[i].umidade_porcentagem, dados[i].nivel_pm25);
        }

        // Muito importante em C: liberar a memória no final!
        free(dados); 
    }

    return 0;
}