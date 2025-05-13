#include "bank.h"
#include "cbank.h"
#include "models/User.h"
#include "models/Token.h"
#include <isce/Utils.h>
#include "systems/cbank.h"


response_t Bank::get_rate(request_t request) {
	
	
	BankRequestDTO set_info{request->input("ISO")};

	const auto cbank = sys::cbank();

	std::string currancy = cbank->get_currency(set_info.iso);
	
	return response()->json(currancy);
}