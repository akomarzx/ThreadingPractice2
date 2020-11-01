/*
Mutex: Mutual Exclusion

RACE CONDITION:
0. Race condition is a situation where two or more threads/process happens to change a common data at the same time.
1. If there is a race condition then we have to protect it and the protected section is  called critical section/region.

MUTEX:
0. Mutex is used to avoid race condition.
1. We use lock() , unlock() on mutex to avoid race condition.


call to std::mutex::lock block the execution until the thread can aquire the lock
*/
#include<iostream>
#include<thread>
#include<mutex>


std::mutex m;
int MyAmount = 0;

void AddMoney()
{
	m.lock();
	++MyAmount;
	m.unlock();
}


int main()
{
	std::thread t1(AddMoney);
	std::thread t2(AddMoney);
	
	t1.join();
	t2.join();

	std::cout << MyAmount << '\n';
	return 0;
}