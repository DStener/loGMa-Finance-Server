#include "auth.h"
#include "models/User.h"
#include "models/Token.h"
#include <format>
#include <isce/Utils.h>
#include "systems/login.h"

response_t Auth::registration(request_t request) {

	RegisterDTO reg{ request->input("login"),
					 "1",
					 request->input("name"),
					 request->input("surname"),
					 request->input("patronymic"),
					 request->input("birthday"),
					 request->input("password") };
	
	user->create(reg);

	return response()->json("SUCCES")
		               ->set_status(http::status::created);
}

response_t Auth::login(request_t request) {

	const auto login_v = request->input("login");
	const auto password_v = request->input("password");

	std::cout << "STD: " <<  login_v << std::endl;

	const auto login = sys::Login(login_v, password_v);
	LOGIN_CHECK_ERROR(login)

	TokenDTO dto_token {Utils::generate_token(),
											std::to_string(login.id),
	                    "2020-02-02"};


	// Insert value to DB
	token->create(dto_token);

	return response()->json("SUCCES")
				           ->cookie(std::format("token={}",dto_token.token));
}

response_t Auth::me(request_t request) {
	
	std::cout << "CALL" << std::endl;

	const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

	auto json = DTO::to_json(login.user);
	json.erase("password");

	return response()->json(json);
}

response_t Auth::update(request_t request) {

	std::cout << "THIS" << std::endl;
	
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

response_t Auth::out(request_t request) {

	const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

  	const auto id = request->input("id");

	if (!id.empty()) {
		token->cdelete(std::format("id_user = {}", id));
	} else {
		token->cdelete(std::format("id_user = {}", login.id));
	}

	return response()->json("SUCCES");
}

response_t Auth::sessions(request_t request) {

	const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

	const auto condition = std::format("id_user = {}", login.id);
	const auto token_vec = token->find<TokenDTO>(condition);

	const auto json = DTO::to_json(token_vec);

	return response()->json("Data");;
}

response_t Auth::out_all(request_t request) {

	json::array test;
	test.emplace_back("");

	const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

  const auto condition = std::format("id_user = {}", login.id);
	token->delete_(condition);

	return response()->json("Data");
}