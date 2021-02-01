#include "lab4.h"
#include "FundClass/cottage.h"
#include "FundClass/apartments.h"
#include "FundClass/flat.h"

#define line "----------------------------------------------------------"

const char* msgs[] =
{
"0. Quit (no autosave);",
"1. Save;",
"2. Add new offer;",
"3. Delete offer;",
"4. Find offer;",
"5. Register check-in;",
"6. Register check-out;",
"7. Show all offers;",
"8. Show vacant offers only;"
};


const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);



namespace Lab4
{

	int dialog(const char* msgs[], int N) {
		std::string errmsgs = "";
		int rc, i;
		do
		{
			std::cout << errmsgs;
			errmsgs = "Error! Try again!";
			for (i = 0; i < N; ++i)
				std::cout << (msgs[i]) << "\n";
			printf("Choose: --> ");
		} while (getType(rc, std::cin) < 0 || rc >= N);
		return rc;
	}


	FundClass::Application Initialization()
	{
		while (true)
		{
			std::cout << "Please choose a way to create: 1 - Create new table; 2 - Load exist table;\n --> ";
			int choose = 0;
			inputType(choose, std::cin, std::cout);
			while (choose < 1 || choose > 2)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(choose, std::cin);
			}
			if (choose == 2)
			{
				std::cout << "Please, enter file name: --> ";
				std::string filename;
				std::getline(std::cin, filename);
				try
				{
					Application table;
					table.load(filename);
					return table;
				}
				catch (const std::invalid_argument& ex)
				{
					std::cout << ex.what() << "\n";
				}
			}
			else
			{
				Application table;
				return table;
			}
		}
	}



	int D_Save(FundClass::Application& table)
	{
		std::string filename;
		std::cout << "Please, enter file name: --> ";
		std::getline(std::cin, filename);
		try
		{
			table.save(filename);
			std::cout << "Table saved successfully!\n";
			return 1;
		}
		catch (const std::invalid_argument& ex) {
			std::cout << ex.what() << "\n";
		}
		return 1;
	}


	int D_Add(Application& table)
	{
		Housing* ptr = nullptr;
		std::cout << "Select the type of accommodation:\n 1 - Flat;\n 2 - Apartments;\n 3 - Cottage;\n --> ";
		int choose;
		inputType(choose, std::cin, std::cout);
		while (choose < 1 || choose > 3)
		{
			std::cout << "Invalid input.Try again:\n--> ";
			getType(choose, std::cin);
		}
		std::string street;
		int house;
		std::cout << "Enter street: --> ";
		std::getline(std::cin, street);
		std::cout << "Enter number: --> ";
		inputType(house, std::cin, std::cout);
		if (choose == 1)
		{
			bool st = true;
			while (st) {
				int door;
				std::cout << "Enter number of flat: --> ";
				inputType(door, std::cin, std::cout);
				if (table.find(street, house, door) != -1)
				{
					std::cout << "There is already accommodation at this address. Try again.\n";
					continue;
				}
				try {
					ptr = new Flat(street);
					ptr->set_number_of_housing(house);
					dynamic_cast<Flat*>(ptr)->set_number(door);
					st = !st;
				}
				catch (const std::invalid_argument& ex)
				{
					std::cout << ex.what() << "\n";
				}
			}
			std::cout << "Now describe the following rooms: hall, kithen, bathroom, hallway:\n ";
			std::string rooms[4] = { "hall", "kithen", "bathroom", "hallway" };
			for (int i = 0; i < 4; ++i) {
				bool state = true;
				while (state)
				{
					double area;
					std::cout << "Enter erea: " << rooms[i] << ": -- > ";
					inputType(area, std::cin, std::cout);
					std::string remark;
					std::cout << "Enter comment: --> ";
					std::getline(std::cin, remark);
					Room* room = nullptr;
					room = create_room(rooms[i], area, remark);
					if (room)
					{
						state = !state;
						dynamic_cast<Flat*>(ptr)->select_room(i + 1) = *room;
					}
					else
						continue;
					delete room;
				}
			}
		}
		else if (choose == 2)
		{
			bool st = true;
			while (st)
			{
				int door;
				std::cout << "Enter number of apartments: --> ";
				inputType(door, std::cin, std::cout);
				if (table.find(street, house, door) != -1)
				{
					std::cout << "There is already accommodation at this address. Try again.\n";
					continue;
				}
				try {
					ptr = new Apartments(street);
					ptr->set_number_of_housing(house);
					dynamic_cast<Apartments*>(ptr)->set_number(door);
					st = !st;
				}
				catch (const std::invalid_argument& ex)
				{
					std::cout << ex.what() << "\n";
					continue;
				}
			}
			int count;
			std::cout << "Now enter the number of rooms in the apartment: --> ";
			inputType(count, std::cin, std::cout);
			while (count < 1)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(count, std::cin);
			}
			for (int i = 0; i < count; ++i)
			{
				bool state = true;
				while (state)
				{
					std::string name;
					std::cout << "Enter type of room: --> ";
					std::getline(std::cin, name);
					double area;
					std::cout << "Enter area of room: -- > ";
					inputType(area, std::cin, std::cout);
					std::string remark;
					std::cout << "Enter comment: --> ";
					std::getline(std::cin, remark);
					Room* room = nullptr;
					room = create_room(name, area, remark);
					if (room)
					{
						state = !state;
						dynamic_cast<Apartments*>(ptr)->add_room(*room);
					}
					else
						continue;
					delete room;
				}
			}
		}
		else
		{
			bool st = true;
			while (st)
			{
				if (table.find(street, house, -1) != -1)
				{
					std::cout << "There is already accommodation at this address. Try again.\n";
					continue;
				}
				try
				{
					ptr = new Cottage(street);
					ptr->set_number_of_housing(house);
					st = !st;
				}
				catch (const std::invalid_argument& ex)
				{
					std::cout << ex.what() << "\n";
					continue;
				}
			}
			int count;
			std::cout << "Now enter count of buildings of cottage: --> ";
			inputType(count, std::cin, std::cout);
			while (count < 1)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(count, std::cin);
			}
			for (int i = 0; i < count; ++i)
			{
				Building* b = create_building();
				dynamic_cast<Cottage*>(ptr)->add_building(*b);
				delete b;
			}
		}
		bool state = true;
		while (state)
		{
			double val;
			std::cout << "Enter the cost of one sq.m. housing: --> ";
			inputType(val, std::cin, std::cout);
			try
			{
				table.insert(ptr, val);
				state = !state;
				std::cout << "Room added successfully." << "\n";
			}
			catch (const std::invalid_argument& ex)
			{
				std::cout << ex.what() << "\n";
			}
		}
		return 1;
	}



	Room* create_room(const std::string& name, double area, const std::string& remark) {
		Room* ptr = new Room(name);
		try
		{
			ptr->set_remark(remark).set_area(area);
			return ptr;
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << ex.what();
			delete ptr;
		}
		return nullptr;
	}


	Building* create_building() {
		Building* ptr = new Building;
		bool state = true;
		while (state) {
			int number;
			std::cout << "Enter number of building: --> ";
			getType(number, std::cin);
			try
			{
				ptr->set_number(number);
				state = !state;
			}
			catch (const std::invalid_argument& ex)
			{
				std::cout << ex.what();
			}
		}
		while (true)
		{
			std::cout << "Choose:\n 1 - Add new room;\n 2 - Delete room;\n 0 - Return;\n --> ";
			int choose;
			inputType(choose, std::cin, std::cout);
			while (choose < 0 || choose > 2)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(choose, std::cin);
			}
			if (!choose)
				return ptr;
			if (choose == 1)
			{
				Room* room = nullptr;
				std::string name;
				std::cout << "Enter type of room: --> ";
				std::getline(std::cin, name);
				int area;
				std::cout << "Enter erea of room: --> ";
				inputType(area, std::cin, std::cout);
				std::string remark;
				std::cout << "Enter comment: --> ";
				std::getline(std::cin, remark);
				if (room = create_room(name, area, remark))
				{
					ptr->add_room(*room);
					std::cout << "Room added successfully:\n" << *ptr << "\n";
				}
				delete room;
			}
			else
			{
				int number;
				std::cout << "Enter number of room: --> ";
				inputType(number, std::cin, std::cout);
				try
				{
					ptr->exclude_room(number);
					std::cout << "Room added successfully:\n" << *ptr << "\n";
				}
				catch (const std::invalid_argument& ex)
				{
					std::cout << ex.what() << "\n";
				}
			}

		}
	}


	int D_Delete(Application& table)
	{
		while (true)
		{
			int choose;
			std::cout << "1. Continue.\n0. Quit.\n --> ";
			inputType(choose, std::cin, std::cout);
			while (choose < 0 || choose > 1)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(choose, std::cin);
			}
			if (!choose)
				break;
			std::string street;
			int house;
			int door = -1;
			adress(street, house, door);
			int i = table.find(street, house, door);
			if (i == -1)
			{
				std::cout << "There is no housing with this address. Try again.\n";
			}
			else
			{
				std::cout << line << "Offer #" << i + 1 << ":\n" << ((*table.access_to_table())[i]) << "\n successfully removed from the table.\n";
				table.access_to_table()->erase(table.access_to_table()->begin() + i);
				return 1;
			}
		}
		return 1;
	}


	int D_Find(Application& table)
	{
		while (true)
		{
			int choose;
			std::cout << "1. Continue.\n0. Quit.\n --> ";
			inputType(choose, std::cin, std::cout);
			while (choose < 0 || choose > 1)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(choose, std::cin);
			}
			if (!choose)
				break;
			std::string street;
			int house;
			int door = -1;
			adress(street, house, door);
			int i = table.find(street, house, door);
			if (i == -1)
			{
				std::cout << "There is no housing with this address. Try again.\n";
			}
			else
			{
				std::cout << line << "Offer found:\n" << "\n" << (*table.access_to_table())[i] << "\n" << line << "\n";
				return 1;
			}
		}
		return 1;
	}


	int D_RegisterIn(Application& table)
	{
		while (true)
		{
			int choose;
			std::cout << "1. Continue.\n0. Quit.\n --> ";
			inputType(choose, std::cin, std::cout);
			while (choose < 0 || choose > 1)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(choose, std::cin);
			}
			if (!choose)
				break;
			std::string street;
			int house;
			int door = -1;
			adress(street, house, door);
			int i = table.find(street, house, door);
			if (i == -1)
			{
				std::cout << "There is no housing with this address. Try again.\n";
			}
			else
			{
				if ((*table.access_to_table())[i].get_status())
					std::cout << "Accommodation with this address is already registered.\n";
				else
				{
					(*table.access_to_table())[i].change_status();
					std::cout << line << "\nAccommodation with this address is vacated:\n" << line << "\n" << (*table.access_to_table())[i] << "\n";
				}
				return 1;
			}
		}
		return 1;
	}


	int D_RegisterOut(Application& table)
	{
		while (true)
		{
			int choose;
			std::cout << "1. Continue.\n0. Quit.\n --> ";
			inputType(choose, std::cin, std::cout);
			while (choose < 0 || choose > 1)
			{
				std::cout << "Invalid input.Try again:\n--> ";
				getType(choose, std::cin);
			}
			if (!choose)
				break;
			std::string street;
			int house;
			int door = -1;
			adress(street, house, door);
			int i = table.find(street, house, door);
			if (i == -1)
			{
				std::cout << "There is no housing with this address.Try again.\n";
			}
			else
			{
				if (!(*table.access_to_table())[i].get_status())
					std::cout << "Housing with this address is already available.\n";
				else
				{
					(*table.access_to_table())[i].change_status();
					std::cout << line << "\nHousing with this address is vacated:\n" << line << "\n" << (*table.access_to_table())[i];
				}
				return 1;
			}
		}
		return 1;
	}


	int D_ShowAll(Application& table) {
		std::cout << line << "\n" << table << "\n" << line << "\n";
		return 1;
	}


	int D_ShowFree(Application& table) {
		std::cout << line << "\n";
		for (int i = 0; i < table.access_to_table()->size(); ++i)
			if (!(*table.access_to_table())[i].get_status())
				std::cout << " Offer #" << i + 1 << ":\n" << (*table.access_to_table())[i] << "\n";
		std::cout << line << "\n";
		return 1;
	}


	void adress(std::string& street, int& house, int& door)
	{
		std::cout << "Please enter the street name: --> ";
		std::getline(std::cin, street);
		std::cout << "Now enter number of street: --> ";
		inputType(house, std::cin, std::cout);
		std::cout << "Will you enter the flat/apartment number? 1 - да, 2 - нет: --> ";
		int choose;
		inputType(choose, std::cin, std::cout);
		while (choose < 1 || choose > 2)
		{
			std::cout << "Invalid input.Try again:\n--> ";
			getType(choose, std::cin);
		}
		if (choose == 1)
		{
			std::cout << "Enter address of flat/apartments: --> ";
			inputType(door, std::cin, std::cout);
		}
	}

}