/**
 * @file queue.h
 * @author Ricardo Cardoso
 * @brief Template class Queue.
 * @version 0.1
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <queue>
#include "myExcepions.h"

/**
 * @brief Class used to queue a finite number of elements of any type.
 * 
 * @tparam T type of the elements
 */
template <typename T> 
class Queue {
private:
	int size; 	/**< Size of the queue*/
	int count;	/**< Amount of elements currently store in the queue */
	std::queue<T> objects;	/**< Elements stored on the queue */

public:
	/**
	 * @brief Construct a new Queue object
	 * 
	 * @exception QueueNegativeSizeException queue size must be positive.
	 * @param size max size of the queue
	 */
	Queue(int size) {
		if (size < 0){
			throw QueueNegativeSizeException();
		}
		this->size = size;
		this->count = 0;
	}

	/**
	 * @brief Add an element to the queue.
	 * 		  
	 * If the queue is already full nothing happens.
	 *
	 * @param element 
	 */
	void Push(T element) {
		if(this->count >= this->size){
			throw QueueFullException();
		}
		this->objects.push(element);
		this->count++;
	};


	/**
	 * @brief Pop element from the queue.
	 * 		  
	 * If the queue is empty return nullptr.
	 * 
	 * @return (T) element popped or 'nullptr' if queue is empty
	 */
	T Pop() {
		if(this->count <= 0){
			return nullptr;
		}
		T e = this->objects.front();
		this->objects.pop();
		this->count--;
		return e;
	};

	/**
	 * @brief Amount of elements currently stored in the queue.
	 * 
	 * @return (int) amount of elements currently stored in the queue
	 */
	int Count() {
		return this->count;
	};

	/**
	 * @brief Maximum size/number of elements of the queue.
	 * 
	 * @return (int) maximum number of elements in the queue.
	 */
	int Size() {
		return this->size;
	}; 
};