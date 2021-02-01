#ifndef APPLICATION_H
#define APPLICATION_H

#include "table.h"

namespace FundClass
{
	class Application {
		mystd::Table<mystd::ElemOfTable> table;
	public:

		Application(int capacity = 0) : table(capacity) {};

		Application& save(const std::string&);

		Application& load(const std::string&);

		Application& insert(Housing*, double);

		mystd::Table<mystd::ElemOfTable>* access_to_table() { return &table; };

		int find(const std::string, int, int = -1);

		friend std::ostream& operator <<(std::ostream&, const Application&);

	};

}


#endif // !APPLICATION_H

