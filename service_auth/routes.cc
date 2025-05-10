#include <iostream>

#include <isce/Route.h>

#include "auth.h"

using namespace isce;

void Route::up() {

  Route::prefix("api/auth")->middleware({})->group({
    Route::post("/login", Auth::login),  
    Route::post("/register", Auth::registration),
    Route::get("/me", Auth::me),
    Route::post("/out", Auth::out),
    Route::post("/out/{id}", Auth::out),
    Route::post("/out_all", Auth::out_all),
    Route::get("/sessions", Auth::sessions),
  });

}
