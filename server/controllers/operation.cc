#include "operation.h"
#include <boost/json/serializer.hpp>
#include <models/Operation.h>
#include <models/User.h>
#include <models/OperationAndWall.h>

#include <systems/login.h>

response_t OperationController::create(request_t request) {

	const auto login = sys::Login(request);
  	LOGIN_CHECK_ERROR(login)

	OperationDTO dto_oper {
		request->input("value"),
		request->input("description"),
		request->input("iso_currency"),
		std::to_string(login.id),
		request->input("time"),
	};

	std::cout << json::serialize(DTO::to_json(dto_oper)) << std::endl; 

	const auto id_wall = request->input("id_wall");
	const auto id = operation->create(dto_oper);

	// if (!id_wall.empty()) {
	// 	operation_and_wall->create({ "id_opreation", "id_wall" }, { std::to_string(id), id_wall });
	// }

	json::object json = { {"id", std::to_string(id)} };

	if (id) {
		return response()->json(json);
	}
	else {
		return response()->json("error")->set_status(http::status::method_not_allowed);
	}

}


response_t OperationController::update(request_t request) {
	OperationUpdateDTO update{
									request->input("value_new"),
									request->input("iso_currency_new"),
									request->input("id_user_new")};

	conditionsDTO condition = { request->input("id") };
	
	auto temp = operation->update(
		{
			std::format("value={}", update.value),
			std::format("iso_currency={}", update.iso_currency),
			std::format("id_user={}",update.id_user)
		},
	{
		std::format("id='{}'", condition.id),
	});
	
	if (temp) {
		return response()->json("updated operation successfully");
	}
	else {
		return response()->json("error");
	}
	
}

response_t OperationController::get(request_t request){
	
	return response()->json("Data");
}

response_t OperationController::delete_(request_t request) {
	conditionsDTO condition = { request->input("id") };

	auto search_operation = operation->find(std::format("id={}", condition.id));

	if (search_operation.size() == 0) {
		return response()->json("operation not found")->set_status(http::status::not_found);
	}
	else {
		operation->delete_(condition.id);
		return response()->json("opertaion deleted successfully")->set_status(http::status::ok);
	}
	
	
}


