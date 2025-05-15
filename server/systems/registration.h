#pragma once 

#include <string>

#include "dto.h"



#define CHECK_AND_MESSAGE(condition, txt)                 \
if(condition) {                                           \
    message = txt;                                        \
    return;                                               \
}


namespace sys {
class Register {
public:
    std::string message;

    Register(RegisterDTO reg) 
        : _reg(std::move(reg)) {
        
    }
private:
    RegisterDTO _reg;
};
} // namespace sys