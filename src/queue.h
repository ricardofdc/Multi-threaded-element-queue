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

#ifndef MY_QUEUE_
#define MY_QUEUE_

#include "myExcepions.h"
#include <queue>
#include <mutex>
#include <iostream>
#include <optional>

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
	std::mutex m;

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
		std::unique_lock<std::mutex> lock(this->m);
		if(this->count >= this->size){
			throw QueueFullException();
		}
		this->objects.push(element);
		this->count++;
		lock.unlock();
	};


	/**
	 * @brief Pop element from the queue.
	 * 		  
	 * If the queue is empty return nullptr.
	 * 
	 * @return (T) element popped or 'nullptr' if queue is empty
	 */
	std::optional <T> Pop() {
		std::unique_lock<std::mutex> lock(this->m);
		if(this->count <= 0){
			return std::nullopt;
		}
		std::optional <T> e = this->objects.front();
		this->objects.pop();
		this->count--;
		lock.unlock();
		return e;
	};

	/**
	 * @brief Amount of elements currently stored in the queue.
	 * 
	 * @return (int) amount of elements currently stored in the queue
	 */
	int Count() const {
		return this->count;
	};

	/**
	 * @brief Maximum size/number of elements of the queue.
	 * 
	 * @return (int) maximum number of elements in the queue.
	 */
	int Size() const {
		return this->size;
	}; 

	/**
	 * @brief Get the Objects object
	 * 
	 * @return std::queue<T> objects.
	 */
	std::queue<T> getObjects() const {
		return this->objects;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream &s, const Queue<T> &queue) {
	std::queue<T> q = queue.getObjects();
	s << "[";
	while (!q.empty())
	{
		s << q.front() << ",";
		q.pop();
	}
	s << "]";
	return s;
};

#endif