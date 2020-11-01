#include<iostream>
#include<thread>



//1 Using Function Pointer
void foo(int x)
{
	while (x-- > 0)
	{
		std::cout << x << '\n';
	}
}
//
//3 Using Functor Function Object
class Base
{
public:
	void operator()(int x)
	{
		while (x-- > 0)
		{

			std::cout << x << '\n';
		}
	}
};

int main()
{
	//2. Using Lambda Expression
	//std::thread t(foo, 5);
	//t.join();
	/*
	std::thread t1([](int x)
		{
			while (x-- > 0)
			{

				std::cout << x << '\n';
			}
		}, 10);


	t1.join();
	*/

	std::thread t1(Base(), 20);
	t1.join();
	return 0;
}