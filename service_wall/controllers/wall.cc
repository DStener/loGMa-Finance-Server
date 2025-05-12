#include "wall.h"
#include <models/Wall.h>

std::unique_ptr<Model> wall = std::make_unique<Wall>("wall");

response_t WallController::create(request_t request) {
	CreateDTO create{
									request->input("name"),
									request->input("is_group"),
									request->input("is_public") };


	auto id = wall->create({ "name", "is_group", "is_public" }, { create.name, create.is_group, create.is_public });

	if (id) {
		return response()->json("created wall is successfully");
	}
	else {
		
		return response()->json("error")
											->set_status(http::status::method_not_allowed);

	}

}

response_t WallController::update(request_t request) {


	UpdateDTO update{
									request->input("name_new"),
									request->input("is_group_new"),
									request->input("is_public_new") };

	conditionsDTO condition = {request->input("id")};

	auto temp = wall->update(
			{
				std::format("name='{}'", update.name),
				std::format("is_group={}", update.is_group),
				std::format("is_public={}",update.is_public)
			},
		{
			std::format("id='{}'", condition.id),
		});
		
	if (temp) {
		return response()->json("updated wall successfully");
	}
	else {
		return response()->json("error");
	}
	
}


response_t WallController::get(request_t request){
	
	return response()->json("Data");
}

response_t WallController::delete_(request_t request) {
	conditionsDTO condition = { request->input("id") };

	auto searh_wall = wall->find(std::format("id={}", condition.id));

	if (searh_wall.size() == 0) {
		return response()->json("wall not found")->set_status(http::status::not_found);
	}
	else {
		wall->delete_(condition.id);
		return response()->json("wall deleted successfully")->set_status(http::status::ok);
	}	 

}
