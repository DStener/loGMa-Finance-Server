#include "auth.h"
#include "models/User.h"

std::shared_ptr<User>user;


response_t Auth::registration(request_t request) {

	RegisterDTO reg{ request->input("login"),
									 request->input("name"),
									 request->input("surname"),
		               request->input("patronymic"),
		               request->input("birthday"),
		               request->input("password") };

	user->create("users", { "login", "name", "surname", "patronymic", "birthday", "password" },
		{ reg.login, reg.name, reg.surname, reg.patronymic, reg.birthday, reg.password });



	return response()->json("Created user successfully");
}

response_t Auth::login(request_t request) {

	LoginDTO login{ request->input("login"),
									request->input("password") };

	

	if (user->where_("users", "login", login.login) ){
		if (user->where_("users", "password", login.password)) {
			return response()->json("Data"); // token or next page
		}
	}
	
	
	return response()->json("Data");
	

}


response_t Auth::me(request_t request) {
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