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
	node<T>* cur = begin;
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

	// delete a certain node and returns its value
	T pop_node(node<T>* del);

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
