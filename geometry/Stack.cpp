#include "Stack.h"

template<typename T>
void Stack<T>::push(const T& el) {

	if (size == used) {
		if (size == 0) { size = 5; }

		T* n_arr = new T * [size * 2];
		for (int i = 0; i < size; ++i) {
			n_arr[i] = arr[i];
		}

		delete[] arr;
		arr = n_arr;
		delete[] n_arr;
	}

	arr[used] = el;
	++used;
}

template<typename T>
bool Stack<T>::is_empty() {
	if (used == 0) {
		return true;
	}
	return false;
}

template<typename T>
T Stack<T>::top() 
{
	if (used == 0) 
	{
		throw "Invalid operation: stack is empty!";
	}
	else 
	{
		return arr[used-1];
	}
}

template<typename T>
T Stack<T>::floor()
{
	if (used == 0)
	{
		throw "Invalid operation: stack is empty!";
	}
	else
	{
		return arr[0];
	}
}

template<typename T>
void Stack<T>::pop() {

	if (used == 0) {
		throw "Invalid operation: stack is empty!";
	}
	else {
		T* n_arr = new T * [used + 1];
		for (int i = 0; i < used; ++i) {
			n_arr[i] = arr[i];
		}
		delete[] arr;
		arr = n_arr;
		delete[] n_arr;
	}
}

template<typename T>
Stack<T>::~Stack() {
	delete[] arr;
}



