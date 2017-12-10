#include <iostream>

#include "vm.hpp"

void start(char* bytecode, unsigned s)
{
    vm::VM vm;

    for (unsigned i=0; i < s; ++i)
        std::cout << (unsigned int) bytecode[i] << ":" << bytecode[i] << std::endl;

    std::cout << "----------" << std::endl;
    vm.exec(bytecode, s);
    std::cout << "----------" << std::endl
              << "stack size : " << vm.getStack().size() << std::endl;
    for (std::size_t i=0; i < vm.getStack().size(); ++i)
    {
        std::cout << "[" << i << "] ";
        if (vm.getStack()[i].type == vm::TYPE_INT)
            std::cout << "INT " << vm.getStack()[i].intValue;
        else if (vm.getStack()[i].type == vm::TYPE_BOOL)
            std::cout << "BOOL " << vm.getStack()[i].boolValue;
        else if (vm.getStack()[i].type == vm::TYPE_STRING)
            std::cout << "STRING " << vm.getStack()[i].stringValue;
        std::cout << std::endl;
    }
    std::cout << std::endl << "=================================" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        // testing area

        // int:18768, str:hello, bool:true
        char bytecode[] = {
            vm::INST_INT, 0x49, 0x50,
            vm::INST_STR, 0x00, 0x05, 'h', 'e', 'l', 'l', 'o',
            vm::INST_BOOL, 'A',
            0x00
        };
        start(bytecode, 14);

        // put the integer 1 into `var`, then put `var` at the top of the stack
        // then push the int 9 on the stack and perform an addition, push the result on the stack
        char bytecode2[] = {
            vm::INST_INT, 0x00, 0x01,
            vm::INST_VAR, 0x3, 'v', 'a', 'r',
            vm::INST_STORE_VAR,
            vm::INST_PUSH_VAR, 0x03, 'v', 'a', 'r',
            vm::INST_INT, 0x00, 0x09,
            vm::INST_ADD,
            0x00
        };
        start(bytecode2, 19);

        // jump to the beginning ... until the world burns out in flame
        char bytecode3[] = {
            vm::INST_SEGMENT, 0x05, 'l', 'a', 'b', 'e', 'l',
            vm::INST_JUMP, 0x05, 'l', 'a', 'b', 'e', 'l',
            0x00
        };
        /// start(bytecode3, 15);
    }

    return 0;
}
