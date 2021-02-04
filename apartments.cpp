#include "pch.h"
#include "apartments.h"

namespace FundClass
{

	double Apartments::get_area() const
	{
		double res = 0;
		for (int i = 0; i < apart.get_countOfRooms(); ++i)
			res += apart.get_room(i + 1).get_area();
		return res;
	}

	Apartments& Apartments::set_number(int val)
	{
		apart.set_number(val);
		return *this;
	}

	Room& Apartments::select_room(int pos)
	{
		return apart.select_room(pos);
	}

	Apartments& Apartments::add_room(Room& room)
	{
		apart.add_room(room);
		return *this;
	}

	Apartments& Apartments::exclude_room(int pos)
	{
		apart.exclude_room(pos);
		return *this;
	}

	std::ostream& Apartments::print(std::ostream& os) const
	{
		os << "type of housing: apartments; ";
		Housing::print(os) << ", N. " << apart.get_number() << ";";
		for (int i = 0; i < apart.get_countOfRooms(); ++i)
		{
			os << "\n " << apart.get_room(i + 1);
		}
		os << "\nTotal living space: " << get_area();
		return os;
	}

	std::ostream& operator << (std::ostream& os, const Apartments& apart)
	{
		apart.print(os);
		return os;
	}


}
