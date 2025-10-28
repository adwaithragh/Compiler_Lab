#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 20

int n, m;  // Number of states, number of symbols
char symbols[MAX_SYMBOLS];  // Input symbols

int transition[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
int epsilon[MAX_STATES][MAX_STATES];  // ε-transitions
int epsilonClosure[MAX_STATES][MAX_STATES];
int closureCount[MAX_STATES];

// Function to add element to closure
void addToClosure(int state, int s) {
    if (!epsilonClosure[state][s]) {
        epsilonClosure[state][s] = 1;
        closureCount[state]++;
        for (int t = 0; t < n; t++) {
            if (epsilon[s][t]) {
                addToClosure(state, t);
            }
        }
    }
}

// Compute epsilon closure for all states
void computeEpsilonClosures() {
    for (int i = 0; i < n; i++) {
        memset(epsilonClosure[i], 0, sizeof(epsilonClosure[i]));
        closureCount[i] = 0;
        addToClosure(i, i);
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols (other than epsilon): ");
    scanf("%d", &m);

    printf("Enter input symbols (epsilon transitions are entered separately):\n");
    for (int i = 0; i < m; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Initialize transitions
    memset(transition, 0, sizeof(transition));
    memset(epsilon, 0, sizeof(epsilon));

    int num;
    printf("\nEnter transition table (for each state and symbol):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("\nFrom state q%d with symbol %c, number of next states: ", i, symbols[j]);
            scanf("%d", &num);

            if (num)
                printf("Enter next states (only state numbers, q not needed): ");

            for (int k = 0; k < num; k++) {
                int s;
                scanf("%d", &s);
                transition[i][j][s] = 1;
            }
        }
    }

    printf("\nEnter epsilon transitions (state -> state), enter -1 -1 to stop:\n");
    while (1) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == -1 && b == -1)
            break;
        epsilon[a][b] = 1;
    }

    // Compute epsilon closures
    computeEpsilonClosures();

    // Build new transition table without epsilon
    printf("\nEquivalent NFA without epsilon moves:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int result[MAX_STATES] = {0};

            // For every state in epsilon-closure of i
            for (int k = 0; k < n; k++) {
                if (epsilonClosure[i][k]) {
                    // Follow symbol transition
                    for (int l = 0; l < n; l++) {
                        if (transition[k][j][l]) {
                            // Add epsilon closure of l
                            for (int p = 0; p < n; p++) {
                                if (epsilonClosure[l][p]) {
                                    result[p] = 1;
                                }
                            }
                        }
                    }
                }
            }

            printf("From state q%d with symbol %c -> { ", i, symbols[j]);
            for (int x = 0; x < n; x++) {
                if (result[x])
                    printf("q%d ", x);
            }
            printf("}\n");
        }
    }

    return 0;
}
