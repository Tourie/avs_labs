#pragma once
#include "DynamicQueue.h"
#include "FixedSizeQueue.h"
#include "SafeQueue.h" 

void task2(int, int, int, ISafeQueue<int>&);
void task2_2(int, int, int, int);
void join(thread*&, int);
void Producer(int, ISafeQueue<int>&);
void Consumer(ISafeQueue<int>&, long long int&);
void check_res(long long int, int, int);

mutex mt;
bool created_at_least_1_producer = { false };
condition_variable cv;

void part2() {
	cout << "Dynamic queue:\n";
	DynamicQueue<int> dynamic_queue;
	task2(4 * 1024 * 1024, 1, 1, dynamic_queue);
	task2(4 * 1024 * 1024, 2, 2, dynamic_queue);
	task2(4 * 1024 * 1024, 3, 3, dynamic_queue);
	cout << "Fixed size queue:\n";
	task2_2(4 * 1024 * 1024, 1, 1, 1);
	task2_2(4 * 1024 * 1024, 2, 2, 4);
	task2_2(4 * 1024 * 1024, 3, 3, 16);
}

void task2_2(int num_tasks, int num_consumers, int num_producers, int size) {
	FixedSizeQueue<int> queue(size);
	task2(num_tasks, num_consumers, num_producers, queue);
}

void task2(int num_tasks, int num_consumers, int num_producers, ISafeQueue<int>&queue) {
	created_at_least_1_producer = { false };
	thread* producers = new thread[num_producers];
	thread* consumers = new thread[num_consumers];
	long long int check = 0;
	for (int i = 0; i < num_consumers; ++i) {
		consumers[i] = thread([&]() { Consumer(queue, check); });
	}

	for (int i = 0; i < num_producers; ++i) {
		producers[i] = thread([&]() { Producer(num_tasks, queue); });
		created_at_least_1_producer = true;
		cv.notify_all();
	}
	join(producers, num_producers);
	join(consumers, num_consumers);
	check_res(check, num_producers, num_tasks);
}

void join(thread*& threads, int size) {
	for (int i = 0; i < size; ++i) {
		threads[i].join();
	}
}

void Producer(int num_tasks, ISafeQueue<int> &queue) {
	cout << "Producer started\n";
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < num_tasks; ++i) {
		queue.push_back(1);
	}
	auto end = chrono::steady_clock::now();
	auto duration = end - start;
	mt.lock();
	cout << "Producer ended. Duration: " << (double) (duration.count() / pow(10,9) ) << endl;
	mt.unlock();
}

void Consumer(ISafeQueue<int>& queue, long long int &local_index) {
	unique_lock<mutex> ul(mt);
	cv.wait(ul, [&]() { return created_at_least_1_producer; });
	ul.unlock();
	this_thread::sleep_for(chrono::milliseconds(1)); //makes code behavior predictable
	cout << "Consumer started\n";
	auto start = chrono::steady_clock::now();
	int value;
	while (queue.pop(value)) {
		lock_guard<mutex> g(mt);
		local_index+=value;
	}
	auto end = chrono::steady_clock::now();
	auto duration = end - start;
	ul.lock();
	cout << "Consumer ended. Duration: " << (double)(duration.count() / pow(10,9)) << endl;
	ul.unlock();
}

void check_res(long long int check, int num_producers, int num_tasks) {
	if (check == num_producers * num_tasks) {
		cout << "Test: ok\n";
	}
	else {
		cout << "Test: error!\n";
	}
}