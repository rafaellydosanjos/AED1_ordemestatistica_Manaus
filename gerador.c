#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *arquivo = fopen("dados_clima_manaus.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "ID_Sensor,Data,Temperatura_C,Umidade_Porcentagem,Nivel_PM25\n");
    srand(time(NULL));

    printf("Gerando exatamente 10.000 registros climaticos...\n");

    // Limite máximo alterado para 10000 conforme instrução do professor
    for (int i = 0; i < 10000; i++) {
        int id = 100 + (rand() % 900); 
        int dia = 1 + (rand() % 30);
        int mes = 8 + (rand() % 3); 
        
        float temp = 28.0 + ((rand() % 120) / 10.0); 
        int umidade = 20 + (rand() % 60);            
        float pm25 = 10.0 + ((rand() % 1400) / 10.0); 

        fprintf(arquivo, "%d,2026-%02d-%02d,%.1f,%d,%.1f\n", id, mes, dia, temp, umidade, pm25);
    }

    fclose(arquivo);
    printf("Sucesso! O arquivo 'dados_clima_manaus.csv' agora tem o limite maximo de 10.000 linhas.\n");
    return 0;
}