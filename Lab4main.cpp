#include "lab4.h"

#include <iomanip>

extern const char* msgs[];


int (*fptr[])(FundClass::Application&) =
{ 
	nullptr, 
	Lab4::D_Save, 
	Lab4::D_Add, 
	Lab4::D_Delete, 
	Lab4::D_Find, 
	Lab4::D_RegisterIn, 
	Lab4::D_RegisterOut, 
	Lab4::D_ShowAll,
	Lab4::D_ShowFree 
};

int main()
{
	std::cout << std::fixed << std::setprecision(2);
	Application table = Lab4::Initialization();
	int rc;
	while (rc = Lab4::dialog(msgs, NMsgs))
		if (!fptr[rc](table))
			break;
	return 0;
}