#ifndef vm_utils
#define vm_utils

#include <vector>
#include <string>
#include <sstream>

namespace vm
{
    namespace abc
    {

        template<typename T>
        T pop(std::vector<T>& obj, std::size_t i)
        {
            T element {};

            if (0 <= i && i < obj.size())
            {
                element = obj[i];
                obj.erase(obj.begin() + i);
            }
            else if (i < 0 && (-i) < obj.size())
            {
                element = obj[obj.size() + i];
                obj.erase(obj.begin() + obj.size() + i);
            }

            return element;
        }

        template<typename T>
        void pop_no_return(std::vector<T>& obj, std::size_t i)
        {
            if (0 <= i && i < obj.size())
                obj.erase(obj.begin() + i);
            else if (i < 0 && (-i) < obj.size())
                obj.erase(obj.begin() + obj.size() + i);
        }

        template<typename T>
        std::string str(const T& n)
        {
            std::ostringstream stm;
            stm << n;
            return stm.str();
        }

        template<typename T>
        T str_to(const std::string& v)
        {
            T t; std::stringstream b(v);
            b >> t;
            return t;
        }

    }  // namespace abc
}  // namespace abc

#endif // vm_utils
