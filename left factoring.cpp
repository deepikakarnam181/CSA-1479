#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTION 100
#define MAX_SYMBOL 20

typedef struct {
    char lhs[MAX_SYMBOL];
    char rhs[MAX_PRODUCTION][MAX_SYMBOL];
    int rhs_count;
} Production;

void eliminate_left_factoring(Production productions[], int production_count) {
    for (int i = 0; i < production_count; i++) {
        Production p = productions[i];
        int j, k;
        for (j = 0; j < p.rhs_count - 1; j++) {
            for (k = j + 1; k < p.rhs_count; k++) {
                int common_prefix_len = 0;
                while (strcmp(p.rhs[j], p.rhs[k]) == 0 && common_prefix_len < strlen(p.rhs[j])) {
                    common_prefix_len++;
                }
                if (common_prefix_len > 0) {
                    char new_symbol[MAX_SYMBOL];
                    sprintf(new_symbol, "%s'", p.lhs);
                    Production new_production;
                    strcpy(new_production.lhs, new_symbol);
                    strcpy(new_production.rhs[0], p.rhs[j] + common_prefix_len);
                    new_production.rhs_count = 1;
                    productions[production_count] = new_production;
                    production_count++;
                    for (int l = j; l < p.rhs_count; l++) {
                        strcpy(p.rhs[l], p.rhs[l] + common_prefix_len);
                    }
                }
            }
        }
    }
}

void print_productions(Production productions[], int production_count) {
    for (int i = 0; i < production_count; i++) {
        Production p = productions[i];
        printf("%s -> ", p.lhs);
        for (int j = 0; j < p.rhs_count; j++) {
            printf("%s | ", p.rhs[j]);
        }
        printf("\n");
    }
}

int main() {
    Production productions[] = {
        {"E", {"E+T", "T"}, 2},
        {"T", {"0", "1"}, 2}
    };
    int production_count = sizeof(productions) / sizeof(productions[0]);

    printf("Original productions:\n");
    print_productions(productions, production_count);

    eliminate_left_factoring(productions, production_count);

    printf("Productions after eliminating left factoring:\n");
    print_productions(productions, production_count);

    return 0;
}
