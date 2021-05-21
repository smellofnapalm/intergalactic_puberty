#pragma once

using namespace std;

template<typename T>
class Stack {
private:
	// Stack 
	T* arr = 0;
	// Amount of used space of Stack
	int used = 0;
	// Size of Stack
	int size = 0;

public:
	// Constructor and Destructor
	Stack() {};
	~Stack();

	// Push the element in Stack
	void push(const T&);
	// Delete the top from Stack
	void pop();
	// Check if Stack is empty
	bool is_empty();
	// Return top-Stack element
	T top();
	// Return first-Stack element
	T floor();
};



