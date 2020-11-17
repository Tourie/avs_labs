#pragma once
#include "SafeQueue.h"
#include <queue>

template<typename T>
class FixedSizeQueue : public ISafeQueue<T>
{
public:
	FixedSizeQueue(int);
	void push_back(T);
	bool pop(T&);

private:
	int size;
	queue<T> queue;
	condition_variable cv;
	mutex mtx;
};

template<typename T>
FixedSizeQueue<T>::FixedSizeQueue(int size)
{
	this->size = size;
}

template<typename T>
inline void FixedSizeQueue<T>::push_back(T arg)
{
	unique_lock<mutex> lk(mtx);
	cv.wait(lk, [&](){ 
		bool result = queue.size() >= size;
		return !result; 
	});
	queue.push(arg);
	++size;
}

template<typename T>
inline bool FixedSizeQueue<T>::pop(T& value)
{
	unique_lock<mutex> g(mtx);
	if (queue.empty()) {
		g.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
		if (queue.empty()) {
			return false;
		}
		g.lock();
	}
	value = queue.front();
	queue.pop();
	--size;
	cv.notify_one();
	return true;
}


