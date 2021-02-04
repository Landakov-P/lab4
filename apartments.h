#ifndef APARTMENTS_H
#define APARTMENTS_H

/*!
\file
\brief Заголовочный файл с описанием класса "Апартаменты"

Данный файл содержит в себе состояние и методы производного класса "Апартаменты"
*/

#include "building.h"
#include "housing.h"
#include "room.h"

namespace FundClass
{
	/*!
	\brief Производный класс жилья "Апартаменты"

	Является классом, который включает в себя состояние и методы, позволяющие описать тип жилья "Апартаменты"
	*/
	class Apartments : public Housing
	{
		Building apart;
	protected:
		/*!
		\brief Метод вывода информации о апартаментах

			В protected область добавляем функцию вывода, чтобы доступ к ней имели и дочерние классы, но напрямую обращаться к ней было нельзя, т.е. вывод происходил только через перегруженный оператор
		То есть, при вызове перегруженного оператора вывода в дочерних классах будет вызываться ИХ метод print,
		а при использовании в них вывода для абстрактного класса, будет использоваться метод print базового класса.
		\param [os] -	ссылка на выходной поток
		\return ссылка на тот же поток
		*/
		virtual std::ostream& print(std::ostream& os) const;
	public:
		/*!
		\brief Конструктор

		Конструктор с заданием названия улицы
		\param [str] - название улицы
		*/
		Apartments(const std::string& str = "undefined") : Housing(str), apart() {};

		/*!
		\brief Метод создания копии объекта апартаментов

		\return указатель на новый объект
		*/
		virtual Apartments* clone() const { return new Apartments(*this); };

		/*!
		\brief Виртуальный деструктор
		*/
		virtual ~Apartments() {};

		/*!
		\brief Получить номер апартаментов
		*/
		int get_number() const { return apart.get_number(); };

		/*!
		\brief Получить кол-во комнат в апартаментах
		*/
		int get_countOfRooms() const { return apart.get_countOfRooms(); };

		/*!
		\brief Получить суммарную жил. площадь апартаментов
		*/
		virtual double get_area() const;

		/*!
		\brief Изменить номер апартаментов

		\param [pos] - номер, на который изменить номер апартаментов
		\return Ссылка на тот же обьект
		\throws std::out_of_range
		*/
		Apartments& set_number(int pos);

		/*!
		\brief Выбрать конкретную комнату апартаментов

		С помощью метода мы получаем доступ к комнате
		\param [pos] - номер комнаты, доступ к которому мы хотим получить
		\return Ссылка на выбранную комнату
		\throws std::out_of_range
		*/
		Room& select_room(int pos);

		/*!
		\brief Удалить комнату из апартаментов

		\param [pos] - номер комнаты, которую нужно удалить
		\return Сслыка на тот же обьект
		\throws std::out_of_range
		*/
		Apartments& exclude_room(int pos);

		/*!
		\brief Добавить новую комнату

		Добавляется не копия, а именно передаваемый обьект
		\param [room] - ссылка на добавляемую комнату
		\return ссылка на тот же обьект
		\throws std::out_of_range
		*/
		Apartments& add_room(Room& room);

		/*!
		\brief Вывод информации об апартаментах в выходной поток (аналогично методу print)

		\return Ссылка на тот же поток
		*/
		friend std::ostream& operator << (std::ostream&, const Apartments&);
	};
}


#endif // !APARTMENTS_H


