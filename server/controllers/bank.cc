#include "bank.h"
#include "cbank.h"
#include "models/User.h"
#include "models/Token.h"
#include <isce/Utils.h>
#include "systems/cbank.h"




response_t Bank::get_rate(request_t request) {
	
	BankRequestDTO req = { request->input("ISO"), request->input("date")};
	std::replace(req.date.begin(), req.date.end(), '.', '/');

	std::unique_ptr<sys::CBank>cbank = std::make_unique<sys::CBank>(req.date);
	cbank->start_work();
	std::string currancy = cbank->get_currency(req.iso);
	
	if (currancy.size() == 0) {
		return response()->json("error");
	}

	return response()->json(currancy);
}

