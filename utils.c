#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* Unpacks the 32-bit machine code instruction given into the correct
 * type within the instruction struct */

//// Kirstin ////
Instruction parse_instruction(uint32_t instruction_bits) {
  /* YOUR CODE HERE */

  //// Helper Function which sets instructions for all the different opcodes of I-type instructions (why does it not work) ////
  Instruction iTypeInstructions(Instruction instruction, uint32_t instruction_bits) {

    // 0000 0001 0101 1010 0000 0100 1
    instruction.itype.rd = instruction_bits;
    instruction_bits >>= 5;
    // 0000 0001 0101 1010 0000
    instruction.itype.funct3 = instruction_bits;
    instruction_bits >>= 3;
    // 0000 0001 0101 1010 0
    instruction.itype.rs1 = instruction_bits;
    instruction_bits >>= 5;
    // 0000 0001 0101
    instruction.itype.imm = instruction_bits;
    instruction_bits >>= 12;
  
    return instruction;
  }

  Instruction instruction;
  // add x9, x20, x21   hex: 01 5A 04 B3, binary = 0000 0001 0101 1010 0000 0100 1011 0011
  // Opcode: 0110011 (0x33) Get the Opcode by &ing 0x1111111, bottom 7 bits
  instruction.opcode = instruction_bits & ((1U << 7) - 1);

  // Shift right to move to pointer to interpret next fields in instruction.
  instruction_bits >>= 7;

  switch (instruction.opcode) {
  // R-Type
  case 0x33:
    // instruction: 0000 0001 0101 1010 0000 0100 1, destination : 01001
    instruction.rtype.rd = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, func3 : 000
    instruction.rtype.funct3 = instruction_bits & ((1U << 3) - 1);
    instruction_bits >>= 3;

    // instruction: 0000 0001 0101 1010 0, src1: 10100
    instruction.rtype.rs1 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101, src2: 10101
    instruction.rtype.rs2 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // funct7: 0000 000
    instruction.rtype.funct7 = instruction_bits & ((1U << 7) - 1);
    break;
  // cases for other types of instructions
  /* YOUR CODE HERE */

  // I-Type
  case 0x13: // 0x11 OR 0x1110011
    //iTypeInstructions(instruction, instruction_bits);
    // 0000 0001 0101 1010 0000 0100 1
    instruction.itype.rd = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101 1010 0000
    instruction.itype.funct3 = instruction_bits;
    instruction_bits >>= 3;

    // 0000 0001 0101 1010 0
    instruction.itype.rs1 = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101
    instruction.itype.imm = instruction_bits;
    instruction_bits >>= 12;
  break;

  // I-Type
  case 0x3:
    //iTypeInstructions(instruction, instruction_bits);
    // 0000 0001 0101 1010 0000 0100 1
    instruction.itype.rd = instruction_bits;
    instruction_bits >>= 5;
    // 0000 0001 0101 1010 0000
    instruction.itype.funct3 = instruction_bits;
    instruction_bits >>= 3;
    // 0000 0001 0101 1010 0
    instruction.itype.rs1 = instruction_bits;
    instruction_bits >>= 5;
    // 0000 0001 0101
    instruction.itype.imm = instruction_bits;
    instruction_bits >>= 12;
  break;

  // I-Type
  case 0x73:
  // 0000 0001 0101 1010 0000 0100 1
    instruction.itype.rd = instruction_bits;
    instruction_bits >>= 5;
    // 0000 0001 0101 1010 0000
    instruction.itype.funct3 = instruction_bits;
    instruction_bits >>= 3;
    // 0000 0001 0101 1010 0
    instruction.itype.rs1 = instruction_bits;
    instruction_bits >>= 5;
    // 0000 0001 0101
    instruction.itype.imm = instruction_bits;
    instruction_bits >>= 12;
    //iTypeInstructions(instruction, instruction_bits);
  break;

  // S-Type
  case 0x23:

    // 0000 0001 0101 1010 0000 0100 1
    instruction.stype.imm5 = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101 1010 0000
    instruction.stype.funct3 = instruction_bits;
    instruction_bits >>= 3;

    // 0000 0001 0101 1010 0
    instruction.stype.rs1 = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101
    instruction.stype.rs2 = instruction_bits;
    instruction_bits >>= 5;

    // 0000 000

    instruction.stype.imm7 = instruction_bits;
    
  break;


  // SB-Type
  case 0x63:

    // 0000 0001 0101 1010 0000 0100 1
    instruction.sbtype.imm5 = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101 1010 0000
    instruction.sbtype.funct3 = instruction_bits;
    instruction_bits >>= 3;

    // 0000 0001 0101 1010 0
    instruction.sbtype.rs1 = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101
    instruction.sbtype.rs2 = instruction_bits;
    instruction_bits >>= 5;

    // 0000 000
    instruction.sbtype.imm7 = instruction_bits;

  break;

  // U-Type
  case 0x37:

    //0000 0001 0101 1010 0000 0100 1
    instruction.utype.rd = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101 1010 0000
    instruction.utype.imm = instruction_bits;

  break;

  // UJ-Type
  case 0x6F:

    // 0000 0001 0101 1010 0000 0100 1
    instruction.ujtype.rd = instruction_bits;
    instruction_bits >>= 5;

    // 0000 0001 0101 1010 0000
    instruction.ujtype.imm = instruction_bits;
  
  break;


  #ifndef TESTING
  default:
    exit(EXIT_FAILURE);
  #endif
  }
  return instruction;
}

/************************Helper functions************************/
/* Here, you will need to implement a few common helper functions, 
 * which you will call in other functions when parsing, printing, 
 * or executing the instructions. */

/* Sign extends the given field to a 32-bit integer where field is
 * interpreted an n-bit integer. */
//// Kirstin ////
int sign_extend_number(unsigned int field, unsigned int n) {
  /* YOUR CODE HERE */

  // Takes the field and masks it with a bit mask of 1s except for the last n bits being 0.
  int mask1 = (~(0) << n);
  int extend = (mask1 | field);

  // Type cast the field to determine if the value is negative or positive
  int typeCast = (int)extend;
  int mask2 = 1 << (n - 1); // bit mask of 1s to obtain the MSB
  int isNegative = !(!(typeCast & mask2)); // double logical negate it to get a single bit of 1 (if negative) and 0 (if positive)

  // return extend with the extended mask of 1 bits if negative; otherwise return field itself
  return (isNegative) ? (extend) : (field);
}

/* Return the number of bytes (from the current PC) to the branch label using
 * the given branch instruction */
int get_branch_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  int imm = instruction.sbtype.imm5;
  return imm;
}

/* Returns the number of bytes (from the current PC) to the jump label using the
 * given jump instruction */
int get_jump_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  int mask;
  int imm = instruction.ujtype.imm;

  int mask1 = (instruction.ujtype.imm >> 7 & ~(0U << 7) - 1);
  return imm;
}

/* Returns the number of bytes (from the current PC) to the base address using the
 * given store instruction */
int get_store_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  return 0;
}
/************************Helper functions************************/

void handle_invalid_instruction(Instruction instruction) {
  printf("Invalid Instruction: 0x%08x\n", instruction.bits);
}

void handle_invalid_read(Address address) {
  printf("Bad Read. Address: 0x%08x\n", address);
  exit(-1);
}

void handle_invalid_write(Address address) {
  printf("Bad Write. Address: 0x%08x\n", address);
  exit(-1);
}
