#include "pch.h"
#include "table.h"


namespace mystd 
{

	ElemOfTable& ElemOfTable::set_price(double val) 
	{
		if (val < 0)
			throw std::invalid_argument("Invalid price. Try again.");
		price = val;
		return *this;
	}

	std::ostream& operator <<(std::ostream& os, const ElemOfTable& eot)
	{
		os << *eot.house << "\nPrice for 1 m.^2: " << eot.price << ";\n status: ";
		if (eot.status)
			os << "populated.";
		else
			os << "not populated.";
		return os;
	}


}
