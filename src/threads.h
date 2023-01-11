/**
 * @file threads.h
 * @author Ricardo Cardoso
 * @brief Header file for reader and writer functions that will be use as threads.
 * @version 0.1
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

using namespace std;


/**
 * @brief Reading thread.
 * 
 * This thread pops elements from a queue.
 * If the queue is empty the thread will block and wait for next element.
 */
void read();

/**
 * @brief Writing thread.
 * 
 * This thread pushes elements to a queue.
 * If the queue is full the thread will block and wait for an element to be removed.
 */
void write();

