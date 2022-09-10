<details>
<summary style="font-size:14px">Documentação em Portugues-Brasil</summary>
<p>

# § memória

``` c
int32_t mem[INT16_MAX];
``` 

|  estrutura da memória  | tamanho (hex)  |
|------------------------|----------------|
| memória de dados       | 0000  - 1110   |
| memória de instruções  | 1110  - ffff   |

essa maquina virtual usa uma **memória de 32 bits** e **16 bits para endereços**

exemplo:
``` c
// address    contents
mem[0x0000] = 00030001;
mem[0x0001] = 00010000;
``` 
os endereços podem ir de 0000 à ffff enquanto seus conteúdos podem ir de 00000000 à ffffffff

### por que os endereços são organizados assim?
porque as instruções usam **16 para o opcode** tendo **16 bits para o operando**, portanto, uma instrução tipo: *jmp 1112* pode apenas usar 16 bits como parâmetro, e pode ser representada na memória da seguinte maneira:

``` c
mem[0x0000] = 000d1112;   // jmp 0x1112
``` 
sendo *000d* o valor do opcode JMP e *1112* sendo seu parâmetro 

# § registradores 
``` c
// registers
struct reg {
    int32_t pc, cir, mar, mbr, acc;
} reg;
```

essa maquina virtual usa 5 registradores.
- pc = contador de programa (program counter)
- cir = registrador de instrução atual (current instruction register)
- mar = registrador de endereço de memoria (memory address register)
- acc = acumulador (accumulator)

existe também um "registrador" extra que serve para apontar o estado da máquina (ligada ou desligada)
``` c
bool running = true;
```
>  ele é definido com o valor *true* por padrão 

# § instruções 

### LDA
- LDA significa "Load Accumulator"
- recebe um endereço como parâmetro e carrega o acumulador com o valor que estiver naquele endereço 
### STO
- STO significa "Store"
- recebe um endereço como parâmetro e carrega este endereço com o valor do acumulador 
### CLA
- CLA significa "Clear Accumulator"
- não recebe nenhum parâmetro e limpa o registrador, deixando seu valor igual a 0

### ADD
- ADD significa "Add"
- recebe um endereço como parâmetro e soma o acumulador com o valor deste endereço 
### SUB
- SUB significa "Subtract"
- recebe um endereço como parâmetro e subtrai o acumulador com o valor deste endereço
### MUL
- MUL significa "Multiply"
- recebe um endereço como parâmetro e multiplica o acumulador com o valor deste endereço
### DIV
- DIV significa "Divide"
- recebe um endereço como parâmetro e divide o acumulador com o valor deste endereço

### AND
- AND significa "logical AND"
- recebe um endereço como parâmetro e efetua um AND(&) no acumulador com o valor deste endereço 
### OR
- OR significa "logical OR"
- recebe um endereço como parâmetro e efetua um OR(|) no acumulador com o valor deste endereço 
### XOR
- XOR significa "Exclusive OR"
- recebe um endereço como parâmetro e efetua um XOR(^) no acumulador com o valor deste endereço 

### SHL
- SHL significa "Shift Left" - deslocar para a esquerda
- recebe um endereço como parâmetro e desloca para a esquerda o acumulador com o valor deste endereço 
### SHR
- SHR significa "Shift Right" - deslocar para a direita
- recebe um endereço como parâmetro e desloca para a direira o acumulador com o valor deste endereço 

### JMP
- JMP significa "Jump"
- recebe um endereço como parâmetro e aponta o PC para este endereço
### JGE
- JGE significa "Jump if Greater or Equal"
- recebe um endereço como parâmetro e aponta o PC para este endereço se o valor do acumulador for maior ou igual a 0
### JNE
- JNE significa "Jump if Not Equal"
- recebe um endereço como parâmetro e aponta o PC para este endereço se o valor do acumulador for diferente de 0
### JAC
- JAC significa "Jump Accumulator"
- não recebe nenhum parâmetro e aponta o PC para o valor do acumulador

<img src="img/table.jpg">

</p></details>




<details>
<summary style="font-size:14px">English Documentation</summary>
<p>

# § memory

``` c
int32_t mem[INT16_MAX];
``` 

|  memory structure  | range (in hex) |
|--------------------|----------------|
| data memory        | 0000  - 1110   |
| instruction memory | 1110  - ffff   |

this virtual machine uses a **32 bit memory** with **16 bit addresses**

example:
``` c
// address    contents
mem[0x0000] = 00030001;
mem[0x0001] = 00010000;
``` 
addresses can range from 0000 to ffff while the contents of each address can range from 00000000 to ffffffff

### why are addresses organized like this?
because instructions have **16 bits for opcode** and **16 bits for operand**, thus, an instruction like *jmp 1112* can only take 16 bits as parameter, and can be represented in memory as:

``` c
mem[0x0000] = 000d1112;   // jmp 0x1112
``` 
with *000d* being the value for the opcode JMP and *1112* as being the location in memory to where to jump

# § registers
``` c
// registers
struct reg {
    int32_t pc, cir, mar, mbr, acc;
} reg;
```

this virtual machine has 5 registers.
- pc = program counter
- cir = current instruction register
- mar = memory address register
- acc = accumulator

there is also an additional "register" that just points out whether the machine is running or not 
``` c
bool running = true;
```
>  it is deffined to be true by default

# § instructions 
### LDA
- LDA stands for "Load Accumulator"
- it receives an address as parameter and loads the accumulator with the value located at that address
### STO
- STO stands for "Store"
- it receives an address as parameter and loads that address with the value inside the accumulator
### CLA
- CLA stands for "Clear Accumulator"
- it receives no parameter and clears the accumulator, setting it's value to 0

### ADD
- ADD stands for "Add"
- it receives an address as parameter and adds the accumulator with the value located at that address
### SUB
- SUB stands for "Subtract"
- it receives an address as parameter and subtracts the accumulator with the value located at that address
### MUL
- MUL stands for "Multiply"
- it receives an address as parameter and multiplies the accumulator with the value located at that address
### DIV
- DIV stands for "Divide"
- it receives an address as parameter and divides the accumulator with the value located at that address

### AND
- AND stands for "logical AND"
- it receives an address as parameter and ands(&) the accumulator with the value located at that address
### OR
- OR stands for "logical OR"
- it receives an address as parameter and ors(|) the accumulator with the value located at that address
### XOR
- XOR stands for "Exclusive OR"
- it receives an address as parameter and xors(^) the accumulator with the value located at that address

### SHL
- SHL stands for "Shift Left"
- it receives an address as parameter and shifts the accumulator to the left with the value located at that address
### SHR
- SHR stands for "Shift Right"
- it receives an address as parameter and shifts the accumulator to the right with the value located at that address

### JMP
- JMP stands for "Jump"
- it receives an address as parameter and sets the PC to point to that address
### JGE
- JGE stands for "Jump if Greater or Equal"
- it receives an address as parameter and sets the PC to point to that address if the accumulator is greater or equal to 0
### JNE
- JNE stands for "Jump if Not Equal"
- it receives an address as parameter and sets the PC to point to that address if the accumulator is different than 0
### JAC
- JAC stands for "Jump Accumulator"
- it receives no parameter and sets the PC to point to the accumulator

<img src="img/table.jpg">

</p></details>
