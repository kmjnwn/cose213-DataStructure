//
// Assignment 2 : Simple calculator using Stack
//
// Array-based stack data structure
//
// COSE213 Fall 2021
//

template<class type>
Stack<type>::~Stack()
{
	delete[] array;
}

template<class type>
type& Stack<type>::Top()
{
	if(top == -1) throw "Error: Stack is empty";
	
	return array[top];
}

template<class type>
void Stack<type>::Push(const type& item)
{
	top++;
	if(top == capacity){
		type *t = new type[capacity*2];

		for(int i = 0; i < capacity; i++){
			t[i] = array[i];
		}		
		capacity *= 2;

		delete[] array;
		array = t;
	}
	
	array[top] = item;
}

template<class type>
void Stack<type>::Pop()
{

	if(top == -1) throw "Error: Stack is empty";

	top --;
}

template<class type>
bool Stack<type>::IsEmpty() const
{
	return (top == -1);
}

