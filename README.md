| Tamanho da Entrada (N) | Abordagem A (Bubble Sort) | Abordagem B | Abordagem C |
| :--- | :--- | :--- | :--- |
| **N = 1.000** | *499500* | *2597* | 50000 |
| **N = 5.000** | *12497500* | *21118* | 1530000 |
| **N = 10.000** | *49995000* | *39892* | 3080000 |

## 🎯 Status de Desenvolvimento (Checklist)
- [x] Configuração da `struct` e leitura dinâmica do CSV (via `malloc`/`realloc`).
- [x] **Abordagem A:** Ordenação Completa (Bubble Sort).
- [x] **Abordagem B:** Divisão e Conquista (Particionamento com pivô aleatório).
- [x] **Abordagem C:** Contagem Comparativa Sequencial (Tratamento de empates com `<=`).
- [ ] **Consultas:** Mediana Exata de PM2.5 ($k = N/2$).
- [ ] **Consultas:** Limiar Crítico (Percentil 90) de PM2.5.
- [ ] **Consultas:** M dias mais secos (menor umidade).
