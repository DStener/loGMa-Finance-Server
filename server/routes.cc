#include <iostream>

#include <isce/Route.h>

#include "auth.h"
#include "wall.h"
#include "category.h"
#include "bank.h"
#include "operation.h"
#include "file.h"
#include "controllers/user.h"

using namespace isce;

void Route::up() {

  Route::prefix("api/auth")->middleware({})->group({
    Route::post("/login", Auth::login),
    Route::post("/reg", Auth::registration),
    Route::get("/me", Auth::me),
    Route::post("/out", Auth::out),
    Route::post("/out/{id}", Auth::out),
    Route::post("/out_all", Auth::out_all),
    Route::get("/sessions", Auth::sessions),
  });

  // Route::prefix("api/user")->middleware({})->group({
  //   Route::get("/avatar", UserCNT::avatar),
  //   Route::put("/update", UserCNT::update),
  // });

  Route::prefix("api/wall")->middleware({})->group({

    Route::post("/create", WallController::create),
    Route::put("/update", WallController::update),
    Route::get("/get", WallController::get),
    Route::delete_("/delete",WallController::delete_),
    Route::get("/my", WallController::get_user_wall),
    Route::get("/operations", WallController::get_operation_wall),
    Route::get("/walls", WallController::get_walls_user),
    Route::get("/c_wall", WallController::get_category_wall),
    Route::get("/c", WallController::get_currency_list),
    });
  Route::prefix("api/category")->middleware({})->group({
    // category
    Route::post("/create",CategoryController::create),
    Route::put("/update",CategoryController::update),
    Route::get("/get",CategoryController::get),
    Route::delete_("/delete",CategoryController::delete_),
    Route::post("/set_l", CategoryController::set_limit),
    });
  Route::prefix("api/opreation")->middleware({})->group({
    // opreation
    Route::post("/create", OperationController::create),
    Route::put("/update", OperationController::update),
    Route::get("/get", OperationController::get),
    Route::delete_("/delete", OperationController::delete_)

    });

  Route::prefix("api/bank")->middleware({})->group({
    Route::get("/get_rate", Bank::get_rate)
    });

  Route::prefix("api/file")->middleware({})->group({
    Route::get("/{id}", FileController::get),
    Route::post("/", FileController::upload)
    });

}
