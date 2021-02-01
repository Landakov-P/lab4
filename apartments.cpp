#include "pch.h"
#include "apartments.h"

namespace FundClass
{

	double Apartments::get_area() const 
	{
		double res = 0;
		for (int i = 0; i < countOfRooms; ++i)
			res += rooms[i].get_area();
		return res;
	}

	Apartments& Apartments::set_number(int val) 
	{
		if (val < 1)
			throw std::invalid_argument("Invalid number of apartments. Try again.");
		number = val;
		return *this;
	}

	Room& Apartments::select_room(int pos) 
	{
		if (pos < 1 || pos > countOfRooms)
			throw std::invalid_argument("Invalid number of room. Try again.");
		return rooms[pos - 1];
	}

	Apartments& Apartments::add_room(const Room& room) 
	{
		rooms.push_back(room);
		++countOfRooms;
		return *this;
	}

	Apartments& Apartments::exclude_room(int pos) 
	{
		if (pos < 1 || pos > countOfRooms)
			throw std::invalid_argument("Invalid number of room. Try again.");
		rooms.erase(rooms.begin() + pos - 1);
		--countOfRooms;
		return *this;
	}

	std::ostream& Apartments::print(std::ostream& os) const 
	{
		os << "type of housing: apartments; ";
		Housing::print(os) << ", N. " << number << ";";
		for (int i = 0; i < countOfRooms; ++i) 
		{
			os << "\n " << rooms[i];
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
