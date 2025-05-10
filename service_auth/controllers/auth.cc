#include "auth.h"


response_t Auth::registration(request_t request) {

	RegisterDTO reg{ request->input("login"),
									 request->input("name"),
									 request->input("surname"),
		               request->input("patronymic"),
		               request->input("birthday"),
		               request->input("password") };


	return response()->json("Data");
}

response_t Auth::login(request_t request) {

	LoginDTO login{ request->input("login"),
									request->input("password") };

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