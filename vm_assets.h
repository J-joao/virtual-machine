#ifndef __ASSETS_H
#define __ASSETS_H

typedef const char * string;

// instruções
enum instructions {
    LDA  = 1, 
    STO  = 2, 
    CLA  = 3,
    ADD  = 4, 
    SUB  = 5, 
    MUL  = 6, 
    DIV  = 7,
    AND  = 8, 
    OR   = 9, 
    XOR  = 10,  
    SHL  = 11, 
    SHR  = 12,
    JMP  = 13, 
    JGE  = 14, 
    JNE  = 15,
    JAC  = 16,
    HALT = 17
} instructions;


// endereço na memória | opcode (ultimos 16 bits) | operando (primeiros 16 bits)
typedef struct Instruction_t {
    uint16_t address;
    uint16_t opcode;
    uint16_t operand;
} Instruction_t;

// esse union divide um uint32_t em dois uint16_t 
union i32 {
    uint32_t v;
    struct {
        int n1:16;
        int n2:16;
    } n;
};

// registradores
struct reg {
    int32_t pc, cir, mar, mbr, acc;
} reg;

// memória
int32_t mem[INT16_MAX];

// estado da maquina
bool running = true;

#endif //__ASSETS_H