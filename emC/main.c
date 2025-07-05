#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PRECO_QUENTINHA 20.0
#define PRECO_BEBIDA 7.0
#define PRECO_EMBALAGEM 0.50
#define PRECO_POR_KG 60
#define MAX_VENDAS_DIA 100

enum TipoVenda {
    REFEICAO,
    QUENTINHA,
    BEBIDA
};

typedef struct Venda {
    char nome_cliente[64];
    int tipo_venda;          
    float peso_refeicao;     
    int quantidade_bebida;   
    float valor_total_venda; 
    int dia;
    int mes;
} Venda;

typedef struct VendasDia {
    Venda vendas[MAX_VENDAS_DIA];
    int contador_vendas;
    int dia;
    int mes;
} VendasDia;

// Função para calcular valor da venda
float valor_da_venda_calculo(Venda *v) {
    if (v->tipo_venda == REFEICAO) {
        v->valor_total_venda = v->peso_refeicao * PRECO_POR_KG;
    } else if (v->tipo_venda == QUENTINHA) {
        v->valor_total_venda = PRECO_QUENTINHA + PRECO_EMBALAGEM;
    } else if (v->tipo_venda == BEBIDA) {
        v->valor_total_venda = v->quantidade_bebida * PRECO_BEBIDA;
        return v->valor_total_venda;
    }

    if (v->quantidade_bebida > 0) {
        v->valor_total_venda += v->quantidade_bebida * PRECO_BEBIDA;
    }
    
    return v->valor_total_venda;
}

// Função para registrar uma venda em um VendasDia específico
void registrar_venda(VendasDia *diaSelecionado) {
    if (diaSelecionado->contador_vendas >= MAX_VENDAS_DIA) {
        printf("Limite máximo de vendas neste dia atingido!\n");
        return;
    }

    Venda nova;
    printf("Nome do cliente: ");
    fgets(nova.nome_cliente, sizeof(nova.nome_cliente), stdin);
    nova.nome_cliente[strcspn(nova.nome_cliente, "\n")] = '\0';

    printf("Tipo da venda (0=Refeição, 1=Quentinha, 2=Bebida): ");
    scanf("%d", &nova.tipo_venda);
    getchar();

    if (nova.tipo_venda == REFEICAO) {
        printf("Peso da refeição (kg): ");
        scanf("%f", &nova.peso_refeicao);
        getchar();
    } else {
        nova.peso_refeicao = 0;
    }

    printf("Quantidade de bebidas: ");
    scanf("%d", &nova.quantidade_bebida);
    getchar();

    nova.dia = diaSelecionado->dia;
    nova.mes = diaSelecionado->mes;

    valor_da_venda_calculo(&nova);
    diaSelecionado->vendas[diaSelecionado->contador_vendas++] = nova;

    printf("|===-- Venda registrada com sucesso! --===|\n");
}

// Função para exibir relatório diário
void relatorioDiario(VendasDia *diaSelecionado) {
    float valor_total_vendido_dia = 0;

    printf("|--- Relatório do Dia %02d/%02d ---|\n", diaSelecionado->dia, diaSelecionado->mes);
    for (int i = 0; i < diaSelecionado->contador_vendas; i++) {
        Venda *v = &diaSelecionado->vendas[i];
        printf("|==========------------------------==========|\n");
        printf("|== Nome do cliente: %s\n", v->nome_cliente);
        printf("|== Tipo de venda: ");
        if (v->tipo_venda == REFEICAO)
            printf("Refeição\n");
        else if (v->tipo_venda == QUENTINHA)
            printf("Quentinha\n");
        else
            printf("Bebida\n");

        printf("|== Peso: ");
        if (v->tipo_venda == REFEICAO)
            printf("%.2f Kg\n", v->peso_refeicao);
        else
            printf("0 Kg\n");

        printf("|== Valor Total da Venda: R$%.2f\n", v->valor_total_venda);
        printf("|==========------------------------==========|\n");

        valor_total_vendido_dia += v->valor_total_venda;
    }

    printf("Valor total vendido neste dia: R$ %.2f\n", valor_total_vendido_dia);
}

// Função para relatório mensal
void relatorioMensal(VendasDia historico[], int totalDias) {
    int mes;
    float totalMes = 0;

    printf("Digite o mês que deseja consultar (1 a 12): ");
    scanf("%d", &mes);
    getchar();

    printf("|--- Relatório Mensal ---|\n");

    for (int i = 0; i < totalDias; i++) {
        if (historico[i].mes == mes) {
            VendasDia *d = &historico[i];
            printf("\n|--- Dia %02d/%02d ---|\n", d->dia, d->mes);
            for (int j = 0; j < d->contador_vendas; j++) {
                Venda *v = &d->vendas[j];
                printf("Cliente: %s | Valor: R$ %.2f\n", v->nome_cliente, v->valor_total_venda);
                totalMes += v->valor_total_venda;
            }
        }
    }
    printf("\nTotal vendido no mês: R$ %.2f\n", totalMes);
}

// Função para mostrar o total vendido em cada mês em ordem decrescente
void relatorioAnualOrdenado(VendasDia historico[], int totalDias) {
    float totaisPorMes[12] = {0};

    // 1. Somar valores por mês
    for (int i = 0; i < totalDias; i++) {
        VendasDia *d = &historico[i];
        for (int j = 0; j < d->contador_vendas; j++) {
            totaisPorMes[d->mes - 1] += d->vendas[j].valor_total_venda;
        }
    }

    // 2. Criar estrutura auxiliar para ordenar
    typedef struct {
        int mes;
        float total;
    } MesTotal;

    MesTotal listaMeses[12];
    for (int i = 0; i < 12; i++) {
        listaMeses[i].mes = i + 1;
        listaMeses[i].total = totaisPorMes[i];
    }

    // 3. Ordenar em ordem decrescente (Bubble Sort)
    for (int i = 0; i < 12 - 1; i++) {
        for (int j = 0; j < 12 - i - 1; j++) {
            if (listaMeses[j].total < listaMeses[j + 1].total) {
                MesTotal temp = listaMeses[j];
                listaMeses[j] = listaMeses[j + 1];
                listaMeses[j + 1] = temp;
            }
        }
    }

    // 4. Exibir resultado
    printf("\n|--- Relatório Anual (Mês com maior venda primeiro) ---|\n");
    for (int i = 0; i < 12; i++) {
        if (listaMeses[i].total > 0) {
            printf("Mês %02d | Total vendido: R$ %.2f\n", listaMeses[i].mes, listaMeses[i].total);
        }
    }
}

int main() {
    VendasDia historico[366];
    int totalDias = 0;

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Registrar nova venda\n");
        printf("2 - Exibir relatório diário\n");
        printf("3 - Exibir relatório mensal\n");
        printf("4 - Exibir relatório anual ordenado\n"); 
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                int dia, mes;
                printf("Dia da venda: ");
                scanf("%d", &dia);
                getchar();
                printf("Mês da venda: ");
                scanf("%d", &mes);
                getchar();

                // Verifica se esse dia já existe no histórico
                VendasDia *diaSelecionado = NULL;
                for (int i = 0; i < totalDias; i++) {
                    if (historico[i].dia == dia && historico[i].mes == mes) {
                        diaSelecionado = &historico[i];
                        break;
                    }
                }

                // Se não encontrou, cria novo
                if (diaSelecionado == NULL) {
                    historico[totalDias].dia = dia;
                    historico[totalDias].mes = mes;
                    historico[totalDias].contador_vendas = 0;
                    diaSelecionado = &historico[totalDias];
                    totalDias++;
                }

                registrar_venda(diaSelecionado);
                break;
            }
            case 2: {
                int dia, mes;
                printf("Dia que deseja consultar: ");
                scanf("%d", &dia);
                getchar();
                printf("Mês que deseja consultar: ");
                scanf("%d", &mes);
                getchar();

                VendasDia *diaSelecionado = NULL;
                for (int i = 0; i < totalDias; i++) {
                    if (historico[i].dia == dia && historico[i].mes == mes) {
                        diaSelecionado = &historico[i];
                        break;
                    }
                }

                if (diaSelecionado != NULL) {
                    relatorioDiario(diaSelecionado);
                } else {
                    printf("Nenhuma venda registrada neste dia.\n");
                }
                break;
            }
            case 3:
                relatorioMensal(historico, totalDias);
                break;
            case 4:
                relatorioAnualOrdenado(historico, totalDias);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
