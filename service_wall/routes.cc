#include <iostream>
#include "wall.h"
#include <isce/Route.h>



using namespace isce;

void Route::up() {

  Route::prefix("api/ref")->middleware({})->group({
    Route::post("/wall", WallController::create),  
    Route::put("/wall", WallController::update),
    Route::get("/get", WallController::get),
    Route::delete_("/del",WallController::delete_)
  });

}
