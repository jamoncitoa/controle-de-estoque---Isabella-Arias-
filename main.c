#include <stdio.h>
#include <string.h>

int main() {
    int op = 0;
    char resp = 's';

    do {
        printf("==============================\n");
        printf("   Controle de Estoque\n");
        printf("==============================\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Estoque\n");
        printf("4. Sair\n");
        printf("Opcao: ");
        
        if (scanf("%d", &op) != 1) {
            printf("Opcao invalida! Tente novamente.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (op < 1 || op > 4) {
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }

        if (op == 4) {
            printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
            break;
        }

        if (op == 1) {
            char nm[50];
            int q = 0;
            printf("Digite o nome do item: ");
            scanf("%s", nm);
            printf("Digite a quantidade: ");
            scanf("%d", &q);

            char nomes[100][50];
            int qt[100];
            int tot = 0;

            FILE *f = fopen("inventory.txt", "r");
            if (f != NULL) {
                while (fscanf(f, "%s %d", nomes[tot], &qt[tot]) == 2) {
                    tot++;
                }
                fclose(f);
            }

            int enc = 0;
            for (int i = 0; i < tot; i++) {
                if (strcmp(nomes[i], nm) == 0) {
                    qt[i] += q;
                    enc = 1;
                    break;
                }
            }
            if (!enc) {
                strcpy(nomes[tot], nm);
                qt[tot] = q;
                tot++;
            }

            f = fopen("inventory.txt", "w");
            for (int i = 0; i < tot; i++) {
                fprintf(f, "%s\n%d\n", nomes[i], qt[i]);
            }
            fclose(f);

            printf("Item adicionado com sucesso!\n");

        } else if (op == 2) {
            char nm[50];
            int q = 0;
            printf("Digite o nome do item: ");
            scanf("%s", nm);
            printf("Digite a quantidade a ser removida: ");
            scanf("%d", &q);

            char nomes[100][50];
            int qt[100];
            int tot = 0;

            FILE *f = fopen("inventory.txt", "r");
            if (f != NULL) {
                while (fscanf(f, "%s %d", nomes[tot], &qt[tot]) == 2) {
                    tot++;
                }
                fclose(f);
            }

            int idx = -1;
            for (int i = 0; i < tot; i++) {
                if (strcmp(nomes[i], nm) == 0) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                printf("Item nao encontrado.\n");
            } else {
                if (q > qt[idx]) {
                    printf("Estoque insuficiente. Quantidade disponivel: %d\n", qt[idx]);
                } else if (q == qt[idx]) {
                    for (int i = idx; i < tot - 1; i++) {
                        strcpy(nomes[i], nomes[i+1]);
                        qt[i] = qt[i+1];
                    }
                    tot--;
                    printf("Item removido do estoque!\n");
                    
                    f = fopen("inventory.txt", "w");
                    for (int i = 0; i < tot; i++) {
                        fprintf(f, "%s\n%d\n", nomes[i], qt[i]);
                    }
                    fclose(f);
                } else {
                    qt[idx] -= q;
                    printf("Quantidade atualizada com sucesso!\n");

                    f = fopen("inventory.txt", "w");
                    for (int i = 0; i < tot; i++) {
                        fprintf(f, "%s\n%d\n", nomes[i], qt[i]);
                    }
                    fclose(f);
                }
            }

        } else if (op == 3) {
            char nomes[100][50];
            int qt[100];
            int tot = 0;

            FILE *f = fopen("inventory.txt", "r");
            if (f != NULL) {
                while (fscanf(f, "%s %d", nomes[tot], &qt[tot]) == 2) {
                    tot++;
                }
                fclose(f);
            }

            if (tot == 0) {
                printf("O estoque esta vazio.\n");
            } else {
                printf("==============================\n");
                printf("       Estoque Atual\n");
                printf("==============================\n");
                for (int i = 0; i < tot; i++) {
                    printf("Nome: %s\n", nomes[i]);
                    printf("Quantidade: %d\n", qt[i]);
                    if (i < tot - 1) {
                        printf("\n");
                    }
                }
            }
        }

        printf("Deseja realizar outra operacao? (s/n): ");
        scanf(" %c", &resp);
        if (resp != 's' && resp != 'S') {
            printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
            break;
        }

    } while (1);

    return 0;
}

