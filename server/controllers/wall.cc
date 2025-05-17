#include "wall.h"
#include <boost/beast/http/status.hpp>
#include <boost/json/object.hpp>
#include <models/Wall.h>
#include <models/UserAndWall.h>
#include <models/OperationAndWall.h>
#include <models/Operation.h>
#include <models/Category.h>
#include <models/CategoryAndWall.h> // rule auto add
#include <models/User.h>
#include <string>
#include <models/CurrencyAndWall.h>
#include "systems/login.h"
#include <models/Currancy.h>
#include <math.h>
#include <numeric>
#include "bank.h"
#include "cbank.h"

response_t WallController::create(request_t request) {

	const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

	CreateDTO create{
						request->input("name"),
						request->input("is_group"),
					  	request->input("is_public"),
						request->input("lim"),
						request->input("def_currancy"),
	};
	

	const auto id_wall = wall->create(create);

	if(!id_wall) {
		return response()->json("error")
						 ->set_status(http::status::method_not_allowed);
	}

	UserToWallDTO dto_connect { std::to_string(login.id),
								std::to_string(id_wall),
								"true"};
	const auto id = user_and_wall->create(dto_connect);

	json::object json = {{"id", std::to_string(id_wall)}};
	return response()->json(json);
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

	const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

	auto find_wall_id = user_and_wall->find(std::format("id_user={}", login.id));
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
	const auto id_wall = request->input("id_wall");
	
	std::cout << id_wall << std::endl;

	auto vec_oper_wall = operation_and_wall->find(std::format("id_wall={}", id_wall));
	std::vector<std::string>operations;

	if (vec_oper_wall.size() == 0) {
		return response()->json("wall not found")
						 ->set_status(http::status::not_found);
	}
	else {
		for (const auto& wall_group : vec_oper_wall)
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

	auto category_data = category->find(std::format("id_wall={}", id_wall));
	json::array js_arr;

	for (size_t i = 0; i < category_data.size(); i++)
	{
		json::object o;
		for (size_t j = 0; j < category_data[i].size(); j++)
		{
			o[category_data[i][j].first] = category_data[i][j].second;
		}
		js_arr.emplace_back(o);
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
	json.emplace_back(js_arr);
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
			for (size_t j = 0; j < find_categorys.size(); j++)
			{
				json::object obj;
				for (size_t k = 0; k < find_categorys[j].size(); k++)
				{
					obj[find_categorys[j][k].first] = find_categorys[j][k].second;
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


// response_t WallController::get_walls_user(request_t request) {
// 	auto id_user = request->input("user_id");
// 	json::array json;
// 	std::vector<std::string> walls;

// 	if (id_user.size() == 0) {
// 		return response()->json("user not found");
// 	}
// 	else {
// 		auto user_walls = user_and_wall->find(std::format("id_user={}", id_user));
		
// 		for (const auto& wall : user_walls) 
// 		{
// 			for (const auto& pair : wall)
// 			{
// 				if (pair.first == "id_wall") {
// 					walls.push_back(pair.second);
// 					break;
// 				}
// 			}
// 		}
// 	}

// 	if (walls.size() != 0) {
// 		for (size_t i = 0; i < walls.size(); i++)
// 		{
// 			auto temp = wall->find(std::format("id={}", walls[i]));
// 			for (size_t i = 0; i < temp.size(); i++)
// 			{
// 				json::object obj;
// 				for (size_t j = 0; j < temp[i].size(); j++)
// 				{
// 					obj[temp[i][j].first] = temp[i][j].second;
// 				}
// 				json.emplace_back(obj);
// 			}
// 		}
// 	}

// 	return response()->json(json);


// }

response_t WallController::get_walls_user(request_t request) {

	const auto login = sys::Login(request);
	LOGIN_CHECK_ERROR(login)

	// auto r = request->input("id_user");

	json::array json;

	const auto vec_user_walls = user_and_wall->find<UserToWallDTO>(std::format("id_user = {}", login.id));
	
	if (vec_user_walls.size() == 0) {
		return response()->json("wall not found")
						 ->set_status(http::status::not_found);
	}

	for(const auto& user_wall: vec_user_walls) {

		const auto vec_wall = wall->find<CreateDTO>(std::format("id = {}", user_wall.second.id_wall));
		if(vec_wall.empty() || vec_wall[0].second.is_group.starts_with('f')) { continue; }

		// Convert wall dto to json
		json::object obj_wall = DTO::to_json(vec_wall[0]);

		// Get another users of wall
		const auto vec_another_user = user_and_wall->find<UserToWallDTO>(std::format("id_wall = {}", user_wall.second.id_wall));
		
		json::array all_group_users;
		for(const auto& another_user: vec_another_user) {
			all_group_users.emplace_back(another_user.second.id_user);
		}
		
		obj_wall["users"] = std::move(all_group_users);
		json.emplace_back(obj_wall);
	}

	return response()->json(json);
}

response_t WallController::get_currency_list(request_t request) {
	auto set_wall = request->input("id_wall");
	auto wall_date = wall->find(std::format("id={}", set_wall));

	if (wall_date.size() == 0) {
		return response()->json("wall not found");
	}

	// auto currancy_wall = currency_and_wall->find(std::format("id_wall={}", set_wall));
	// std::vector<std::string> currancys; 


	// for (size_t i = 0; i < currancy_wall.size(); i++)
	// {
	// 	for (size_t j = 0; j < currancy_wall[i].size(); j++)
	// 	{
	// 		if (currancy_wall[i][j].first == "id_currency") {
	// 			currancys.push_back(currancy_wall[i][j].second);
	// 		}
	// 	}
	// }
	// json::array json;

	// if (!currancys.empty()) {
	// 	for (size_t i = 0; i < currancys.size(); i++)
	// 	{
	// 		auto current_currancy = currancy->find(std::format("id={}", currancys[i]));
	// 		for (size_t j = 0; j < current_currancy.size(); j++)
	// 		{
	// 			json::object obj;
	// 			for (size_t k = 0; k < current_currancy[j].size(); k++)
	// 			{
	// 				obj[current_currancy[j][k].first] = current_currancy[j][k].second;
	// 			}
	// 			json.emplace_back(obj);
	// 		}
	// 	}

	// 	return response()->json(json);
	// }


	return response()->json("some data");
}


response_t WallController::get_sum_operation_wall(request_t request) {
	auto id_wall = request->input("id_wall");

	auto wall_id = wall->find(std::format("id={}", id_wall));

	if (wall_id.size() == 0) {
		return response()->json("wall not found")->set_status(http::status::not_found);
	}

	auto operation_wall = operation_and_wall->find(std::format("id_wall={}", id_wall));

	std::vector<std::string> operations;

	for (const auto& operation : operation_wall)
	{
		for (const auto& pair : operation)
		{
			if (pair.first == "id_operation") {
				operations.push_back(pair.second);
				break;
			}
		}
	}
	std::vector<int>sum;

	if (operations.size() != 0) {
		for (size_t i = 0; i < operations.size(); i++)
		{
			auto temp = operation->find(std::format("id={}", operations[i]));
			for (const auto& value : temp)
			{
				for (const auto& pair : value)
				{
					if (pair.first == "value") {
						sum.push_back(std::stoi(pair.second));
						break;
					}
				}
			}
		}

	auto default_curr = wall_id[0][5].second;

	std::cout << default_curr << std::endl; 
	int s = std::reduce(sum.begin(), sum.end(), 0);

	json::object obj;

	if (default_curr == "rub") {
		obj["sum"] = std::to_string(s);
		return response()->json(obj);
		}
		else {
			BankRequestDTO rate = { default_curr, "17.05.2025" };
			std::unique_ptr<sys::CBank>bank = std::make_unique<sys::CBank>(rate.date);
			bank->start_work();
			std::string currancy = bank->get_currency(rate.iso);
			int currancy_sum = s * std::stof(currancy);

			obj["sum"] = std::to_string(currancy_sum);

			return response()->json(obj);

		}
	}


		return response()->json("some data");

	}

response_t WallController::get_summ_anothers_curr(request_t request) {
	auto id_wall = request->input("id_wall");

	auto wall_id = wall->find(std::format("id={}", id_wall));

	if (wall_id.size() == 0) {
		return response()->json("wall not found")->set_status(http::status::not_found);
	}
	auto default_curr = wall_id[0][5].second;

	if (default_curr != "rub") {
		auto operation_wall = operation_and_wall->find(std::format("id_wall={}", id_wall));
		json::array json;

		std::vector<std::string> operations;

		for (const auto& operation : operation_wall)
		{
			for (const auto& pair : operation)
			{
				if (pair.first == "id_operation") {
					operations.push_back(pair.second);
					break;
				}
			}
		}

		std::vector<int>value;

		if (operations.size() != 0) {
			for (size_t i = 0; i < operations.size(); i++)
			{
				auto operation_value = operation->find(std::format("id={}", operations[i]));
				for (const auto& o : operation_value) {
					for (const auto& pair : o)
					{
						if (pair.first == "value") {
							value.push_back(std::stoi(pair.second));
						}
					}
				}
			}
		}
		
		/*for (size_t i = 0; i < value.size(); i++)
		{
			json::object obj;
			if (value[i] > 0) {
				obj["deposit"] = value[i];
			}
			else if(value[i] < 0) {
				obj
			}
		}
		*/

	}
	else {
		return response()->json("some data");
	}

	return response()->json("some data");
}

response_t WallController::get_currency(request_t request) {
	auto vac_currancy = currancy->find(std::format("id != 0"));
	
	if (vac_currancy.size() == 0) {
		return response()->json("currancy is empty!");
	}
	
	json::array json;

	for (size_t i = 0; i < vac_currancy.size(); i++)
	{
		json::object obj;
		for (size_t j = 0; j < vac_currancy[i].size(); j++)
		{
			obj[vac_currancy[i][j].first] = vac_currancy[i][j].second;
		}
		json.emplace_back(obj);
	}

	return response()->json(json);


	
}