#ifndef __MIR_INSN_H__
#define __MIR_INSN_H__

#include "dr_api.h"
#include "mir_opc.h"
#include "mir_opnd.h"

#include "list.h"

#include "assert.h"
#include "string.h"

#define PRINT_HEX_THRESHOLD 0x1000

struct mir_insn_t {
    mir_opc_t op;          // The opcode of the MIR instruction
    mir_opnd_t opnd0;     // The first source operand of the MIR instruction
    mir_opnd_t opnd1;     // The second source operand of the MIR instruction
    mir_opnd_t dst;       // The destination operand of the MIR instruction
    struct list_elem elem; // Linked list traversal element
};

// Allocate a new MIR instruction with a given opcode
mir_insn_t* mir_insn_malloc(mir_opc_t op);

// Free a MIR instruction
void mir_insn_free(mir_insn_t *insn);

// malloc a new opnd
void mir_insn_set_src0_reg(mir_insn_t *insn, reg_id_t reg);
void mir_insn_set_src0_imm(mir_insn_t *insn, int64_t imm);   
void mir_insn_set_src1_reg(mir_insn_t *insn, reg_id_t reg);
void mir_insn_set_src1_imm(mir_insn_t *insn, int64_t imm);
void mir_insn_set_dst_reg(mir_insn_t *insn, reg_id_t reg);
void mir_insn_set_dst_imm(mir_insn_t *insn, int64_t imm); // useful for storing immediates

// Set the opcode of a MIR instruction
void mir_insn_set_op(mir_insn_t *insn, mir_opc_t op);

// LIST of MIR
typedef struct list mir_insn_list_t;

void init_mir_insn_list(mir_insn_list_t* list);
void mir_insn_push_front(mir_insn_list_t* list, mir_insn_t* insn);
void mir_insn_push_back(mir_insn_list_t* list, mir_insn_t* insn);
void mir_insn_insert_before(mir_insn_t* insn, mir_insn_t* before);
void mir_insn_insert_after(mir_insn_t* insn, mir_insn_t* after);
void print_mir_insn_list(mir_insn_list_t* list);

#endif // __MIR_INSN_H__