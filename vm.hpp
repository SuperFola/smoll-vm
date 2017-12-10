#ifndef vm_vm
#define vm_vm

#include "instructions.hpp"
#include "value.hpp"
#include "utils.hpp"

#include <map>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

namespace vm
{

    class VM
    {
    private:
        int m_stack_size;
        std::vector<Value> m_stack;
        // variable name => Value
        std::map<std::string, Value> m_variables;
        // just keeping the position of the segments
        std::map<std::string, unsigned> m_segments;

        void push(Value value);
        Value pop();
        void clear();
        char getByte(char* bytecode, unsigned s, unsigned i);

    public:
        VM();
        ~VM();

        int exec(char* bytecode, unsigned s);
        int execSegment(char* bytecode, char* segment_name);

        std::vector<Value>& getStack();
    };

}  // namespace vm

#endif // vm_vm
