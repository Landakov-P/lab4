#include "pch.h"
#include "flat.h"

namespace FundClass
{

	Flat::Flat(const std::string& str) : Housing(str), number(-1)
	{
		rooms[0].set_name("hall");
		rooms[1].set_name("kichen");
		rooms[2].set_name("bathroom");
		rooms[3].set_name("hallway");
	}

	double Flat::get_area() const
	{
		return rooms[0].get_area() + rooms[1].get_area() + rooms[2].get_area() + rooms[3].get_area();
	}


	Flat& Flat::set_number(int val)
	{
		if (val < 1)
			throw std::invalid_argument("Invalid number of flat. Try again.");
		number = val;
		return *this;
	}

	Room& Flat::select_room(int pos)
	{
		if (pos < 1 || pos > 4)
			throw std::out_of_range("Invalid number of flat. Try again.");
		return rooms[pos - 1];
	}

	std::ostream& Flat::print(std::ostream& os) const
	{
		os << "type of housing: flat; ";
		Housing::print(os) << ", N. " << number << ";";
		for (int i = 0; i < 4; ++i)
			os << "\n " << rooms[i];
		os << "\ntotal living space: " << get_area();
		return os;
	}


	std::ostream& operator << (std::ostream& os, const Flat& flat) 
	{
		flat.print(os);
		return os;
	}

}
