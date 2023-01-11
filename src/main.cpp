#include "queue.h"

#include <iostream>
#include <thread>

using namespace std;

void read(){
	cout << "reader" << endl;
}

void write(){
	cout << "writer" << endl;
}

int main(int argc, char* argv[])
{

	thread writer(write);
	thread reader(read);

	writer.join();
	reader.join();
}