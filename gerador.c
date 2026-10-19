#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *arquivo = fopen("dados_clima_manaus.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    // Escreve o cabeçalho
    fprintf(arquivo, "ID_Sensor,Data,Temperatura_C,Umidade_Porcentagem,Nivel_PM25\n");

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("Gerando 12.000 registros climaticos simulados...\n");

    for (int i = 0; i < 12000; i++) {
        int id = 100 + (rand() % 900); // ID entre 100 e 999
        int dia = 1 + (rand() % 30);
        int mes = 8 + (rand() % 3); // Meses 8, 9 ou 10 (Agosto a Outubro)
        
        // Simula os dados do fumaceiro
        float temp = 28.0 + ((rand() % 120) / 10.0); // 28.0 a 40.0 °C
        int umidade = 20 + (rand() % 60);            // 20% a 80%
        float pm25 = 10.0 + ((rand() % 1400) / 10.0); // 10.0 a 150.0 (Poluição)

        fprintf(arquivo, "%d,2026-%02d-%02d,%.1f,%d,%.1f\n", id, mes, dia, temp, umidade, pm25);
    }

    fclose(arquivo);
    printf("Sucesso! O arquivo 'dados_clima_manaus.csv' agora tem 12.000 linhas de dados.\n");
    return 0;
}