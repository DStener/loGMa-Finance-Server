#include "category.h"
#include <models/Category.h>

std::unique_ptr<Model> category = std::make_unique<Category>("category");

response_t CategoryController::create(request_t request) {
	CreateCategoryDTO create{
									request->input("icon"),
									request->input("name"),
									request->input("id_wall") };


	auto id = category->create({ "icon", "name", "id_wall" }, { create.icon, create.name, create.id_wall});

	if (id) {
		return response()->json("created category successfully");
	}
	else {
		return response()->json("error")->set_status(http::status::method_not_allowed);
	}

}

response_t CategoryController::update(request_t request) {
	UpdateCategoryDTO update{
									request->input("icon_new"),
									request->input("name_new"),
									request->input("id_wall_new") };

	conditionsDTO condition = { request->input("id") };
	

	
	auto temp = category->update(
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


response_t CategoryController::get(request_t request){
	
	return response()->json("Data");
}

response_t CategoryController::delete_(request_t request) {
	conditionsDTO condition = { request->input("id") };

	auto searh_category = category->find(std::format("id={}", condition.id));

	if (searh_category.size() == 0) {
		return response()->json("category not found")->set_status(http::status::not_found);
	}
	else {
		category->delete_(condition.id);
		return response()->json("category deleted successfully")->set_status(http::status::ok);
	}
	
	
}
