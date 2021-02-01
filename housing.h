#ifndef HOUSING_H
#define HOUSING_H

namespace FundClass {

	class Housing
	{
		std::string street;		
		int number;				

	public:

		Housing(const std::string& str = "undefined") : street(str), number(-1) {};


		virtual ~Housing() {};


		std::string get_street() const { return street; };
		int get_number_of_housing() const { return number; };


		virtual double get_area() const = 0;


		Housing& set_street(const std::string& str) noexcept { street = str; return *this; };
		Housing& set_number_of_housing(int);


		virtual Housing* clone() const = 0;

		friend std::ostream& operator <<(std::ostream& os, const Housing& h) { return h.print(os); };


	protected:

		virtual std::ostream& print(std::ostream&) const;

	};

}

#endif // !HOUSING_H


