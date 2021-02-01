#ifndef ROOM_H
#define ROOM_H

namespace FundClass
{

	class Room
	{
		std::string name;
		double area;
		std::string remark;
	public:
		Room(const std::string& str = "undefined") :
			name(str),
			area(0),
			remark("empty") {};


		std::string get_name() const { return name; };
		std::string get_remark() const { return remark; };
		double get_area() const { return area; };


		Room& set_name(const std::string& str) { name = str; return *this; };
		Room& set_remark(const std::string& str) { remark = str; return *this; };
		Room& set_area(double);


		friend std::ostream& operator <<(std::ostream&, const Room&);
	};

}

#endif // !ROOM_H


