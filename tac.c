#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LEN 5
#define SIZE 50

// Structure to store three address code
struct {
    char res[LEN];
    char op;
    char opnd1[LEN];
    char opnd2[LEN];
} tac[SIZE];

int num_instr = 0;
char instr[SIZE];

void read_three_address_code() {
    printf("Enter the number of instructions\n");
    scanf("%d", &num_instr);

    printf("Enter each instruction, separate result opcodes and operands by space\n");
    printf("E.g. s = a + b\n");

    for (int i = 0; i < num_instr; i++) {
        scanf("%s = %s %c %s", tac[i].res, tac[i].opnd1, &tac[i].op, tac[i].opnd2);
    }
}

char *get_instr(char op) {
    // ASCII values: * = 42, + = 43, - = 45, / = 47
    char mnemonics[][LEN] = { "MUL", "ADD", "", "SUB", "", "DIV" };
    strcpy(instr, mnemonics[op - '*']);
    return instr;
}

void generate_target_code() {
    for (int i = 0; i < num_instr; i++) {
        printf("MOV AX, %s\n", tac[i].opnd1);
        printf("%s AX, %s\n", get_instr(tac[i].op), tac[i].opnd2);
        printf("MOV %s, AX\n", tac[i].res);
    }
}

int main() {
    read_three_address_code();
    printf("Equivalent Assembly code is:\n");
    generate_target_code();
    return 0;
}
