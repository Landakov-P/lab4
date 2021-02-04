#ifndef BUILDING_H
#define BUILDING_H

#include "room.h"


namespace FundClass
{

	class Building
	{
		int number;
		int countOfRooms;
		std::vector<Room> rooms;
	public:

		Building(int num = -1) :
			number(num),
			countOfRooms(0),
			rooms() {};


		int get_number() const { return number; };
		int get_countOfRooms() const { return countOfRooms; };
		double get_area() const;
		const Room& get_room(int) const;

		Building& set_number(int);
		Building& add_room(Room&);
		Building& exclude_room(int);
		Room& select_room(int);

		friend std::ostream& operator << (std::ostream& os, const Building& building);

	};

}

#endif // !BUILDING_H
