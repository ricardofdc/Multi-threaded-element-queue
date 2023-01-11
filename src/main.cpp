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
#include "threads.h"

#include <iostream>
#include <thread>

using namespace std;


int main(int argc, char* argv[])
{

	thread writer(write);
	thread reader(read);

	writer.join();
	reader.join();
}