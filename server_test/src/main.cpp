#include <iostream>
#include <isce/Microservice.h>

class Test : isce::Microservice<Test> {
	public:
		METHOD_LIST_BEGIN
				std::cout << "BEST" << std::endl;
		METHOD_LIST_END
};

int main() {

}