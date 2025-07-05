# 🍲 Sistema de Gerenciamento de Vendas para Restaurantes

Bem-vindo ao Sistema de Gerenciamento de Vendas para Restaurantes! Este é um programa simples em C, desenvolvido para ajudar pequenos restaurantes e negócios de alimentação a gerenciar suas vendas diárias, mensais e anuais. Acompanhe os pedidos dos clientes, calcule os totais e gere relatórios para monitorar o desempenho do seu negócio.

---

## ✨ Funcionalidades

* **Registro de Vendas:** Registre facilmente novas vendas, incluindo nome do cliente, tipo de venda (refeição, quentinha ou bebida), peso para refeições e quantidade de bebidas.
* **Cálculo Automático:** Os valores das vendas são calculados automaticamente com base em preços predefinidos para refeições (por peso), quentinhas (com embalagem) e bebidas.
* **Relatórios Diários:** Visualize um detalhamento de todas as vendas de um dia específico, incluindo nomes dos clientes, tipos de venda, pesos e totais de vendas individuais, além da receita total do dia.
* **Relatórios Mensais:** Obtenha um resumo de todas as vendas de um mês escolhido, mostrando cada transação e o total acumulado para o mês inteiro.
* **Análise de Desempenho Anual:** Veja os totais de vendas mensais de todo o ano, ordenados do mês de maior faturamento para o de menor. Isso ajuda a identificar rapidamente os períodos de pico de desempenho.

---

## 🚀 Como Compilar e Executar

Para compilar e executar este programa, você precisará de um compilador C (como o GCC).

1.  **Salve o código:** Salve o código C fornecido como `main.c` (ou qualquer outra extensão `.c`).

2.  **Compile:** Abra seu terminal ou prompt de comando e navegue até o diretório onde você salvou o arquivo. Em seguida, compile o código usando o GCC:

    ```bash
    gcc main.c -o gerenciador_vendas
    ```

3.  **Execute:** Após a compilação bem-sucedida, execute o programa:

    ```bash
    ./gerenciador_vendas
    ```

---

## 🖥️ Como Usar

Assim que o programa estiver em execução, você verá o **menu principal**:

Siga as instruções para realizar a ação desejada:
```markdown
=== MENU ===
1 - Registrar nova venda
2 - Exibir relatório diário
3 - Exibir relatório mensal
4 - Exibir relatório anual ordenado
0 - Sair
Escolha uma opção:
```

* **1 - Registrar nova venda:**
    * Digite o **dia** e o **mês** da venda.
    * Forneça o **nome do cliente**.
    * Escolha o **tipo de venda** (0 para Refeição, 1 para Quentinha, 2 para Bebida).
    * Se for "Refeição", digite o **peso em quilogramas**.
    * Digite a **quantidade de bebidas** (mesmo que seja 0).

* **2 - Exibir relatório diário:**
    * Digite o **dia** e o **mês** que deseja consultar.

* **3 - Exibir relatório mensal:**
    * Digite o **mês** (1-12) que deseja consultar.

* **4 - Exibir relatório anual ordenado:**
    * Esta opção exibirá automaticamente todos os meses com vendas, ordenados pelo total de suas receitas.

* **0 - Sair:** Encerra a aplicação.

---

## 💡 Visão Geral do Código

O programa é estruturado com várias funções para gerenciar diferentes aspectos do sistema de vendas:

* **`valor_da_venda_calculo(Venda *v)`**: Calcula o valor total de uma única venda com base em seu tipo e quantidades.
* **`registrar_venda(VendasDia *diaSelecionado)`**: Lida com a entrada de dados do usuário para uma nova venda e a adiciona ao registro de vendas para um dia específico.
* **`relatorioDiario(VendasDia *diaSelecionado)`**: Imprime um relatório detalhado de todas as vendas de um determinado dia.
* **`relatorioMensal(VendasDia historico[], int totalDias)`**: Gera um relatório resumido para um mês selecionado.
* **`relatorioAnualOrdenado(VendasDia historico[], int totalDias)`**: Calcula e exibe os dados de vendas anuais, ordenados pelos totais mensais.
* **`main()`**: A função principal que executa o programa, apresentando o menu e chamando outras funções com base na entrada do usuário.

---

## ⚙️ Configuração

O programa inclui várias constantes predefinidas para precificação:

* `PRECO_QUENTINHA`: Preço de uma quentinha (R$ 20.0)
* `PRECO_BEBIDA`: Preço por bebida (R$ 7.0)
* `PRECO_EMBALAGEM`: Custo da embalagem para quentinhas (R$ 0.50)
* `PRECO_POR_KG`: Preço por quilograma para refeições (R$ 60.0)
* `MAX_VENDAS_DIA`: Número máximo de registros de vendas por dia (100)

Você pode modificar esses valores `#define` no código-fonte para ajustar os preços ou limites conforme necessário.

---

## 🤝 Contribuição

Sinta-se à vontade para "forkar" este repositório e contribuir! Sejam correções de bugs, novas funcionalidades ou melhorias no código existente, todas as contribuições são bem-vindas.

---

Aproveite para gerenciar as vendas do seu restaurante!