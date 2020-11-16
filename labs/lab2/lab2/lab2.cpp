#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "time.h"
#include "Part2.h"

using namespace std;

void part1();
void part2();
void task1(int, int, void(*inc_f)(int, int*&));
void check_result(int*,int);
void inc_mutex(int, int*&);
void inc_atomic(int, int*&);

int main() {
	setlocale(LC_ALL, "RU");
	
	part1();
	part2();
}

void part1() {
	int num_tasks = 1024 * 1024;
	cout << "Мьютекс\n";
	task1(num_tasks, 1, inc_mutex);
	task1(num_tasks, 2, inc_mutex);
	task1(num_tasks, 4, inc_mutex);
	task1(num_tasks, 8, inc_mutex);
	task1(num_tasks, 16, inc_mutex);
	task1(num_tasks, 32, inc_mutex);

	cout << "Атомик\n";
	task1(num_tasks, 1, inc_atomic);
	task1(num_tasks, 2, inc_atomic);
	task1(num_tasks, 4, inc_atomic);
	task1(num_tasks, 8, inc_atomic);
	task1(num_tasks, 16, inc_atomic);
	task1(num_tasks, 32, inc_atomic);
}

int index=0;
mutex mtx;
void inc_mutex(int num_tasks,int *&arr) {
	while (index < num_tasks) {
		mtx.lock();
		int tmp = index;
		++index;
		mtx.unlock();
		++arr[tmp];
		this_thread::sleep_for(chrono::nanoseconds(10));
	}
}

atomic<int> safe_index{ 0 };
void inc_atomic(int num_tasks, int*& arr) {
	while (safe_index < num_tasks) {
		arr[safe_index.fetch_add(1)]+=1;
		this_thread::sleep_for(chrono::nanoseconds(10));
	}
}

void task1(int num_tasks, int num_threads, void(*inc_func)(int,int*&)) {
	
	auto start = chrono::steady_clock::now();

	thread* threads = new thread[num_threads];
	int* arr = new int[num_tasks] {0};
	index = 0;
	safe_index.store(0);
	for (int i = 0; i < num_threads; ++i) {
		threads[i] = thread([&]() { inc_func(num_tasks, arr); });
	}
	for (int i = 0; i < num_threads; ++i) {
		threads[i].join();
	}
	/*clock_t end = clock();*/
	auto end = chrono::steady_clock::now();
	auto duration = end - start;
	//Check result
	check_result(arr, num_tasks);

	cout << "Число потоков: " << num_threads << ", время выполнения: " << (double) (duration.count() / pow(10,9)) << endl;
}

void check_result(int* arr , int size) {
	for (int i = 0; i < size; ++i) {
		if (arr[i] != 1) {
			cout << "Error!";
			return;
		}
	}
}



