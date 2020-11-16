#pragma once
#include "DynamicQueue.h"
#include "FixedSizeQueue.h"
#include "SafeQueue.h" 

void task2_1(int,int,int);
void task2_2(int,int,int,int);
void join(thread*&, int);
void Producer(int, ISafeQueue<int>&);
void Consumer(ISafeQueue<int>&, long long int&);
void check_res(long long int, int, int);

mutex mt;

void part2() {
	cout << "Dynamic queue:\n";
	task2_1(4 * 1024 * 1024, 1, 1);
	task2_1(4 * 1024 * 1024, 2, 2);
	task2_1(4 * 1024 * 1024, 3, 3);
	cout << "Fixed size queue:\n";
	task2_2(4 * 1024*1024, 1, 1,1);
	task2_2(4 * 1024 * 1024, 2, 2, 4);
	task2_2(4 * 1024 * 1024, 3, 3, 16);
}

void task2_1(int num_tasks, int num_consumers, int num_producers) {
	DynamicQueue<int> dynamic_queue;
	thread* producers = new thread[num_producers];
	thread* consumers = new thread[num_consumers];
	for (int i = 0; i < num_producers; ++i) {
		producers[i] = thread([&]() { Producer(num_tasks, dynamic_queue); });
	}
	//long long int* results = new long long int[num_consumers] {0};
	long long int check = 0;
	for (int i = 0; i < num_consumers; ++i) {
		consumers[i] = thread([&]() { Consumer(dynamic_queue, check); });
	}
	join(producers, num_producers);
	join(consumers, num_consumers);
	check_res(check, num_producers, num_tasks);
}

void task2_2(int num_tasks, int num_consumers, int num_producers, int size_queue) {
	FixedSizeQueue<int> queue1(size_queue);
	thread* producers = new thread[num_producers];
	thread* consumers = new thread[num_consumers];
	for (int i = 0; i < num_producers; ++i) {
		producers[i] = thread([&]() { Producer(num_tasks, queue1); });
	}
	//long long int* results = new long long int[num_consumers] {0};
	long long int check = 0;
	for (int i = 0; i < num_consumers; ++i) {
		consumers[i] = thread([&]() { Consumer(queue1, check); });
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
	mt.lock();
	cout << "Producer started\n";
	mt.unlock();
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
	mt.lock();
	cout << "Consumer started\n";
	mt.unlock();
	auto start = chrono::steady_clock::now();
	int value;
	while (queue.pop(value)) {
		lock_guard<mutex> g(mt);
		local_index+=value;
	}
	auto end = chrono::steady_clock::now();
	auto duration = end - start;
	mt.lock();
	cout << "Consumer ended. Duration: " << (double)(duration.count() / pow(10,9)) << endl;
	mt.unlock();
}

void check_res(long long int check, int num_producers, int num_tasks) {
	if (check == num_producers * num_tasks) {
		cout << "Test: ok\n";
	}
	else {
		cout << "Test: error!\n";
	}
}