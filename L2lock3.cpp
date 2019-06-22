#include<iostream>
#include<thread>
#include<vector>
#include<string>
#include <mutex>
#include <chrono>
#include <time.h>
#include<memory.h>
//#include<sstream>


using namespace std;
using namespace chrono;
std::mutex m;
bool con = true;
int door = 0;
static const int numthread = 200;

vector<bool> Array(numthread, true);
double waiting_time = 0;
//memset(Array, false, sizeof(Array));
void foo(int i)
{
	
	while (con) {}
	auto start2 = system_clock::now();
	if (i != 0) {
		while (Array[i - 1]) {}
	}
	m.lock();
	auto end2 = system_clock::now();
	auto duration2 = duration_cast<microseconds>(end2 - start2);
	
	cout << /*endl << i << " time cost2: " <<*/ double(duration2.count()) /*<< " microseconds"*/ << endl;

	waiting_time += double(duration2.count());

	door++;
	
	m.unlock();

	

	Array[i] = false;
}


int main()
{

	//std::size_t const numthread = 10;
	thread mythread[numthread];

	auto start = system_clock::now();

	for (int i = 0; i < numthread; i++)
	{
		mythread[i] = thread(foo, i);
	}

	/*for (int i = 0; i < numthread; i++)
	{
		mythread[i].join();
	}*/
	con = false;
	//Array[0] = false;
	while (door != numthread) {}  // hold the main fuc untill all thread finished 

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << endl << "time cost: " << double(duration.count()) << " microseconds" << endl;

	double average_waiting_time = waiting_time / numthread;
	cout << "average time: " << average_waiting_time << endl;
	
	system("pause");
}