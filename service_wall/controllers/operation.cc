#include "category.h"
#include <models/Operation.h>

std::unique_ptr<Model> operation = std::make_unique<Operation>("category");

response_t OperationController::create(request_t request) {
	CreateOperationDTO create{
									request->input("value"),
									request->input("id_currency"),
									request->input("id_user") };


	auto id = operation->create({ "value", "id_currency", "id_user" }, {create.value, create.id_currency, create.id_user });

	if (id) {
		return response()->json("created operation is successfully");
	}
	else {
		return response()->json("error")->set_status(http::status::method_not_allowed);
	}

}

response_t OperationController::update(request_t request) {
	UpdateCategoryDTO update{
									request->input("icon_new"),
									request->input("name_new"),
									request->input("id_wall_new") };

	conditionsDTO condition = { request->input("id") };
	

	
	auto temp = operation->update(
		{
			std::format("icon={}", update.icon),
			std::format("name='{}'", update.name),
			std::format("id_wall={}",update.id_wall)
		},
	{
		std::format("id='{}'", condition.id),
	});
	
	if (temp) {
		return response()->json("updated category successfully");
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

	auto searh_category = operation->find(std::format("id={}", condition.id));

	if (searh_category.size() == 0) {
		return response()->json("category not found")->set_status(http::status::not_found);
	}
	else {
		category->delete_(condition.id);
		return response()->json("category deleted successfully")->set_status(http::status::ok);
	}
	
	
}
