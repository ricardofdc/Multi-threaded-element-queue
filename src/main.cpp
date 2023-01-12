/**
 * @file main.cpp
 * @author Ricardo Cardoso
 * @brief Main file for the app.
 * @version 0.1
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "queue.h"

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

std::mutex m; /**< mutex used to synchronize writer and reader threads */
std::condition_variable cv_read, cv_write; /**< condition variables to check when blocked threads can unblock */

bool write_enabled = true;	/**< to be used by cv_read */
bool read_enabled = false;	/**< to be used by cv_write */

/**
 * @brief Reader thread.
 * 
 * Waits for messages/instructions from main(). 
 * These instructions come in the form of a bool variable:
 * - true: Pop the next object from Queue.
 * - false: terminate thread.
 * 
 * In the case of the Queue being empty this thread blocks
 * and waits for 'read_enabled' to be set to 'true' by the
 * writer thread.
 * 
 * If needed sets 'write_enabled' to 'true' after popping one
 * object from the Queue.
 * 
 * @tparam T Type of the objects in the Queue.
 * @param q Queue to read objects from.
 * @param msg Message queue to receive instructions from main() (or any other function that creates this thread).
 */
template <typename T>
void read(Queue<T> & q, std::queue<bool> & msg){
	while(1){
		// check if msg queue has new messages
		if(msg.empty()){
			continue;
		}

		// check message
		// true -> do a Pop operation
		// false -> end thread
		if(msg.front() == false){
			return;
		}

		// check if queue returns an object
		if (!q.Pop()){
			// Queue is empty
			// wait for objects to be added
			read_enabled = false;
			std::unique_lock<std::mutex> lock(m);
			while(!read_enabled) {
				std::cout << "locked read" << std::endl;
				cv_read.wait(lock);
			}
			continue;
		}
		// object was returned 
		// delete msg from queue and notify writer if needed
		msg.pop();	
		if(!write_enabled){
			write_enabled = true;
			cv_write.notify_one();
		}
	}

	std::cout << "end of reader" << endl;
}

/**
 * @brief Writer thread.
 * 
 * Waits for messages/instructions from main(). 
 * These instructions come in the form of optional objects:
 * - nullopt: terminate thread.
 * - any object: Push that object to Queue.
 * 
 * In the case of the Queue being full this thread blocks
 * and waits for 'write_enabled' to be set to 'true' by the
 * reader thread.
 * 
 * If needed sets 'read_enabled' to 'true' after pushing one
 * object to the Queue.
 * 
 * @tparam T Type of the objects in the Queue.
 * @param q Queue to read objects from.
 * @param msg Message queue to receive instructions from main() (or any other function that creates this thread).
 */
template <typename T>
void write(Queue<T> & q, std::queue<T> & msg){
	while(1){
		// check if msg queue has new messages
		if(msg.empty()){
			continue;
		}

		// if message is '-1' end thread 
		// works in this use case, might need to be changed
		// for other use cases
		if(!msg.front()){
			return;
		}

		// try to push object to Queue
		try{
			q.Push(msg.front());
			msg.pop();

			// notifies reader if needed
			if(!read_enabled){
				read_enabled = true;
				cv_read.notify_one();
			}
		}

		// Queue is full
		// wait for objects to be added
		catch (QueueFullException e){
			write_enabled = false;
			std::unique_lock<std::mutex> lock(m);
			while(!write_enabled) {
				std::cout << "locked write" << std::endl;
				cv_write.wait(lock);
			}
		}
	}
}

/**
 * @brief Main function of the app.
 * 
 * 1. Creates a Queue of int with size 2.
 * 2. Creates two message queues to send commands to the threads.
 * 3. Creates two threads (reader and writer).
 * 4. Sends multiple commands to the threads.
 * 5. Waits for the threads to join.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[])
{
	Queue<int> q(2);

	std::queue<std::optional<int>> m_queue_writer;
	std::queue<bool> m_queue_reader;


	thread writer(&write<int>, std::ref(q), std::ref(m_queue_writer));
	thread reader(&read<int>, std::ref(q), std::ref(m_queue_reader));

	m_queue_writer.push(1);
	sleep(1);
	m_queue_reader.push(true);
	sleep(1);
	m_queue_writer.push(2);
	sleep(1);
	m_queue_writer.push(3);
	sleep(1);
	m_queue_writer.push(4);
	sleep(1);
	m_queue_reader.push(true);
	sleep(1);
	m_queue_reader.push(true);
	sleep(1);
	m_queue_reader.push(true);
	sleep(1);
	m_queue_reader.push(true);
	sleep(1);
	m_queue_writer.push(5);
	sleep(1);

	m_queue_writer.push(std::nullopt);
	m_queue_reader.push(false);

	if(writer.joinable()){
		std::cout << "Joining writer thread." <<std::endl;
		writer.join();
		std::cout << "Writer thread joined." << std::endl;
	}
	if(reader.joinable()){
		std::cout << "Joining reader thread." << std::endl;
		reader.join();
		std::cout << "Reader thread joined." << std::endl;
	}

	return 0;
}