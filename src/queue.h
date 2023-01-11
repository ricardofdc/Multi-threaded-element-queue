#include <queue>

template <typename T> 
class Queue {
private:
	int size;
	int count;
	std::queue<T> objects;

public:
	Queue(int size) {
		this->size = size;
		this->count = 0;
	}

	void Push(T element) {
		if(this->count < this->size){
			this->objects.push(element);
			this->count++;
		}
	};

	T Pop() {
		if(this->count > 0){
			this->objects.pop();
			this->count--;
		}
	};

	int Count() {
		return this->count;
	}; // Amount of elements stored now

	int Size() {
		return this->size;
	}; // Max number of elements
};