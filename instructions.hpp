#ifndef vm_inst
#define vm_inst

namespace vm
{

    enum Instruction
    {
        /// Constant name = value, // how to use it ; behaviour

        // types
        INST_INT       = 0x01,  // 0x01 [integer on 2 bytes]
        INST_STR       = 0x02,  // 0x02 [size of the string on 2 bytes] [string]
        INST_BOOL      = 0x03,  // 0x03 [value] ; if value > 0x00 => true
        INST_VAR       = 0x04,  // 0x04 [size of var name on 1 byte][var]

        // labels and blocs
        INST_SEGMENT   = 0x10,  // 0x10 [segment size on 1 byte] [segment]
        INST_STORE_VAR = 0x11,  // 0x11 ; store the value at stack[-2] in stack[-1]
        INST_PUSH_VAR  = 0x12,  // 0x12 [size of the name of the var on 1 byte] [var] ; push its value on the stack
        INST_JUMP      = 0x13,  // 0x13 [size of the segment name on 1 byte] [segment]
        /// to implement !
        INST_JMP_TRUE  = 0x14,  // 0x14 [size of the segment name on 1 byte] [segment] ; jump if stack[-1] compares to true
        INST_JMP_FALSE = 0x15,  // 0x15 [size of the segment name on 1 byte] [segment] ; jump if stack[-1] compares to false
        INST_RET       = 0x16,  // 0x16 ; return from a segment

        // built-in procedures around numbers and booleans
        INST_ADD       = 0x50,  // 0x50 ; push the result of stack[-2] + stack[-1]
        /// to implement !
        INST_SUB       = 0x51,  // 0x51 ; push the result of stack[-2] - stack[-1]
        INST_DIV       = 0x52,  // 0x52 ; push the result of stack[-2] / stack[-1]
        INST_MUL       = 0x53,  // 0x53 ; push the result of stack[-2] * stack[-1]
        INST_MOD       = 0x54,  // 0x54 ; push the result of stack[-2] % stack[-1]
        INST_INC       = 0x55,  // 0x55 ; push the result of stack[-1]++
        INST_DEC       = 0x56,  // 0x56 ; push the result of stack[-1]--
        INST_NEG       = 0x57,  // 0x57 ; push the result of - stack[-1]
        INST_BIN_AND   = 0x58,  // 0x58 ; push the result of stack[-2] & stack[-1]
        INST_BIN_OR    = 0x59,  // 0x59 ; push the result of stack[-2] | stack[-1]
        INST_BIN_NOT   = 0x60,  // 0x60 ; push the result of ~ stack[-1]
        INST_LSHIFT    = 0x61,  // 0x61 ; push the result of stack[-2] << stack[-1]
        INST_RSHIFT    = 0x62,  // 0x62 ; push the result of stack[-2] >> stack[-1]
        INST_BIN_XOR   = 0x63,  // 0x63 ; push the result of stack[-2] ^ stack[-1]
        INST_AND       = 0x64,  // 0x64 ; push the result of stack[-2] && stack[-1]
        INST_OR        = 0x65,  // 0x65 ; push the result of stack[-2] || stack[-1]
        INST_NOT       = 0x66,  // 0x66 ; push the result of ! stack[-1]

        // built-in functions
        /// to implement !
        // print, getchar, getline
    };

}  // namespace vm

#endif // vm_inst
