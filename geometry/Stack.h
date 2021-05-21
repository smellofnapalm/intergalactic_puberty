#pragma once

using namespace std;

template<typename T>
class Stack 
{
private:
	T* arr = nullptr;
	size_t used = 0;
	size_t size = 0;
public:
	// ctors and dtor
	Stack(size_t _capacity = 100);
	Stack(const Stack&);
	~Stack() { delete[] arr; size = 0; used = 0; }

	// getters
	size_t get_used() const noexcept { return used; }
	size_t get_size() const noexcept { return size; }

	void push(const T&);
	T top() const;
	void pop();

	bool is_empty() const noexcept { return used == 0; }
};

template<typename T>
Stack<T>::Stack(size_t _capacity)
{
	if (_capacity == 0)
		throw "Invalid size!";

	T* new_arr = new T[_capacity];
	delete[] arr;
	arr = new_arr;

	size = _capacity;
	used = 0;
}

template<typename T>
Stack<T>::Stack(const Stack& s)
{
	T* new_arr = new T[s.size];
	for (size_t i = 0; i < s.used; i++)
		new_arr[i] = s.arr[i];

	delete[] arr;
	arr = new_arr;
	size = s.size;
	used = s.used;
}

template<typename T>
void Stack<T>::push(const T& el)
{
	if (size == used)
	{
		T* new_arr = new T[size * 2 + 1];
		for (size_t i = 0; i < size; i++)
			new_arr[i] = arr[i];

		delete[] arr;
		arr = new_arr;
		size = size * 2 + 1;
	}
	arr[used] = el;
	used++;
}

template<typename T>
T Stack<T>::top() const
{
	if (used == 0)
		throw "Invalid operation: stack is empty!";
	return arr[used - 1];
}

template<typename T>
void Stack<T>::pop() {

	if (used == 0)
		throw "Invalid operation: stack is empty!";
	used--;
}


