#include <iostream>
#include "wall.h"
#include <isce/Route.h>



using namespace isce;

void Route::up() {

  Route::prefix("api/ref")->middleware({})->group({
    Route::post("/wall", WallController::create),  
    Route::post("/register", WallController::update),
    Route::get("/me", WallController::get),
    Route::delete_("/out",WallController::delete_)
  });

}
