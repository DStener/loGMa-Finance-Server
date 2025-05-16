#include "user.h"
#include "dto.h"

response_t UserCNT::avatar(request_t request) {

	std::string id_user = request->input("id_user");

	// If not parmetr, get current user id
	if(id_user.empty() || id_user == "0") {

		const auto login = sys::Login(request);
		LOGIN_CHECK_ERROR(login)

		id_user = std::to_string(login.id);
	}

	const auto vec_user = user->find<RegisterDTO>(std::format("id = {}", id_user));
	if(vec_user.empty()) { return response()->not_found("NOT FOUND"); }

	const auto file_vec= file->find<FileDTO>(std::format("id = {}", vec_user[0].second.avatar));
	if(file_vec.empty()) { return response()->not_found("NOT FOUND"); }

	return response()->file(file_vec[0].second.path);
}

response_t UserCNT::update(request_t request) {
    const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

	RegisterDTO reg{ request->input("login"),
					 request->input("avatar"),
					 request->input("name"),
					 request->input("surname"),
					 request->input("patronymic"),
					 request->input("birthday"),
					 request->input("password") };
	
	const auto message = user->update(reg, std::format("id = {}", login.id));

	if(!message.empty()) {
		return response()->json(message)
		               	 ->set_status(http::status::range_not_satisfiable);
	}

	return response()->json("SUCCES");
}