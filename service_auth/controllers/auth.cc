#include "auth.h"
#include "models/User.h"
#include "models/Token.h"


std::unique_ptr<Model> user = std::make_unique<User>("users");
std::unique_ptr<Model> token = std::make_unique<Token>("token");

response_t Auth::registration(request_t request) {

	RegisterDTO reg{ request->input("login"),
									 request->input("name"),
									 request->input("surname"),
		               request->input("patronymic"),
		               request->input("birthday"),
		               request->input("password") };
	
	
	user->create({ "login", "name", "surname", "patronymic", "birthday", "password" },
		{ reg.login, reg.name, reg.surname, reg.patronymic, reg.birthday, reg.password });

	return response()->json("error")
		               ->cookie("token=fjkegwfhjkeghjkfegfhj");
}

response_t Auth::login(request_t request) {

	LoginDTO login{ request->input("login"),
									request->input("password") };

	std::cout << "Token: " << request->cookie("token").value_or("") << std::endl;


	//if (user->where_("login", login.login) ){
	//	if (user->where_("password", login.password)) {
	//		auto temp = user->find(std::format("login = '{}' AND password = '{}'", login.login, login.password));

	//		for (const auto& row : temp)
	//		{
	//			std::cout << std::endl;
	//			for (const auto& value : row)
	//			{
	//				std::cout << value.first << ":" << value.second << ' ';
	//			}
	//		}

	//		return response()->json("so cool"); // token or next page

	//	}
	//}
	
	
	return response()->json("error");
	

}


response_t Auth::me(request_t request) {
	
	const auto value_token = request->cookie("token");
	auto db_token = token->find(std::format("token = '{}'", value_token.value_or("")));

	// Return error
	if (db_token.size() == 0) {
		return response()->json("Not authorized")
										 ->set_status(http::status::unauthorized);
	}

	// 


	return response()->json("Data");
}

response_t Auth::out(request_t request) {

	if (request->input("id") != "") {

	}

	return response()->json("Data");
}

response_t Auth::sessions(request_t request) {
	return response()->json("Data");;
}

response_t Auth::out_all(request_t request) {
	return response()->json("Data");
}