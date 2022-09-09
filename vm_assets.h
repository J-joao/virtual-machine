#ifndef __ASSETS_H
#define __ASSETS_H

//
// as 3 macros abaixo servem para manipular bits individuais
//
#define SET_BIT(BF, N) BF |= ((uint32_t)0x00000001 << N)
#define CLR_BIT(BF, N) BF &= ~((uint32_t)0x00000001 << N)
#define IS_BIT_SET(BF, N) ((BF >> N) & 0x1)

#define ERRORMSG "[\e[1;31mERROR\e[0m]: "

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

// instruções
enum {
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
};

// registradores
struct reg {
    int32_t pc, cir, mar, mbr, acc;
} reg;

// memória
int32_t mem[INT16_MAX];

bool running = true;

/* essa função busca a instrução na memória */
void fetch();

/* essa função parcela a instrução "crua" em: endereço/opcode/operando
 *  @param address: endereço da instrução na memória
 *  @param raw_instruction: instrução "crua" (valor do endereço de memória passado anteriormente) */
Instruction_t parse_instruction(uint16_t address, uint32_t raw_instruction);

/* essa função decodifica a instrução e executa uma ação  baseada em seu valor
 * @param instruction: struct contendo opcode, operando e endereço */
void execute(Instruction_t instruction);

#endif //__ASSETS_H