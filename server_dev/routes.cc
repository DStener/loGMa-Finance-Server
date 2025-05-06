#include <iostream>

#include <isce/Route.h>

#include "controllers/auth.h"
#include "controllers/role.h"
#include "controllers/permission.h"
#include "controllers/user_and_role.h"
#include "controllers/role_and_permission.h"

using namespace isce;

void Route::up() {

  Route::prefix("api/ref/policy")->middleware({})->group({
    // Controller "Role"
    Route::get("/role", Role::get_list),  
    Route::get("/role/{id}", Role::get),
    Route::post("/role", Role::create),
    Route::put("/role/{id}", Role::update),
    Route::delete_("/role/{id}", Role::delete_),
    Route::delete_("/role/{id}/soft", Role::soft_delete),
    Route::post("/role/{id}/restore", Role::restore),

    // Controller "Permission"
    Route::get("/permissions", Permission::get_list ),
    Route::get("/permissions/{id}", Permission::get),
    Route::post("/permissions", Permission::create),
    Route::put("/permissions/{id}", Permission::update),
    Route::delete_("/permissions/{id}", Permission::delete_),
    Route::delete_("/permissions/{id}/soft", Permission::soft_delete),
    Route::post("/permissions/{id}/restore", Permission::restore),
  });

  Route::prefix("api/ref")->middleware({})->group({
    // Controller "UserAndRole"
    Route::get("/user", UserAndRole::get_users),
    Route::get("/user/{id}/role", UserAndRole::get_user_role),
    Route::post("/user/{id}/role", UserAndRole::add_user_role),
    Route::delete_("user/{id}/role/{role_id}", UserAndRole::remove_user_role),

    // Controller "RoleAndPermission"
    Route::get("/role/{id}/permission", RoleAndPermission::get_permisison_role),
    Route::post("/role/{id}/permission", RoleAndPermission::add_permission_role),
    Route::delete_("/role/{id}/permission/{permission_id}", RoleAndPermission::remove_permission_role),
  });

  Route::post("/auth/register", Auth::registration);
  Route::post("/login", Auth::login);

  Route::prefix("api/auth")->middleware({})->group({
    Route::get("/me", Auth::me),
    Route::post("/out", Auth::out),
    Route::get("/tokens", Auth::tokens),
    Route::post("/out_all", Auth::out_all)
  });
}
