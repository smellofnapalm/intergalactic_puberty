#pragma once

#include <exception>
#include <map>
#include <algorithm>
#include <iostream>
#include "Object.h"

template <class T>
struct node
{
	T value;
	node<T>* next;
	node<T>* last;

	node(T _value, node<T>* _next, node<T>* _last)
	{
		value = _value;
		next = _next;
		last = _last;
	}
};

template <class T>
class list
{
public:
	// getters
	node<T>* get_begin() const { return begin; }
	node<T>* get_end() const { return end; }
	size_t get_size() const { return size; }

	// dtor
	~list();

	// push functions
	void push_front(const T& val);
	void push_back(const T& val);

	// pop functions
	T pop_front();
	T pop_back();

	// operators
	node<T>* operator[] (size_t index);
	template<class U>
	friend std::ostream& operator<<(std::ostream& out, const list<U>& l);
private:
	void push_first(const T& val);
	T pop_first();
	node<T>* begin = nullptr;
	node<T>* end = nullptr;
	size_t size = 0;
};

template<class T>
list<T>::~list()
{
	node<T>* p = begin;
	while (p != nullptr)
	{
		node<T>* cur = p->next;
		delete p;
		p = cur;
	}
}

// push functions
template<class T>
void list<T>::push_front(const T& val)
{
	if (size == 0)
		push_first(val);
	else
	{
		node<T>* first = new node<T>(val, begin, nullptr);
		begin->last = first;
		begin = first;
	}
	size++;
}
template<class T>
void list<T>::push_back(const T& val)
{
	if (size == 0)
		push_first(val);
	else
	{
		node<T>* last = new node<T>(val, nullptr, end);
		end->next = last;
		end = last;
	}
	size++;
}

// pop functions
template<class T>
T list<T>::pop_front()
{
	if (size < 2)
		return pop_first();
	else
	{
		T val = begin->value;
		node<T>* first = begin->next;
		first->last = nullptr;
		delete begin;
		begin = first;
		size--;
		return val;
	}
}

template<class T>
T list<T>::pop_back()
{
	if (size < 2)
		return pop_first();
	else
	{
		T val = end->value;
		node<T>* new_end = end->last;
		new_end->next = nullptr;
		delete end;
		end = new_end;
		size--;
		return val;
	}
}

// operators
template<class T>
node<T>* list<T>::operator[] (size_t index)
{
	if (index >= size)
		throw std::exception("Index must be < size!");

	int i = 0;
	node<T>* p = begin;
	while (i < index) { p = p->next; i++; }
	return p;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const list<T>& l)
{
	if (l.get_size() == 0)
	{
		out << "There is no elements in here";
		return out;
	}
	node<T>* p = l.get_begin();
	while (p)
	{
		out << p->value << " ";
		p = p->next;
	}
	out << std::endl;
	return out;
}

template<class T>
void list<T>::push_first(const T& val)
{
	begin = new node<T>(val, nullptr, nullptr);
	end = begin;
}

template<class T>
T list<T>::pop_first()
{
	if (size == 0)
		throw std::exception("There is no elements in list");
	if (size == 1)
	{
		T val = begin->value;
		begin = nullptr;
		end = nullptr;
		size--;
		return val;
	}
}