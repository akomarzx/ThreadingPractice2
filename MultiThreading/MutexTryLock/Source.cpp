/*

TOPIC: std::mutex::try_lock() On Mutex In C++11 Threading

0. try_lock() Tries to lock the mutex. Returns immediately. On successful lock acquisition returns true otherwise returns false.
1. If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking.
2. If try_lock is called again by the same thread which owns the mutex, the behavior is undefined.
   It is a dead lock situation with undefined behavior. (if you want to be able to lock the same mutex by same thread more than one time the go for recursive_mutex)
*/


#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>


int counter = 0;
std::mutex m;

void foo()
{
	for (int i{ 0 }; i < 10000; ++i)
	{
		if (m.try_lock())
		{
			++counter;
			m.unlock();
		}
	}
}

void foo2()
{
	while (!m.try_lock())
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "t2 locked the mutex\n";
	}
	std::cout << "Thread t1 locked the mutex!\n";
	std::this_thread::sleep_for(std::chrono::seconds(10));
	m.unlock();
	std::cout << "Thread t1 released the mutex!\n";
}

void foo3()
{
	while (!m.try_lock())
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "t1 locked the mutex\n";
	}
	std::cout << "Thread t2 locked the mutex!\n";
	std::this_thread::sleep_for(std::chrono::seconds(10));
	m.unlock();
	std::cout << "Thread t2 released the mutex!\n";

}

int main()
{
	std::thread t1(foo2);
	std::thread t2(foo3);

	t1.join();
	t2.join();

	std::cout << "Counter: " << counter << '\n';

	return 0;
}