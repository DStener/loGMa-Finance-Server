#include "category.h"
#include <models/Category.h>
#include <models/Wall.h>
#include <models/CategoryAndWall.h>

response_t CategoryController::create(request_t request) {

	CreateCategoryDTO create{
									request->input("icon"),
									request->input("name"),
									request->input("id_wall") };

	auto find_wall = wall->find(std::format("id={}", create.id_wall));

	if (find_wall.size() == 0) {
		return response()->json("wall not found")->set_status(http::status::not_found);
	}

	auto id = category->create({ "icon", "name", "id_wall" }, { create.icon, create.name, create.id_wall});

	rule_auto_add->create({ "id_category", "id_wall" }, { std::to_string(id), create.id_wall });

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

response_t CategoryController::set_limit(request_t request) {
	UpdateCategoryLimitsDTO categorydto{ request->input("id_category"), request->input("new_limit") };
	auto id_category = category->find(std::format("id={}", categorydto.id_category));
	std::vector<std::string>cur_limit;


	if (id_category.size() == 0) {
		return response()->json("category not found");
	}
	else {
		 /*current limit*/
		for (const auto& current_limit : id_category)
		{
			for (const auto& pair : current_limit) {
				if (pair.first == "limits") {
					cur_limit.push_back(pair.second);
					break;
				}
			}
		}
	}

	if (cur_limit.size() != 0) {
		category->update({ categorydto.new_limit }, { std::format("limit={}", cur_limit[0]) });
		return response()->json("limit updated successfully")->set_status(http::status::method_not_allowed);
	}
	else {
		return response()->json("error updated")->set_status(http::status::method_not_allowed);
	}
	return response()->json("error updated")->set_status(http::status::method_not_allowed);

}