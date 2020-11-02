/*
NOTES:
0. std::timed_mutex is blocked till timeout_time or the lock is aquired and returns true if success 
   otherwise false.
1. Member Function:
   a. lock 
   b. try_lock
   c. try_lock_for    ---\ These two functions makes it different from mutex.
   d. try_lock_until  ---/ 
   e. unlock

EXAMPLE: try_lock_for();
Waits until specified timeout_duration has elapsed or the lock is acquired, whichever comes first.
On successful lock acquisition returns true, otherwise returns false.
*/
#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

int MyAmount = 0;
std::timed_mutex m;

void increment(int i)
{
   if(m.try_lock_for(std::chrono::seconds(1)))
   {
      ++MyAmount;
      std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout << "Thread : "<< i << " Entered\n";
      m.unlock(); 
   }
   else
   {
      std::cout <<"Thread " << i << " Couldnt Enter\n";
   }
   
}

int main()
{
    std::thread t1(increment ,1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    std::cout << MyAmount << '\n';
    
    std::cin.get();
    return 0;
    }

