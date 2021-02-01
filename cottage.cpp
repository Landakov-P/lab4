#include "pch.h"
#include "cottage.h"

namespace FundClass 
{


	double Cottage::get_area() const 
	{
		double res = 0;
		for (int i = 0; i < countOfBuildings; ++i)
			res += buildings[i].get_area();
		return res;
	}


	Building& Cottage::select_building(int pos) 
	{
		if (pos < 1 || pos > countOfBuildings)
			throw std::out_of_range("Invalid number of room Try again.");
		return buildings[pos - 1];
	}

	Cottage& Cottage::add_building(const Building& building) 
	{
		buildings.push_back(building);
		++countOfBuildings;
		return *this;
	}

	Cottage& Cottage::exclude_building(int pos) 
	{
		if (pos < 1 || pos > countOfBuildings)
			throw std::out_of_range("Invalid number of room Try again.");
		buildings.erase(buildings.begin() + pos - 1);
		--countOfBuildings;
		return *this;
	}

	std::ostream& Cottage::print(std::ostream& os) const 
	{
		os << "type of housing: cottage; ";
		Housing::print(os) << ", count of buildings: " << countOfBuildings << ";";
		for (int i = 0; i < countOfBuildings; ++i) 
			os << "\n " << buildings[i];
		os << "\ntotal living space: " << get_area();
		return os;
	}

	std::ostream& operator << (std::ostream& os, const Cottage& cot) 
	{
		cot.print(os);
		return os;
	}



}
