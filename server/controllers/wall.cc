#include "wall.h"
#include <models/Wall.h>
#include <models/UserAndWall.h>
#include <models/OperationAndWall.h>
#include <models/Operation.h>
#include <models/Category.h>
#include <models/CategoryAndWall.h> // rule auto add
#include <models/User.h>


response_t WallController::create(request_t request) {
	CreateDTO create{request->input("name"),
						       request->input("is_group"),
						       request->input("is_public") };


	const auto id = wall->create(create);

	if (id) {
		return response()->json("created wall is successfully");
	} else {
		
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

response_t WallController::add_user(request_t request) {
	UserToWallDTO add = { request->input("id_user"), request->input("id_wall"), request->input("is_admin")};
	
	auto id_user_and_wall = user_and_wall->create({ "id_user", "id_wall", "is_admin" }, {add.id_user, add.id_wall, add.is_admin});
	
	if (id_user_and_wall) {
		return response()->json("relationship added successfully");
	}
	else {

		return response()->json("error")
			->set_status(http::status::method_not_allowed);

	}


}



response_t WallController::get_user_wall(request_t request) {
	GetUserWall get = { request->input("id_user") };
	auto user_id = user->find(std::format("id={}", get.id_user));

	if (user_id.size() == 0) {
		return response()->json("user not found");
	}

	auto find_wall_id = user_and_wall->find(std::format("id_user={}", get.id_user));
	auto wall_id = find_wall_id[0][2].second;

	auto find_data = wall->find(std::format("id={}", wall_id));

	std::string data;

	json::array json;


	for (size_t i = 0; i < find_data.size(); i++)
	{
		json::object obj;
		for (size_t j = 0; j < find_data[i].size(); j++)
		{
			obj[find_data[i][j].first] = find_data[i][j].second;

		}

		json.emplace_back(std::move(obj));

	}


	return response()->json(json);

}

response_t WallController::get_operation_wall(request_t request) {
	OperationAndWallDTO get{ request->input("id_wall") };
	auto id_wall = operation_and_wall->find(std::format("id_wall={}", get.id_wall));
	std::vector<std::string>operations;

	if (id_wall.size() == 0) {
		return response()->json("wall not found");
	}
	else {
		for (const auto& wall_group : id_wall)
		{
			for (const auto& pair : wall_group)
			{
				if (pair.first == "id_operation") {
					operations.push_back(pair.second);
					break; 
				}
			}
		}

	}

	json::array json;

	if (operations.size() != 0) {
		for (size_t i = 0; i < operations.size(); i++)
		{
			auto find_operation = operation->find(std::format("id={}", operations[i]));
			json::object obj;
			for (size_t i = 0; i < find_operation.size(); i++)
			{
				json::object obj;
				for (size_t j = 0; j < find_operation[i].size(); j++)
				{
					obj[find_operation[i][j].first] = find_operation[i][j].second;
				}
				json.emplace_back(obj);
			}


		}
	}
	
	return response()->json(json);

}

response_t WallController::get_category_wall(request_t request) {
	CategoryAndWallDTO get{ request->input("id_wall") };
	auto find_id_wall = rule_auto_add->find(std::format("id_wall={}", get.id_wall));
	std::vector<std::string>categorys;
	json::array json;

	if (find_id_wall.size() == 0) {
		return response()->json("wall not found")->set_status(http::status::not_found);
	}
	else {
		for (const auto& category_group : find_id_wall)
		{
			for (const auto& pair : category_group) {
				if (pair.first == "id_category") {
					categorys.push_back(pair.second);
					break;
				}
			}
		}
	}

	if (categorys.size() != 0) {
		for (size_t i = 0; i < categorys.size(); i++)
		{
			auto find_categorys = category->find(std::format("id={}", categorys[i]));
			for (size_t i = 0; i < find_categorys.size(); i++)
			{
				json::object obj;
				for (size_t j = 0; j < find_categorys[i].size(); j++)
				{
					obj[find_categorys[i][j].first] = find_categorys[i][j].second;
				}
				json.emplace_back(obj);
			}

		}
	}

	return response()->json(json);



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
