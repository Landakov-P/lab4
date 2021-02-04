#include "pch.h"
#include "building.h"

namespace FundClass 
{

	double Building::get_area() const 
	{
		double res = 0;
		for (int i = 0; i < countOfRooms; ++i)
			res += rooms[i].get_area();
		return res;
	}

	Building& Building::set_number(int val) 
	{
		if (val < 1)
			throw std::invalid_argument("Invalid naumber of building. Try again.");
		number = val;
		return *this;
	}


	Building& Building::add_room(Room& room) 
	{
		rooms.push_back(room);
		++countOfRooms;
		return *this;
	}

	Building& Building::exclude_room(int pos) 
	{
		if (pos < 1 || pos > countOfRooms)
			throw std::invalid_argument("Invalid number of room. Try again.");
		rooms.erase(rooms.begin() + pos - 1);
		--countOfRooms;
		return *this;
	}

	Room& Building::select_room(int pos) 
	{
		if (pos < 1 || pos > countOfRooms)
			throw std::invalid_argument("Invalid number of room. Try again.");
		return rooms[pos - 1];
	}

	const Room& Building::get_room(int pos) const 
	{
		if (pos < 1 || pos > countOfRooms)
			throw std::invalid_argument("Invalid number of room. Try again.");
		return rooms[pos - 1];
	}

	std::ostream& operator <<(std::ostream& os, const Building& building) 
	{
		os << "building #" << building.number << "; count of rooms: " << building.countOfRooms << ";";
		for (int i = 0; i < building.countOfRooms; ++i)
			os << "\n#" << i + 1 << ": " << building.rooms[i];
		os << "\ntotal living space: " << building.get_area();
		return os;
	}

}

