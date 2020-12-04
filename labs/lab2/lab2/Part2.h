#pragma once
#include "DynamicQueue.h"
#include "FixedSizeQueue.h"
#include "SafeQueue.h" 

void task2(int, int, int, ISafeQueue<int>&);
void task2_2(int, int, int, int);
void join(thread*&, int);
void Producer(int, ISafeQueue<int>&, int&);
void Consumer(ISafeQueue<int>&, long long int&, int&, int);
void check_res(long long int, int, int);

mutex mt;
bool all_producers_worked = false;
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
	all_producers_worked =  false;
	int finished_producers = 0;
	thread* producers = new thread[num_producers];
	thread* consumers = new thread[num_consumers];
	long long int check = 0;
	for (int i = 0; i < num_consumers; ++i) {
		consumers[i] = thread([&]() { Consumer(queue, check, finished_producers, num_producers); });
	}

	for (int i = 0; i < num_producers; ++i) {
		producers[i] = thread([&]() { Producer(num_tasks, queue, finished_producers); });
		/*created_at_least_1_producer = true;
		cv.notify_all();*/
	}
	join(consumers, num_consumers);
	join(producers, num_producers);
	//all_producers_worked = true;
	
	check_res(check, num_producers, num_tasks);
}

void join(thread*& threads, int size) {
	for (int i = 0; i < size; ++i) {
		threads[i].join();
	}
}

mutex mt1;
void Producer(int num_tasks, ISafeQueue<int> &queue, int& finished_producers) {
	cout << "Producer started\n";
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < num_tasks; ++i) {
		queue.push_back(1);
	}
	auto end = chrono::steady_clock::now();
	auto duration = end - start;
	mt1.lock();
	cout << "Producer ended. Duration: " << (double) (duration.count() / pow(10,9) ) << endl;
	++finished_producers;
	mt1.unlock();
}

void Consumer(ISafeQueue<int>& queue, long long int &local_index, int& finished_producers, int num_producers) {
	cout << "Consumer started\n";
	auto start = chrono::steady_clock::now();
	int value;
	while (true) {
		if (queue.pop(value)) {
			mt.lock();
			local_index += value;
			mt.unlock();
		}
		else {
			/*if (all_producers_worked)
				break;*/
			if (finished_producers == num_producers) break;
		}
	}

	auto end = chrono::steady_clock::now();
	auto duration = end - start;
	cout << "Consumer ended. Duration: " << (double)(duration.count() / pow(10,9)) << endl;
}

void check_res(long long int check, int num_producers, int num_tasks) {
	if (check == num_producers * num_tasks) {
		cout << "Test: ok\n";
	} else {
		cout << "Test: error!\n";
	}
}