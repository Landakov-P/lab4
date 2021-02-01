#ifndef LAB4_H
#define LAB4_H


#include "FundClass/pch.h"
#include "FundClass/application.h"
#include "FundClass/room.h"
#include "FundClass/building.h"

extern const int NMsgs;

namespace Lab4 
{


	template <class T>
	int getType(T& a, std::istream& stream) 
	{
		int rc = 0;
		stream >> a;
		if (!stream.good())
			rc = 1;		
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return rc;
	};

	template<class T>
	void inputType(T& p, std::istream& istream, std::ostream& ostream) {
		while (getType(p, istream))
			ostream << "Invalid input. Please re-enter: --> ";
	}



	int dialog(const char* msgs[], int);

	FundClass::Application Initialization();

	int D_Save(Application&);

	int D_Add(Application&);

	int D_Delete(Application&);

	int D_Find(Application&);

	int D_RegisterIn(Application&);

	int D_RegisterOut(Application&);

	int D_ShowAll(Application&);

	int D_ShowFree(Application&);

	Room* create_room(const std::string&, double, const std::string&);

	Building* create_building();

	void adress(std::string&, int&, int&);

}

#endif // !LAB4_H
