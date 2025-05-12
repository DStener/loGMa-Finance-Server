#include <iostream>
#include "wall.h"
#include <isce/Route.h>
#include <category.h>


using namespace isce;

void Route::up() {

  Route::prefix("api/ref")->middleware({})->group({

    Route::post("/wall", WallController::create),  
    Route::put("/wall", WallController::update),
    Route::get("/get_wall", WallController::get),
    Route::delete_("/del_wall",WallController::delete_),

    // category
    Route::post("/category",CategoryController::create),
    Route::put("/category",CategoryController::update),
    Route::get("/get_category",CategoryController::get),
    Route::delete_("/del_category",CategoryController::delete_),
  });

}
