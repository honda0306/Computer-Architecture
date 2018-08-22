#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) {
  return cpu->ram[address];
}

void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) {
  cpu->ram[address] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *file)
{
    FILE * f;
    f = fopen(file, "r");
    if (f == NULL) {
      fprintf(stderr, "We cannot open the given file.\n");
      exit(1);
    }

  int address = 0;

  char line[256];

  while (fgets(line, sizeof(line), f)) {
    char *endptr;
    unsigned long int new_line;
    new_line = strtoul(line, &endptr, 2);
    cpu->ram[address++] = new_line;
  }

  fclose(f);

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      cpu->reg[regA] *= cpu->reg[regB];
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);
    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);
    
    switch(IR) {

      case LDI:
        cpu->reg[operandA] = operandB;
        // cpu->pc += 3;
        break;
      
      case PRN:
        printf("%d\n", cpu->reg[operandA]);
        // cpu->pc += 2;
        break;
      
      case HLT:
        running = 0;
        break;
      
      case MUL:
        alu(cpu, ALU_MUL, operandA, operandB);
        break;

      default:
        printf("Cannot identify instruction at %02x: %02x\n", cpu->pc, IR);
        exit(2);


    }

    cpu->pc += (IR >> 6) + 1;

    // Just a test to see if this format works, need to confirm (Stack Overflow!!)
    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  // TODO: Zero registers and RAM
}
