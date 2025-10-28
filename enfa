#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

// Adjacency matrix for storing ε-transitions only
bool epstable[MAX][MAX] = { false };
int numstates, numtrans;

// Read an NFA with ε-transitions (only ε-transitions are stored)
void get_enfa() {
    char transition[MAX], *p;

    printf("Enter the number of states n, states will be named from q0 to q(n-1)\n");
    scanf("%d", &numstates);

    printf("Enter the total number of transitions\n");
    scanf("%d", &numtrans);

    printf("Enter all the transitions as state symbol state (no spaces), e.g. q0aq1\n");
    printf("Use # for epsilon transitions (e.g. q0#q1)\n");

    for (int i = 0; i < numtrans; i++) {
        scanf("%s", transition);
        printf("%s", transition);

        // Only ε-transitions are stored
        if ((p = strchr(transition, '#')) != NULL) {
            int from, to;
            sscanf(transition, "q%d", &from); // state on left ε-transition
            to = atoi(p + 2);                 // state on right ε-transition
            epstable[from][to] = true;        // adjacency matrix of ε-transitions
        }
    }
}

// Recursively finds ε-closure of a state
void findeclose(int state, bool visited[]) {
    visited[state] = true; // Mark the state as part of ε-closure

    for (int i = 0; i < numstates; i++) {
        // If there is an ε-transition and not already considered
        if (epstable[state][i] && !visited[i]) {
            findeclose(i, visited); // Recursively find ε-closure of reachable state
        }
    }
}

// Prints the ε-closure of all states
void printeclose() {
    for (int i = 0; i < numstates; i++) {
        bool visited[MAX] = { false };
        char outstr[MAX] = { '\0' };
        char tempstr[MAX] = { '\0' };

        findeclose(i, visited);

        printf("ε-closure(q%d) = {", i);
        for (int j = 0; j < numstates; j++) {
            if (visited[j]) {
                sprintf(tempstr, "q%d,", j);
                strcat(outstr, tempstr);
            }
        }

        // Remove the last comma if present
        if (strlen(outstr) > 0)
            outstr[strlen(outstr) - 1] = '\0';

        printf("%s}\n", outstr);
    }
}

int main() {
    get_enfa();
    printeclose();
    return 0;
}
