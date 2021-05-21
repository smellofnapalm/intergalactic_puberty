#include "List.h"


template<class T>
list<T>::~list()
{
	node<T>* p = begin;
	while (p != nullptr)
	{
		node<T>* current = p->next;
		if (p == cur) cur = nullptr;
		delete p;
		p = current;
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
		if (begin == cur) cur = nullptr;
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
		if (end == cur) cur = nullptr;
		delete end;
		end = new_end;
		size--;
		return val;
	}
}

template <class T>
T list<T>::pop_node(node<T>* del)
{
	if (size == 0 || !del)
		throw std::exception("Current element is NULL!");

	if (del == end)
		return pop_back();
	else if (del == begin)
		return pop_front();
	else
	{
		del->last->next = del->next;
		del->next->last = del->last;
		if (del == cur) cur = nullptr;
		size--;
		T val = del->value;
		delete del;
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