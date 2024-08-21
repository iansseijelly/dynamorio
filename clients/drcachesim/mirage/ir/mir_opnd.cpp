#include "mir_opnd.h"

mir_opnd_t* mir_opnd_malloc_reg(reg_id_t reg) {
    mir_opnd_t* opnd = (mir_opnd_t*)malloc(sizeof(mir_opnd_t));
    assert(opnd != NULL);
    opnd->type = MIR_OPND_REG;
    opnd->value.reg = reg;
    return opnd;
}

mir_opnd_t* mir_opnd_malloc_imm(int64_t imm) {
    mir_opnd_t* opnd = (mir_opnd_t*)malloc(sizeof(mir_opnd_t));
    assert(opnd != NULL);
    opnd->type = MIR_OPND_IMM;
    opnd->value.imm = imm;
    return opnd;
}

void mir_opnd_free(mir_opnd_t *opnd) {
    if (opnd != NULL) {
        free(opnd);
    }
}

const char* mir_opnd_to_str(mir_opnd_t* opnd) {
    static char buffer[256];
    if (mir_opnd_is_reg(opnd)) {
        if (opnd->value.reg >= MIR_TMP_REG_START) {
            snprintf(buffer, sizeof(buffer), "R[%s](%d)", get_tmp_register_name(opnd->value.reg), opnd->value.reg);
        } else {
            snprintf(buffer, sizeof(buffer), "R[%s](%d)", get_register_name(opnd->value.reg), opnd->value.reg);
        }
    } else if (mir_opnd_is_imm(opnd)) {
        snprintf(buffer, sizeof(buffer), "I[%ld]", opnd->value.imm);
    }
    return buffer;
}

bool mir_opnd_is_reg(const mir_opnd_t *opnd) {
    return opnd->type == MIR_OPND_REG;
}

bool mir_opnd_is_imm(const mir_opnd_t *opnd) {
    return opnd->type == MIR_OPND_IMM;
}