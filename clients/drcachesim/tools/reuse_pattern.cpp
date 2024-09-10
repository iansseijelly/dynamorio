#include <iostream>
#include "reuse_pattern.h"

namespace dynamorio {
namespace drmemtrace {

analysis_tool_t *
reuse_pattern_tool_create()
{
    return new reuse_pattern_t();
}

reuse_pattern_t::reuse_pattern_t()
{
    replayer = new Replayer(INIT_STRATEGY_ZERO);
}

reuse_pattern_t::~reuse_pattern_t()
{
    // Empty.
}

std::string
reuse_pattern_t::initialize()
{
    dcontext_.dcontext = dr_standalone_init();
    return "";
}

std::string
reuse_pattern_t::initialize_stream(memtrace_stream_t *serial_stream)
{
    serial_stream_ = serial_stream;
    return "";
}

bool
reuse_pattern_t::parallel_shard_supported()
{
    return false;
}

void* 
reuse_pattern_t::parallel_shard_init_stream(int shard_index, void *worker_data, memtrace_stream_t *shard_stream)
{
    return shard_stream;
}

bool 
reuse_pattern_t::parallel_shard_exit(void *shard_data)
{
    return true;
}

std::string
reuse_pattern_t::parallel_shard_error(void *shard_data)
{
    return error_string_;
}

bool
reuse_pattern_t::process_memref(const memref_t &memref)
{
    return parallel_shard_memref(serial_stream_, memref);
}

bool
reuse_pattern_t::parallel_shard_memref(void *shard_data, const memref_t &memref)
{
    if (type_is_instr(memref.instr.type))
    {
        app_pc decode_pc = const_cast<app_pc>(memref.instr.encoding);
        // addr_t curr_inst_addr = memref.instr.addr;
        const app_pc curr_pc = reinterpret_cast<app_pc>(memref.instr.addr); 
        
        instr_t curr_instr;
        instr_init(dcontext_.dcontext, &curr_instr);
        app_pc tmp_pc = decode_from_copy(dcontext_.dcontext, decode_pc, curr_pc, &curr_instr);
        if (tmp_pc == NULL || !instr_valid(&curr_instr))
        {
            instr_free(dcontext_.dcontext, &curr_instr);
            // shard->error = "Failed to decode instruction " + to_hex_string(memref.instr.addr);
            return false;
        }
        // TODO: debug, remove
        // if (instr_get_opcode(&curr_instr) == OP_adc) {
            printf("encountered instruction at %p\n", curr_pc);
            mir_insn_list_t insn_list;
            init_mir_insn_list(&insn_list);
            dr_gen_mir_ops(&curr_instr, &insn_list);
            replayer->replay(&insn_list);
        // }
        return true;
    }
    return true;
}

bool
reuse_pattern_t::print_results()
{
    std::cerr << "Hello World\n";
    return true;
}

} // namespace drmemtrace
} // namespace dynamorio