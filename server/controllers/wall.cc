#include "wall.h"
#include <models/Wall.h>
#include <models/UserAndWall.h>
#include <models/User.h>

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

response_t WallController::add_user(request_t request) {
	UserToWall add = { request->input("id_user"), request->input("id_wall"), request->input("is_admin")};
	
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
	// у стены можно запросить стену пользовтеля
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
			//data += find_data[i][j].first + " " + find_data[i][j].second + ' ';
			obj[find_data[i][j].first] = find_data[i][j].second;

		}

		json.emplace_back(std::move(obj));

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
