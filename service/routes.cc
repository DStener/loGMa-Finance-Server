#include <iostream>

#include <isce/Route.h>

#include "auth.h"
#include "wall.h"
#include "category.h"
#include "operation.h"

using namespace isce;

void Route::up() {

  Route::prefix("api/auth")->middleware({})->group({
    Route::get("/login", Auth::login),  
    Route::get("/reg", Auth::registration),
    Route::get("/me", Auth::me),
    Route::post("/out", Auth::out),
    Route::post("/out/{id}", Auth::out),
    Route::post("/out_all", Auth::out_all),
    Route::get("/sessions", Auth::sessions),

  });

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
    
    // opreation
    Route::post("/opreation", OperationController::create),
    Route::put("/opreation", OperationController::update),
    Route::get("/get_opreation", OperationController::get),
    Route::delete_("/del_opreation", OperationController::delete_)

    });

  

}
