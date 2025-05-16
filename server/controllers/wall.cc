#include "wall.h"
#include <boost/beast/http/status.hpp>
#include <models/Wall.h>
#include <models/UserAndWall.h>
#include <models/OperationAndWall.h>
#include <models/Operation.h>
#include <models/Category.h>
#include <models/CategoryAndWall.h> // rule auto add
#include <models/User.h>

#include "systems/login.h"


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


response_t WallController::get_walls_user(request_t request) {

	/*const auto login = sys::Login(request)*/;
	//LOGIN_CHECK_ERROR(login)

	// возврощаем все стены пользователя is_group == true

	auto t = request->input("id_user");
	auto is_group_true = wall->find(std::format("id_user={} AND is_group=true", t));
	
	std::vector<std::string>walls; // index_walls 

	json::array json;

	// 
	for (const auto& row : is_group_true)
	{
		std::string wall_id;
		for (const auto& pair : row)
		{
			if (pair.first == "id") {
				wall_id = pair.second;
				break;
			}
		}

		if (!wall_id.empty()) {
			// Ищем записи в user_and_wall по wall_id
			auto temp = user_and_wall->find(std::format("id_user={}", wall_id));
			for (size_t k = 0; k < temp.size(); k++) {
				json::object obj;

				for (size_t j = 0; j < temp[k].size(); j++) {
					if (temp[k][j].first == "id_user" && temp[k][j].second == t) {
						obj[temp[k][j].first] = temp[k][j].second;
					}
				}

				if (!obj.empty()) {
					json.emplace_back(obj);
				}
			}
		}
	}


	//auto wall_id = find_wall_id[0][2].second; // id_wall

	//auto find_data = wall->find(std::format("id={}", wall_id)); // wall 
	//auto ig = user_and_wall->find(std::format("id_wall={}", wall_id)); // все wall с этим id

	//std::vector<std::string>walls; // все id в user_and_wall
	//

	//for (size_t i = 0; i < ig.size(); i++)
	//{
	//	for (size_t j = 0; j < ig[i].size(); j++)
	//	{
	//		auto temp = user_and_wall->find("id_user={}")
	//	}

	//}
	//auto temp = wall->find(std::format("id={} AND is_group={}", ig[i][j].second, "true"));
	//auto temp = wall->find(std::format("id={}")) // поиск всех wall с таким id
	
	
	/*std::string data;
	json::array json;

	if (is_group.size() > 0) {
		for (size_t i = 0; i < is_group.size(); i++)
		{
			json::object obj;
			for (size_t j = 0; j < is_group[i].size(); j++)
			{
				obj[is_group[i][j].first] = is_group[i][j].second;
			}
			json.emplace_back(std::move(obj));
		}

		return response()->json(json);
	}*/


	return response()->json("some error");

}

// all operation wall
response_t WallController::get_operation_wall(request_t request) {
	OperationAndWallDTO get{ request->input("id_wall") };
	auto id_wall = operation_and_wall->find(std::format("id_wall={}", get.id_wall));
	std::vector<std::string>operations;

	if (id_wall.size() == 0) {
		return response()->json("wall not found")
						 ->set_status(http::status::not_found);
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
		return response()->json("wall not found")
						 ->set_status(http::status::not_found);
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
	auto wall_id = request->input("wall_id");

	auto size_wall = wall->find(std::format("id={}", wall_id));
	json::array json;


	if (size_wall.size() == 0) {
		return response()->json("wall not found!");
	}
	else {
		for (size_t i = 0; i < size_wall.size(); i++)
		{
			json::object obj;
			for (size_t j = 0; j < size_wall[i].size(); j++)
			{
				obj[size_wall[i][j].first] = size_wall[i][j].second;
			}
			json.emplace_back(obj);

		}
	}

	return response()->json(json);

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


response_t WallController::get_user_wall(request_t request) {
	auto id_user = request->input("user_id");
	json::array json;
	std::vector<std::string> walls;
	
	// if flag is_group == false return obj json возврощает его стену
	if (id_user.size() == 0) {
		return response()->json("user not found");
	}
	else {
		auto user_walls = user_and_wall->find(std::format("id_user={}", id_user));
		
		for (const auto& wall : user_walls) 
		{
			for (const auto& pair : wall)
			{
				if (pair.first == "id_wall") {
					walls.push_back(pair.second);
					break;
				}
			}
		}
	}

	if (walls.size() != 0) {
		for (size_t i = 0; i < walls.size(); i++)
		{
			auto temp = wall->find(std::format("id={}", walls[i]));
			for (size_t i = 0; i < temp.size(); i++)
			{
				json::object obj;
				for (size_t j = 0; j < temp[i].size(); j++)
				{
					obj[temp[i][j].first] = temp[i][j].second;
				}
				json.emplace_back(obj);
			}
		}
	}

	// return wall его
	return response()->json(json);


}

response_t WallController::get_currency_list(request_t request) {
	auto set_wall = request->input("id_wall");
	auto wall_date = wall->find(std::format("id={}", set_wall));

	if (wall_date.size() == 0) {
		return response()->json("wall not found")->set_status(http::status::not_found);
	}





	return response()->json("data");


}