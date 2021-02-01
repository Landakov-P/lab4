#include "pch.h"
#include "room.h"

namespace FundClass {

	Room& Room::set_area(double val) 
	{
		if (val <= 0)
			throw std::invalid_argument("Invalid value of area. Try again.");
		area = val;
		return *this;
	}

	std::ostream& operator <<(std::ostream& os, const Room& room) 
	{
		os << "type of room: " << room.name << "; area: " << room.area << "; comment: " << room.remark << ";";
		return os;
	}


}
