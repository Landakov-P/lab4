#include "pch.h"
#include "cottage.h"
#include "flat.h"
#include "apartments.h"
#include "application.h"


namespace FundClass
{

	int Application::find(const std::string street, int house, int door)
	{
		for (int i = 0; i < table.size(); ++i)
			if (table[i].get_house()->get_street() == street && table[i].get_house()->get_number_of_housing() == house)
			{
				if (typeid(*(table[i].get_house())) == typeid(Cottage))
					if (door == -1)
						return i;
				if (typeid(*(table[i].get_house())) == typeid(Flat))
					if (dynamic_cast<Flat*>(table[i].change_house())->get_number() == door)
						return i;
				if (typeid(*(table[i].get_house())) == typeid(Apartments))
					if (dynamic_cast<Apartments*>(table[i].change_house())->get_number() == door)
						return i;
			}
		return -1;
	}


	Application& Application::insert(Housing* ptr, double val)
	{
		if (val < 0)
			throw std::invalid_argument("Invalid price for 1 m.^2. Try again.");
		std::string street = ptr->get_street();
		int house = ptr->get_number_of_housing();
		int door = -1;
		if (typeid(*ptr) == typeid(Flat))
			door = dynamic_cast<Flat*>(ptr)->get_number();
		else if (typeid(*ptr) == typeid(Apartments))
			door = dynamic_cast<Apartments*>(ptr)->get_number();
		if (find(street, house, door) != -1)
			throw std::invalid_argument("Accommodation at this address is already registered. Try again.");
		mystd::ElemOfTable res(ptr);
		res.set_price(val);
		table.insert(res);
		return *this;
	}


	Application& Application::save(const std::string& name)
	{
		std::fstream file;
		file.open(name, std::ios::out);
		if (!file)
			throw std::invalid_argument("Error open/create file. Try again.");
		int sz = table.size();
		file.write((char*)&sz, sizeof(sz));
		for (int i = 0; i < table.size(); ++i) {
			int len = table[i].get_house()->get_street().size() + 1;
			file.write((char*)&len, sizeof(len));
			file.write((char*)table[i].get_house()->get_street().c_str(), len);
			int n = table[i].get_house()->get_number_of_housing();
			file.write((char*)&n, sizeof(n));
			if (typeid(*(table[i].change_house())) == typeid(Flat))
			{
				Flat* ptr = dynamic_cast<Flat*>(table[i].change_house());
				int id = 1;
				file.write((char*)&id, sizeof(id));
				int number = ptr->get_number();
				file.write((char*)&number, sizeof(number));
				for (int i = 0; i < 4; ++i)
				{
					int len = ptr->select_room(i + 1).get_name().size() + 1;
					file.write((char*)&len, sizeof(len));
					file.write((char*)ptr->select_room(i + 1).get_name().c_str(), len);
					double area = ptr->select_room(i + 1).get_area();
					file.write((char*)&area, sizeof(area));
					len = ptr->select_room(i + 1).get_remark().size() + 1;
					file.write((char*)&len, sizeof(len));
					file.write((char*)ptr->select_room(i + 1).get_remark().c_str(), len);
				}
			}
			else if (typeid(*(table[i].change_house())) == typeid(Apartments))
			{
				Apartments* ptr = dynamic_cast<Apartments*>(table[i].change_house());
				int id = 2;
				file.write((char*)&id, sizeof(id));
				int number = ptr->get_number();
				file.write((char*)&number, sizeof(number));
				int count = ptr->get_countOfRooms();
				file.write((char*)&count, sizeof(count));
				for (int i = 0; i < ptr->get_countOfRooms(); ++i)
				{
					int len = ptr->select_room(i + 1).get_name().size() + 1;
					file.write((char*)&len, sizeof(len));
					file.write((char*)ptr->select_room(i + 1).get_name().c_str(), len);
					double area = ptr->select_room(i + 1).get_area();
					file.write((char*)&area, sizeof(area));
					len = ptr->select_room(i + 1).get_remark().size() + 1;
					file.write((char*)&len, sizeof(len));
					file.write((char*)ptr->select_room(i + 1).get_remark().c_str(), len);
				}
			}
			else
			{
				Cottage* ptr = dynamic_cast<Cottage*>(table[i].change_house());
				int id = 3;
				file.write((char*)&id, sizeof(id));
				int count = ptr->get_countOfBuildings();
				file.write((char*)&count, sizeof(count));
				for (int i = 0; i < ptr->get_countOfBuildings(); ++i)
				{
					Building b = ptr->select_building(i + 1);
					int num = b.get_number();
					file.write((char*)&num, sizeof(num));
					int numrooms = b.get_countOfRooms();
					file.write((char*)&numrooms, sizeof(numrooms));
					for (int j = 0; j < b.get_countOfRooms(); ++j)
					{
						int len = b.select_room(j + 1).get_name().size() + 1;
						file.write((char*)&len, sizeof(len));
						file.write((char*)b.select_room(j + 1).get_name().c_str(), len);
						double area = b.select_room(j + 1).get_area();
						file.write((char*)&area, sizeof(area));
						len = b.select_room(j + 1).get_remark().size() + 1;
						file.write((char*)&len, sizeof(len));
						file.write((char*)b.select_room(j + 1).get_remark().c_str(), len);
					}
				}
			}
			double price = table[i].get_price();
			file.write((char*)&price, sizeof(price));
			int status;
			if (table[i].get_status())
				status = 1;
			else
				status = 0;
			file.write((char*)&status, sizeof(status));
		}
		file.close();
		return *this;
	}


	Application& Application::load(const std::string& name)
	{
		std::ifstream file(name);
		if (!file)
			throw std::invalid_argument("Error open/write file. Try again.");
		int count;
		file.read((char*)&count, sizeof(count));
		Application tmp(count + 5);
		for (int i = 0; i < count; ++i)
		{
			std::string street;
			int len;
			file.read((char*)&len, sizeof(len));
			char* buf = new char[len];
			file.read(buf, len);
			street = buf;
			delete[] buf;
			int numberOfHousing;
			file.read((char*)&numberOfHousing, sizeof(numberOfHousing));
			int type;
			file.read((char*)&type, sizeof(type));
			Housing* ptr = nullptr;
			mystd::ElemOfTable el(ptr);
			if (type == 1)
			{
				ptr = new Flat(street);
				ptr->set_number_of_housing(numberOfHousing);
				Flat* cur = dynamic_cast<Flat*>(ptr);
				file.read((char*)&type, sizeof(type));
				cur->set_number(type);
				for (int i = 0; i < 4; ++i)
				{
					std::string str;
					int len;
					file.read((char*)&len, sizeof(len));
					buf = new char[len];
					file.read(buf, len);
					str = buf;
					delete[] buf;
					double area;
					file.read((char*)&area, sizeof(area));
					cur->select_room(i + 1).set_name(str).set_area(area);
					file.read((char*)&len, sizeof(len));
					buf = new char[len];
					file.read(buf, len);
					str = buf;
					delete[] buf;
					cur->select_room(i + 1).set_remark(str);
				}
			}
			else if (type == 2)
			{
				ptr = new Apartments(street);
				ptr->set_number_of_housing(numberOfHousing);
				Apartments* cur = dynamic_cast<Apartments*>(ptr);
				file.read((char*)&type, sizeof(type));
				cur->set_number(type);
				int num;
				file.read((char*)&num, sizeof(num));
				for (int i = 0; i < num; ++i)
				{
					std::string str;
					int len;
					file.read((char*)&len, sizeof(len));
					buf = new char[len];
					file.read(buf, len);
					str = buf;
					delete[] buf;
					double area;
					file.read((char*)&area, sizeof(area));
					Room room(str);
					room.set_area(area);
					cur->add_room(room);
					file.read((char*)&len, sizeof(len));
					buf = new char[len];
					file.read(buf, len);
					str = buf;
					delete[] buf;
					cur->select_room(i + 1).set_remark(str);
				}
			}
			else if (type == 3)
			{
				ptr = new Cottage(street);
				ptr->set_number_of_housing(numberOfHousing);
				Cottage* cur = dynamic_cast<Cottage*>(ptr);
				int buildings;
				file.read((char*)&buildings, sizeof(buildings));
				for (int i = 0; i < buildings; ++i)
				{
					Building b;
					int counts;
					file.read((char*)&counts, sizeof(counts));
					b.set_number(counts);
					file.read((char*)&counts, sizeof(counts));
					for (int j = 0; j < counts; ++j)
					{
						Room room;
						std::string str;
						int len;
						file.read((char*)&len, sizeof(len));
						buf = new char[len];
						file.read(buf, len);
						str = buf;
						delete[] buf;
						double area;
						file.read((char*)&area, sizeof(area));
						room.set_name(str).set_area(area);
						file.read((char*)&len, sizeof(len));
						buf = new char[len];
						file.read(buf, len);
						str = buf;
						delete[] buf;
						room.set_remark(str);
						b.add_room(room);
					}
					cur->add_building(b);
				}
			}
			double price;
			file.read((char*)&price, sizeof(price));
			el.set_price(price);
			file.read((char*)&type, sizeof(type));
			if (type)
				el.change_status();
			el.set_house(ptr);
			tmp.access_to_table()->insert(el);
		}
		*this = tmp;
		return *this;
	}


	std::ostream& operator <<(std::ostream& os, const Application& table)
	{
		if (!table.table.size())
			os << "Empty.";
		int i = 1;
		for (auto iter = table.table.begin(); iter != table.table.end(); ++iter)
			os << "#" << i++ << ":\n" << *iter << "\n";
		return os;
	}
}
