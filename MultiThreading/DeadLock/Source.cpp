#include<iostream>
#include<thread>
#include<mutex>
std::mutex m1, m2;

void thread1()
{
	m1.lock();
	m2.lock();
	std::cout << "Critical Section Of t1\n";
	m1.unlock();
	m2.unlock();
}
void thread2()
{
	m2.lock();
	m1.lock();
	std::cout << "Critical Section Of t2\n";
	m2.unlock();
	m1.unlock();
}

int main()
{
	std::thread t1(thread1);
	std::thread t2(thread2);

	t1.join();
	t2.join();

	
	return 0;
}