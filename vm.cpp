#include <iostream>
#include <string.h>

#include "vm.hpp"

namespace vm
{

    VM::VM() :
        m_stack_size(0)
    {}

    VM::~VM() {}

    void VM::push(Value value)
    {
        m_stack.push_back(value);
        m_stack_size++;
    }

    Value VM::pop()
    {
        return abc::pop(m_stack, --m_stack_size);
    }

    void VM::clear()
    {
        m_stack.clear();
        m_stack_size = 0;
        m_variables.clear();
        m_segments.clear();
    }

    char VM::getByte(char* bytecode, unsigned s, unsigned i)
    {
        if (i < s)
            return bytecode[i];
        throw std::runtime_error("Index out of range, can not get next byte ! => Malformed bytecode");
    }

    int VM::exec(char* bytecode, unsigned s)
    {
        clear();

        for (unsigned i=0; i < s; ++i)
        {
            char instruction = getByte(bytecode, s, i);

            switch (instruction)
            {
                case INST_INT:
                {
                    std::cout << "int" << std::endl;
                    Value v;
                    v.type = TYPE_INT;
                    v.intValue = (getByte(bytecode, s, ++i) << 8) + getByte(bytecode, s, ++i);
                    push(v);
                    break;
                }

                case INST_STR:
                {
                    std::cout << "str" << std::endl;
                    unsigned str_size = (getByte(bytecode, s, ++i) << 8) + getByte(bytecode, s, ++i);
                    if (str_size > 0)
                    {
                        Value a;
                        a.type = TYPE_STRING;
                        ++i;
                        for (unsigned j=i; i - j < str_size; ++i)
                            { a.stringValue += getByte(bytecode, s, i); }
                        i--;
                        push(a);
                    }
                    else
                        { throw std::logic_error("Invalid size given for the string to store"); }
                    break;
                }

                case INST_BOOL:
                {
                    std::cout << "bool" << std::endl;
                    Value a;
                    a.type = TYPE_BOOL;
                    a.boolValue = getByte(bytecode, s, ++i) > 0;
                    push(a);
                    break;
                }

                case INST_VAR:
                {
                    std::cout << "var" << std::endl;
                    unsigned str_size = getByte(bytecode, s, ++i);
                    if (str_size > 0)
                    {
                        Value a;
                        a.type = TYPE_STRING;
                        ++i;
                        for (unsigned j=i; i - j < str_size; ++i)
                            { a.stringValue += getByte(bytecode, s, i); }
                        i--;
                        push(a);
                    }
                    else
                        { throw std::logic_error("Invalid size given for the variable name to store"); }
                    break;
                }

                case INST_SEGMENT:
                {
                    std::cout << "segment" << std::endl;
                    unsigned seg_size = getByte(bytecode, s, ++i);
                    std::string seg_name;
                    if (seg_size > 0)
                    {
                        ++i;
                        for (unsigned j=i; i - j < seg_size; ++i)
                            { seg_name += getByte(bytecode, s, i); }
                        --i;
                    }
                    else
                        { throw std::logic_error("Invalid size for the segment name"); }
                    m_segments[seg_name] = i;
                    break;
                }

                case INST_STORE_VAR:
                {
                    std::cout << "store var" << std::endl;
                    Value var_name = pop();
                    Value val = pop();
                    if (var_name.type == TYPE_STRING)
                        { m_variables[var_name.stringValue] = val; }
                    else
                        { throw std::logic_error("A variable name should be a string"); }
                    break;
                }

                case INST_PUSH_VAR:
                {
                    std::cout << "push var" << std::endl;
                    unsigned str_size = getByte(bytecode, s, ++i);
                    if (str_size > 0)
                    {
                        std::string v;
                        ++i;
                        for (unsigned j=i; i - j < str_size; ++i)
                            { v += getByte(bytecode, s, i); }
                        i--;
                        if (m_variables.find(v) != m_variables.end())
                            { push(m_variables[v]); }
                        else
                            { throw std::runtime_error("Can not push an undefined variable onto the stack"); }
                    }
                    else
                        { throw std::logic_error("Invalid size given for the variable name to fetch"); }
                    break;
                }

                case INST_JUMP:
                {
                    std::cout << "jump" << std::endl;
                    unsigned str_size = getByte(bytecode, s, ++i);
                    if (str_size > 0)
                    {
                        std::string v;
                        ++i;
                        for (unsigned j=i; i - j < str_size; ++i)
                            { v += getByte(bytecode, s, i); }
                        i--;
                        if (m_segments.find(v) != m_segments.end())
                            { i = m_segments[v]; }
                        else
                            { throw std::runtime_error("Can not jump to an undefined segment"); }
                    }
                    else
                        { throw std::logic_error("Invalid size given for the segment name to fetch"); }
                    break;
                }

                case INST_ADD:
                {
                    std::cout << "add" << std::endl;
                    Value b = pop();
                    Value a = pop();
                    if (a.type == b.type)
                    {
                        if (a.type == TYPE_INT)
                        {
                            Value c;
                            c.type = TYPE_INT;
                            c.intValue = b.intValue + a.intValue;
                            push(c);
                        }
                        else if (a.type == TYPE_STRING)
                        {
                            Value c;
                            c.type = TYPE_STRING;
                            c.stringValue = std::string(a.stringValue) + std::string(b.stringValue);
                            push(c);
                        }
                        else
                            { throw std::logic_error("Can not add two booleans"); }
                    }
                    else
                        { throw std::logic_error("Can not add two variables of heterogeneous types"); }
                    break;
                }

                default:
                {
                    // could be end of string
                    if (instruction != 0x00)
                        { throw std::runtime_error("Can not identify the instruction " + std::string(instruction, 1)); }
                }
            }
        }

        return 0;
    }

    int VM::execSegment(char* bytecode, char* segment_name)
    {
        return 0;
    }

    std::vector<Value>& VM::getStack()
    {
        return m_stack;
    }

}  // namespace vm
