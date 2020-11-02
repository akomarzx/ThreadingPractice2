/*
TOPIC: Condition Variable In C++ Threading

NOTES:
1. Condition variables allow us to synchronize threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronize two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.
5. Condition variables can be used for two purposes:
	a. Notify other threads
	b. Wait for some condition
*/

#include<thread>
#include<condition_variable>
#include<iostream>
#include<functional>

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money)
{
	std::lock_guard<std::mutex>lg(m);
	balance += money;
	std::cout << "Amount added current balance: " << balance << '\n';
	cv.notify_one();
}

void withdrawMoney(int money)
{
	std::unique_lock<std::mutex> ul(m);
	cv.wait(ul, [] 
	{
	return(balance != 0) ? true : false; 
	});
	if (balance >= money)
	{
		balance -= money;
		std::cout << "Amount DEdecuted:" << money << '\n';
	}
	else
	{
		std::cout << "Amount cant deducted, current balance is less than << money << '\n";
	}
	std::cout << "Current Balance is: " << balance << '\n';
}

int main()
{
	std::thread t1(withdrawMoney, 500);
	std::thread t2(addMoney, 500);
	t1.join();
	t2.join();
	return 0;
}