#include "bank.h"
#include "models/User.h"
#include "models/Token.h"
#include <isce/Utils.h>
#include "systems/cbank.h"

response_t Bank::test(request_t request) {

	const auto cbank = sys::CBank();

	return response()->json("The Best Of the best");
}