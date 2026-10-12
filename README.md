# 🌳 Análise da Qualidade do Ar e Clima de Manaus (Estatísticas de Ordem)

**Universidade Federal do Amazonas (UFAM)**  
**Instituto de Computação (IComp)**  
**Disciplina:** ICC002 - Algoritmos e Estruturas de Dados I  

---

## 📌 Sobre o Projeto
Este projeto tem como objetivo desenvolver um motor de processamento de dados climáticos para o Instituto Ambiental da Amazônia. O sistema processa medições diárias (como Temperatura, Umidade e PM2.5) coletadas durante o "verão amazônico" e o fenômeno do "fumaceiro" em Manaus.

A finalidade central é implementar e comparar três algoritmos distintos de **Estatística de Ordem** para encontrar o *k-ésimo* elemento de um conjunto massivo de dados (com até 10.000 registros), auxiliando na identificação de picos críticos de poluição.

## 👩‍💻 Equipe
* **Desenvolvimento (C):** Rafaelle Barreto dos Anjos
* **Análise e Relatório Técnico:** [Nome da sua Dupla aqui]

## 📂 Estrutura do Repositório
* `src/`: Contém os códigos-fonte em linguagem C (`main.c`).
* `data/`: Contém a base de dados `dados_clima_manaus.csv`.
* `docs/`: Arquivos do relatório técnico em formatação LaTeX/PDF.

## 🚀 Como Compilar e Executar
Certifique-se de ter o compilador GCC instalado (via MinGW ou Linux). 
Abra o terminal na pasta raiz do projeto e execute:

1. **Para compilar:**
   ```bash
   gcc src/main.c -o clima_manaus
