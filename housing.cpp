#include "pch.h"
#include "housing.h"

namespace FundClass {

	Housing& Housing::set_number_of_housing(int val) 
	{
		if (val < 1)
			throw std::invalid_argument("Invalid number of housing. Try again.");
		number = val;
		return *this;
	}


	std::ostream& Housing::print(std::ostream& os) const 
	{
		os << "address: " << street << ", " << number;
		return os;
	}

}
