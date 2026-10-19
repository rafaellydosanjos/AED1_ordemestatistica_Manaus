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
* [Cole aqui o valor e a data que apareceram no terminal]

**2. Limiar Crítico - Percentil 90 (k = 9000):**
* [Cole aqui o valor e a data que apareceram no terminal]

**3. Os 10 Dias Mais Secos:**
* [Cole aqui a lista dos 10 dias que o terminal imprimiu]
