#pragma once 

#include <format>
#include <string>

#include "dto.h"
#include <isce/Request.h>

#include "models/User.h"
#include "models/Wall.h"
#include "models/UserAndWall.h"

#define CHECK_AND_MESSAGE(condition, txt)                 \
if(condition) {                                           \
    message = txt;                                        \
    return;                                               \
}


namespace sys {
class Register {
public:
    std::string message;

    Register(const request_t& request) {
        
        RegisterDTO reg{ request->input("login"),
                         "1",
                         request->input("name"),
                         request->input("surname"),
                         request->input("patronymic"),
                         request->input("birthday"),
                         request->input("password") };
        
        CreateDTO create{std::format("Wall of user {}", reg.login),
						 "false",
						 "false",
                         "20000",
                         "RUB"};


        const auto id_user = user->create(reg);
	    const auto id_wall = wall->create(create);

        UserToWallDTO dto_user_and_wall = {std::to_string(id_user), 
                                            std::to_string(id_wall), 
                                            "true"};

        const auto id = user_and_wall->create(dto_user_and_wall);
    }
};
} // namespace sys