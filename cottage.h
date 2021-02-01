#ifndef COTTAGE_H
#define COTTAGE_H

#include "housing.h"
#include "building.h"

namespace FundClass
{

	class Cottage : public Housing 
	{
		int countOfBuildings;					
		std::vector<Building> buildings;
	protected:
		virtual std::ostream& print(std::ostream&) const;
	public:

		Cottage(const std::string& str = "undefined"): Housing(str), countOfBuildings(0), buildings() {};

		virtual ~Cottage() {};

		int get_countOfBuildings() const { return countOfBuildings; };

		virtual double get_area() const;

		Building& select_building(int);

		Cottage& exclude_building(int);

		Cottage& add_building(const Building&);

	public:

		friend std::ostream& operator << (std::ostream&, const Cottage&);

		virtual Cottage* clone() const { return new Cottage(*this); };



	};
}

#endif // !COTTAGE_H



