#include "wall.h"
#include <models/Wall.h>

std::unique_ptr<Model> wall = std::make_unique<Wall>("wall");

response_t WallController::create(request_t request) {
	CreateDTO create{
									request->input("name"),
									request->input("is_group"),
									request->input("is_public") };


	wall->create({ "name", "is_group", "is_public" }, { create.name, create.is_group, create.is_public });

	
}

response_t WallController::update(request_t request) {

	UpdateDTO update{
									request->input("name"),
									request->input("is_group"),
									request->input("is_public") };
	
	
	wall->update()

	return response()->json("error");
	

}


response_t WallController::get(request_t request){
	
	return response()->json("Data");
}

response_t WallController::delete_(request_t request) {


	return response()->json("Data");
}
