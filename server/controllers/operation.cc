#include "operation.h"
#include <models/Operation.h>
#include <models/User.h>

std::unique_ptr<Model> operation = std::make_unique<Operation>("operation");

response_t OperationController::create(request_t request) {
	OperationCreateDTO create{
									request->input("value"),
									request->input("id_currency"),
									request->input("id_user")};

	auto user_id = user->find(std::format("id={}", create.id_user));

	if (user_id.size() == 0) {
		return response()->json("user not found")->set_status(http::status::not_found);
	}

	auto id = operation->create({ "value", "id_currency", "id_user" }, { create.value, create.id_currency, create.id_user });


	if (id) {
		return response()->json("created operation successfully");
	}
	else {
		return response()->json("error")->set_status(http::status::method_not_allowed);
	}

}

response_t OperationController::update(request_t request) {
	OperationUpdateDTO update{
									request->input("value_new"),
									request->input("id_currency_new"),
									request->input("id_user_new")};

	conditionsDTO condition = { request->input("id") };
	
	auto temp = operation->update(
		{
			std::format("value={}", update.value),
			std::format("id_currency={}", update.id_currency),
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
