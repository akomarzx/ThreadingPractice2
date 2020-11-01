/*
NOTES:0
0. It is very light weight wrapper for owning mutex on scoped basis.
1. It acquires mutex lock the moment you create the object of lock_guard.
2. It automatically removes the lock while goes out of scope.
3. You can not explicitly unlock the lock_guard.
4. You can not copy lock_guard.
*/

#include <iostream>
#include<thread>
#include<mutex>

std::mutex m;
int buffer = 0;

void foo(const char* ThreadNumber , int LoopFor)
{
	std::lock_guard<std::mutex> lock1(m);
	for (int i{ 0 }; i <= LoopFor; ++i)
	{
		++buffer;
		std::cout << "thread name : " << ThreadNumber << '\n';
	}
}



int main()
{
	std::thread t1(foo ,"T1", 5);
	std::thread t2(foo, "T2", 10);

	t1.join();
	t2.join();

	std::cout << buffer << '\n';
	return 0;
}
