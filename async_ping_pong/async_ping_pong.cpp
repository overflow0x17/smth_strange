#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

constexpr int COUNTER = 50;
std::mutex mtx;
std::condition_variable check_print;
bool is_printed = false;


void ping()
{
	for (int i = 0; i < COUNTER; ++i)
	{
		std::unique_lock<std::mutex> lock(mtx);
		check_print.wait(lock, []() {return !is_printed; });
		std::cout << "ping\n";
		is_printed = true;
		check_print.notify_one();
	}
}

void pong()
{
	for (int i = 0; i < COUNTER; ++i)
	{
		std::unique_lock<std::mutex> lock(mtx);
		check_print.wait(lock, []() {return is_printed; });
		std::cout << "pong\n";
		is_printed = false;
		check_print.notify_one();
	}

}
int main()
{
	std::thread thread_1(ping);
	std::thread thread_2(pong);


	thread_1.join();
	thread_2.join();
}
