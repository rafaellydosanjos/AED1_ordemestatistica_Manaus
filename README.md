## 🎯 Status de Desenvolvimento (Checklist)
- [x] Configuração da `struct` e leitura dinâmica do CSV (via `malloc`/`realloc`).
- [x] **Abordagem A:** Ordenação Completa (Bubble Sort).
- [x] **Abordagem B:** Divisão e Conquista (Particionamento com pivô aleatório).
- [x] **Abordagem C:** Contagem Comparativa Sequencial (Tratamento de empates com `<=`).
- [x] **Consultas:** Mediana Exata de PM2.5 ($k = N/2$).
- [ ] **Consultas:** Limiar Crítico (Percentil 90) de PM2.5.
- [ ] **Consultas:** M dias mais secos (menor umidade).

---

| Tamanho da Entrada (N) | Abordagem A (Bubble Sort) | Abordagem B | Abordagem C |
| :--- | :--- | :--- | :--- |
| **N = 1.000** | *499500* | *2597* | 50000 |
| **N = 5.000** | *12497500* | *21118* | 1530000 |
| **N = 10.000** | *49995000* | *39892* | 3080000 |

---

## 📊 Resultados das Consultas Obrigatórias

**1. Mediana Exata de PM2.5 (k = 5000):**
* Valor Central: 79.9 ug/m3 (Dia 2026-09-21)

**2. Limiar Crítico - Percentil 90 (k = 9000):**
* Valor de Alerta: 135.8 ug/m3 (Dia 2026-10-30)

**3. Os 10 Dias Mais Secos:**
* 1. Data: 2026-10-26 | Umidade: 20% | Temp: 31.4 C
2. Data: 2026-09-15 | Umidade: 20% | Temp: 39.2 C
3. Data: 2026-08-09 | Umidade: 20% | Temp: 39.4 C
4. Data: 2026-08-07 | Umidade: 20% | Temp: 37.8 C
5. Data: 2026-08-19 | Umidade: 20% | Temp: 38.5 C
6. Data: 2026-09-11 | Umidade: 20% | Temp: 39.2 C
7. Data: 2026-08-07 | Umidade: 20% | Temp: 35.8 C
8. Data: 2026-10-15 | Umidade: 20% | Temp: 35.6 C
9. Data: 2026-08-17 | Umidade: 20% | Temp: 33.1 C
10. Data: 2026-08-06 | Umidade: 20% | Temp: 39.2 C
