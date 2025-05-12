#include "auth.h"
#include "models/User.h"


std::unique_ptr<Model> user = std::make_unique<User>("users");

response_t Auth::registration(request_t request) {

	RegisterDTO reg{ request->input("login"),
									 request->input("name"),
									 request->input("surname"),
		               request->input("patronymic"),
		               request->input("birthday"),
		               request->input("password") };
	
	
	user->create({"login", "name", "surname", "patronymic", "birthday", "password" },
		{ reg.login, reg.name, reg.surname, reg.patronymic, reg.birthday, reg.password });



	return response()->json("Created user successfully");
}

response_t Auth::login(request_t request) {

	LoginDTO login{ request->input("login"),
									request->input("password") };

	

	if (user->where_("login", login.login) ){
		if (user->where_("password", login.password)) {
			auto temp = user->find(std::format("login = '{}' AND password = '{}'", login.login, login.password));

			for (const auto& row : temp)
			{
				std::cout << std::endl;
				for (const auto& value : row)
				{
					std::cout << value.first << ":" << value.second << ' ';
				}
			}

			return response()->json("so cool"); // token or next page

		}
	}
	
	
	return response()->json("error");
	

}


response_t Auth::me(request_t request){
	
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