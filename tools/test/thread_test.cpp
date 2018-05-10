#include <utility>
#include <functional>
#include <atomic>

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <vector>         // std::vector

void pause_thread(int n) 
{
  std::this_thread::sleep_for (std::chrono::seconds(n));
  std::cout << "pause of " << n << " seconds ended\n";
}
void test1(){
	
	std::thread threads[5];
	std::cout << "Spawning 5 threads...\n";
	for (int i=0; i<5; ++i)
		threads[i] = std::thread(pause_thread,i+1);   // move-assign threads

	std::cout << "Done spawning threads. Now waiting for them to join:\n";
	for (int i=0; i<5; ++i)
		threads[i].join();

	std::cout << "All threads joined!\n";

}



std::atomic<int> global_counter (0);

void increase_global (int n) { for (int i=0; i<n; ++i) ++global_counter; }

void increase_reference (std::atomic<int>& variable, int n) { for (int i=0; i<n; ++i) ++variable; }

struct C : std::atomic<int> {
  C() : std::atomic<int>(0) {}
  void increase_member (int n) { for (int i=0; i<n; ++i) fetch_add(1); }
};
void test2(){
	
	std::vector<std::thread> threads;

	std::cout << "increase global counter with 10 threads...\n";
	for (int i=1; i<=10; ++i)
		threads.push_back(std::thread(increase_global,1000));

	std::cout << "increase counter (foo) with 10 threads using reference...\n";
	std::atomic<int> foo(0);
	for (int i=1; i<=10; ++i)
	threads.push_back(std::thread(increase_reference,std::ref(foo),1000));

	std::cout << "increase counter (bar) with 10 threads using member...\n";
	C bar;
	for (int i=1; i<=10; ++i)
		threads.push_back(std::thread(&C::increase_member,std::ref(bar),1000));

	std::cout << "synchronizing all threads...\n";
	for (auto& th : threads) th.join();

	std::cout << "global_counter: " << global_counter << '\n';
	std::cout << "foo: " << foo << '\n';
	std::cout << "bar: " << bar << '\n';

}



void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread f1  " << n << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread f2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void test3(){
	
    int n = 0;

    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n + 1); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference,	std::ref会把地址传给线程
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    t2.join();
    t4.join();
    std::cout << "Final value of n is " << n << '\n';	
}
int main()
{
	test1();
	test2();
	test3();
}