#ifndef TABLE_H
#define TABLE_H

#include "housing.h"

using namespace FundClass;

namespace mystd
{

	class ElemOfTable {
		bool status;
		double price;
		Housing* house;
	public:

		ElemOfTable() : status(false), price(-1), house() {};

		ElemOfTable(Housing* ptr) : status(false), price(-1), house(ptr) {};

		bool get_status() const { return status; };

		double get_price() const { return price; };

		const Housing* get_house() const { return house; };

		ElemOfTable& change_status() { status = !status; return *this; };

		ElemOfTable& set_price(double);

		ElemOfTable& set_house(Housing* ptr) { house = ptr; return *this; };

		Housing* change_house() { return house; };

		friend std::ostream& operator <<(std::ostream&, const ElemOfTable&);

	};


	template<typename T>
	class TableIt;


	template<typename T>
	class Table {
		static const int QUOTA = 5;
		int m_size;
		int m_top;
		T* m_data;

		friend class TableIt<T>;

	public:

		Table() : m_size(QUOTA), m_top(0), m_data(new T[m_size]) {};

		Table(int);

		~Table() { delete[] m_data; };

		Table(const Table&);

		Table(Table&&);

		Table& operator =(const Table&);

		Table& operator =(Table&&);

		typedef TableIt<T> iterator;

		iterator begin() const { return iterator(m_data); };

		iterator end() const { return iterator(m_data + m_top); };

		T& operator[](const int pos) { return m_data[pos]; };

		const T& operator[](const int pos) const { return m_data[pos]; };

		int size() const { return m_top; };

		int capicity() const { return m_size; };

		bool empty() { return !m_top; };

		Table& clear();

		Table& insert(const T&);

		iterator erase(iterator);

		Table& swap(const Table&);

	};


	template<typename T>
	class TableIt {
		T* m_ptr;

	public:

		TableIt() : m_ptr() {};

		TableIt(T* ob) : m_ptr(ob) {};

		TableIt& operator =(const TableIt& copy) { m_ptr = copy.m_ptr; return *this; };

		TableIt operator +(const int);

		TableIt operator -(const int);

		TableIt& operator +=(const int pos) { m_ptr += pos; return *this; };

		TableIt& operator -=(const int pos) { m_ptr -= pos; return *this; };

		TableIt& operator ++();

		TableIt& operator --();

		TableIt operator++(int);

		TableIt operator--(int);

		bool operator <(const TableIt& cur) { return m_ptr < cur.m_ptr; };


		bool operator >(const TableIt& cur) { return m_ptr > cur.m_ptr; };

		bool operator <=(const TableIt& cur) { return m_ptr <= cur.m_ptr; };


		bool operator >=(const TableIt& cur) { return m_ptr >= cur.m_ptr; };


		T& operator*() { return *m_ptr; };

		const T& operator*() const { return *m_ptr; };

		bool operator == (const TableIt& cur) { return m_ptr == cur.m_ptr; };
		bool operator != (const TableIt& cur) { return m_ptr != cur.m_ptr; };
		bool operator !() { return !m_ptr; };

	};



	template <typename T>
	Table<T>::Table(int sz)
	{
		if (sz < 0)
			throw std::invalid_argument("Invalid value of capacity. Try again.");
		m_data = new T[sz];
		m_size = sz;
		m_top = 0;
	};


	template <typename T>
	Table<T>::Table(const Table<T>& copy) : Table<T>(copy.m_size)
	{
		m_top = copy.m_top;
		for (int i = 0; i < m_top; ++i)
			m_data[i] = copy.m_data[i];
	}


	template<typename T>
	Table<T>::Table(Table<T>&& move) : m_data(move.m_data), m_size(move.m_size), m_top(move.m_top) {
		move.m_data = nullptr;
	}


	template<typename T>
	Table<T>& Table<T>::operator=(const Table<T>& copy)
	{
		if (this != &copy)
		{
			T* _new = new T[copy.m_size];
			m_size = copy.m_size;
			m_top = copy.m_top;
			delete[] m_data;
			m_data = _new;
			for (int i = 0; i < m_top; ++i)
				m_data[i] = copy.m_data[i];
		}
		return *this;
	}


	template<typename T>
	Table<T>& Table<T>::operator=(Table<T>&& move) {
		return swap(move);
	}


	template <typename T>
	Table<T>& Table<T>::clear()
	{
		T* _new = new T[QUOTA];
		T* old = m_data;
		m_size = QUOTA;
		m_top = 0;
		m_data = _new;
		delete[] old;
		return *this;
	}



	template<typename T>
	Table<T>& Table<T>::insert(const T& el)
	{
		if (m_top >= m_size)
		{
			T* _new = new T[m_size + QUOTA];
			m_size += QUOTA;
			T* _old = m_data;
			m_data = _new;
			for (int i = 0; i < m_top; ++i)
				m_data[i] = _old[i];
			delete _old;
		}
		m_data[m_top++] = el;
		return *this;
	}


	template<typename T>
	TableIt<T> Table<T>::erase(TableIt<T> pos)
	{
		if (pos < begin() || pos >= end())
			throw std::out_of_range("Invalid index. Try again.");
		if (m_top != 1)
			(*pos) = *(end() - 1);
		--m_top;
		return pos + 1;
	}


	template<typename T>
	// Обменять содержимое двух векторов
	Table<T>& Table<T>::swap(const Table& other)
	{
		int tmp = m_top;
		m_top = other.m_top;
		other.m_top = tmp;
		tmp = m_size;
		m_size = other.m_size;
		other.m_size = tmp;
		T* ptr = m_data;
		m_data = other.m_data;
		other.m_data = ptr;
		return *this;
	}


	template<typename T>
	TableIt<T> TableIt<T>::operator +(const int pos) {
		TableIt<T> res(m_ptr + pos);
		return res;
	}


	template<typename T>
	TableIt<T> TableIt<T>::operator -(const int pos)
	{
		TableIt<T> res(m_ptr - pos);
		return res;
	}


	template <typename T>
	TableIt<T>& TableIt<T>::operator++()
	{
		++m_ptr;
		return *this;
	}


	template <typename T>
	TableIt<T>& TableIt<T>::operator--()
	{
		--m_ptr;
		return *this;
	}


	template<typename T>
	TableIt<T> TableIt<T>::operator++(int)
	{
		TableIt iter(*this);
		++m_ptr;
		return iter;
	}


	template<typename T>
	TableIt<T> TableIt<T>::operator--(int)
	{
		TableIt iter(*this);
		--m_ptr;
		return iter;
	}


}


#endif // !TABLE_H


