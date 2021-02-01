#ifndef FLAT_H
#define FLAT_H

#include "housing.h"
#include "room.h"

namespace FundClass 
{
	class Flat : public Housing {
		int number;					
		Room rooms[4];		
	protected:
		virtual std::ostream& print(std::ostream&) const;
	public:

		Flat(const std::string& str = "undefined");

		virtual ~Flat() {};

		int get_number() const { return number; };

		virtual double get_area() const;

		Flat& set_number(int);

		Room& select_room(int);

		friend std::ostream& operator << (std::ostream&, const Flat&);

		virtual Flat* clone() const { return new Flat(*this); };

	};


}

#endif // !FLAT_H



