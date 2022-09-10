#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "vm_assets.h"

typedef const char * string;

// as 3 macros abaixo servem para manipular bits individualmente
#define SET_BIT(BF, N) BF |= ((uint32_t)0x00000001 << N)
#define CLR_BIT(BF, N) BF &= ~((uint32_t)0x00000001 << N)
#define IS_BIT_SET(BF, N) ((BF >> N) & 0x1)

#define WARNINGMSG "[\e[0;31mWARNING\e[0m]: "
#define ERRORMSG "[\e[0;31mERROR\e[0m]: "

// mensagem de aviso
void warning(string message) {
    fprintf(stderr, WARNINGMSG"%s", message); 
}

// mensagem de erro
void failure(string message) {
    fprintf(stderr, ERRORMSG"%s", message); exit(EXIT_FAILURE);
}

/* essa função busca a instrução na memória 
 * -retorna 0 se houve sucesso em sua execução */
int fetch() {
    reg.mar = reg.pc;
    reg.mbr = reg.cir = mem[reg.mar];
    reg.pc++;
    return 0;
}

/* essa função parcela a instrução "crua" em: endereço/opcode/operando
 *  @param address: endereço da instrução na memória
 *  @param raw_instruction: instrução "crua" (valor do endereço de memória passado anteriormente) */
Instruction_t parse_instruction(uint16_t address, uint32_t raw_instruction) {
    union i32 i; i.v = (int32_t)mem[address];

    Instruction_t parsed_instruction = {
        .address = address,
        .opcode  = i.n.n2,      // ultimos 16 bits da instrução
        .operand = i.n.n1       // primeiros 16 bits da instrução
    };
    return parsed_instruction;
}

/* essa função decodifica a instrução e executa uma ação  baseada em seu valor
 * @param instruction: struct contendo opcode, operando e endereço 
 * -retorna 0 se houve sucesso em sua execução */
int execute(Instruction_t instruction) {
    switch (instruction.opcode) {
        case LDA:
            printf("lda %04x   ", instruction.operand);
            reg.acc = mem[instruction.operand];         // acc = mem[S]       
            break;
        case STO:
            printf("sto %04x   ", instruction.operand);
            mem[instruction.operand] = reg.acc;         // mem[S] = acc       
            break;
        case CLA:
            printf("cla        ");                        // acc = 0
            reg.acc = 0;
            break;
        case ADD:
            printf("add %04x   ", instruction.operand);
            reg.acc += mem[instruction.operand];        // acc += mem[S]
            break;
        case SUB:
            printf("sub %04x   ", instruction.operand);
            reg.acc -= mem[instruction.operand];        // acc -= mem[S]
            break;
        case MUL:
            printf("mul %04x   ", instruction.operand);
            reg.acc *= mem[instruction.operand];        // acc *= mem[S]
            break;
        case DIV:
            printf("div %04x   ", instruction.operand);
            reg.acc /= mem[instruction.operand];        // acc /= mem[S]
            break;
        case AND:
            printf("and %04x   ", instruction.operand);
            reg.acc &= mem[instruction.operand];        // acc &= mem[S]
            break;
        case OR:
            printf("or  %04x   ", instruction.operand);
            reg.acc |= mem[instruction.operand];        // acc |= mem[S]
            break;
        case XOR:
            printf("xor %04x   ", instruction.operand);
            reg.acc ^= mem[instruction.operand];        // acc ^= mem[S]
            break;
        case SHL:
            printf("shl %04x   ", instruction.operand);
            reg.acc <<= mem[instruction.operand];       // acc <<= mem[S]
            break;
        case SHR:
            printf("shr %04x   ", instruction.operand);
            reg.acc >>= mem[instruction.operand];       // acc >>= mem[S]
            break;
        case JMP:
            printf("jmp %04x   ", instruction.operand);
            reg.pc = instruction.operand;               // pc = S
            break;
        case JGE: {
            if (reg.acc >= 0) {
                printf("jge %04x   ", instruction.operand);
                reg.pc = instruction.operand;           // if acc >= 0; pc = S
                break;
            }
            break;
        }
        case JNE: {
            if (reg.acc != 0) {
                printf("jne %04x   ", instruction.operand);
                reg.pc = instruction.operand;           // if acc != 0; pc = S
                break;
            }
            break;
        }
        case JAC:
            printf("jac        ");
            reg.pc = reg.acc;                           // pc = ACC
            break;
        case HALT:
            printf("halt       ");
            running = false;                            // running = false
            break;

        // caso a instrução tenha valor 0 -> erro
        case 0:
            warning("blank opcode\n");
            return 1;

        // caso a instrução seja desconhecida -> erro
        default:
            warning("unknown instruction\n");
            return 1;
    }
    return 0;
}

int main(int argc, const char *argv[]) {
    mem[0x0000] = 0x2000;       // mem 0x0 = 0x2000
    mem[0x0001] = 0x2;          // mem 0x1 = 0x2

    mem[0x1111] = 0x00010000;   // lda 0000    
    mem[0x1112] = 0x00020003;   // sto 0003
    mem[0x1113] = 0x00030000;   // cla     
    mem[0x1114] = 0x00040000;   // add 0000
    mem[0x1115] = 0x00050000;   // sub 0000
    mem[0x1116] = 0x00060000;   // mul 0000
    mem[0x1117] = 0x00070000;   // div 0000
    mem[0x1118] = 0x00080000;   // and 0000
    mem[0x1119] = 0x00090000;   // or  0000
    mem[0x111a] = 0x000a0000;   // xor 0000
    mem[0x111b] = 0x000b0000;   // shl 0000
    mem[0x111c] = 0x000c0000;   // shr 0000
    mem[0x111d] = 0x000d111e;   // jmp 111e
    mem[0x111e] = 0x000e111f;   // jge 111f
    mem[0x111f] = 0x00010001;   // lda 0000
    mem[0x1120] = 0x000f1121;   // jne 1121 
    mem[0x1121] = 0x00010000;   // lda 0000
    mem[0x1122] = 0x00100000;   // jac
    mem[0x2000] = 0x00110000;   // halt     
    
    // apontar o PC para o inicio da memória de instruções
    reg.pc = 0x1111;
    
    while (running) {
        // verificar se o PC esta na memória de instruções
        if (reg.pc < 0x1111 || reg.pc > 0xffff) {
            failure("inappropriate memory address\n");
        }
        
        // fetch
        if (fetch() != 0) {
            failure("failed to fetch instruction\n");
        }
        
        // decode
        Instruction_t instruction = parse_instruction(reg.mar, reg.cir);
        
        // execute
        if (execute(instruction) != 0) {
            failure("failed to execute instruction\n");
        }
        
        printf("pc = %04x acc = %04x ADDR[%04x] INSTRUCTION: %08x | opcode = %04x operand = %04x\n", 
               reg.pc, reg.acc, reg.mar, mem[reg.mar], instruction.opcode, instruction.operand);
        
    }
    return 0;
}