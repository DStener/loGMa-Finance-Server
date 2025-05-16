#include "user.h"

response_t UserCNT::avatar(request_t request) {
    return response()->json("");
}

response_t UserCNT::update(request_t request) {
    // const auto login = sys::Login(request);
	// LOGIN_CHECK_ERROR(login)

	// RegisterDTO reg{ request->input("login"),
	// 				 request->input("avatar"),
	// 				 request->input("name"),
	// 				 request->input("surname"),
	// 				 request->input("patronymic"),
	// 				 request->input("birthday"),
	// 				 request->input("password") };
	
	// const auto message = user->update(reg, std::format("id = {}", login.id));

	// if(!message.empty()) {
	// 	return response()->json(message)
	// 	               	 ->set_status(http::status::range_not_satisfiable);
	// }

	return response()->json("SUCCES");
}